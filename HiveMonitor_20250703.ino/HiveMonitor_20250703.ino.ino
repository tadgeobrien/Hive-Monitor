//T OBRIEN 20250703
// Taken from https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-web-server-ap-mode/
//
// So now can I modify this so that I am passing sensor data to the page? 
//
//  - Onewire is for external temperature of the hive. Still need to figure out
//    where I would want to put the sensor itself.
//  
//  - QWICC should probaly document the i2c addresses.
//
//  RTC Notes - run 24 hour clock run MM/DD/YYYY I think would make the most sense unless something else makes the data processing different.
//      Or you can use  timestamp in ISO 8601 format (yyyy-mm-ddThh:mm:ss).
//
//  OpenLog Notes - Do you simply create a file for every day of a month and a folder for the month. Then a folder for they year? 
//        Or do you simply create a file to X MB size and then have it time stamp when it creates the file? 
//        I really think the thing here is how do you want to download the data? If you download it periodly with your phone 
//        then you have to think about he file manipulation. If you pull the SD card who cares. (I will pull the SD at the end of the season I think regrdless.
//  
//        Perhaps I do a file write a week and download a weeks worth of data? That would make a lot of sense. What is my weekly start and end date? 
////

//// Libraries I am using
#include <WiFiNINA.h>           //Wifi Library
#include <OneWire.h>            // Takes in the data.
#include <DallasTemperature.h>  //Does calculations and conversion.
#include <SparkFun_RV8803.h>    //Real Time Clock 
#include <SparkFun_SHTC3.h>     //Using for inside Humidity and Temp
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
#include "HX711.h"

//Scale HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

//Adding Classes
RV8803 rtc;       // Declare an instance of the RV8803 class
SHTC3 mySHTC3;    // Declare an instance of the SHTC3 class
OpenLog myLog;    // Declare an instance of the OpenLog class
HX711 scale;      // Declare an instance of HX711 scale class

//Wireless network details.
char ssid[] ="HiveMind";
char pass[] = "Password";  // Can I keep this open? What are the risks?
int keyIndex = 0; //Only for WEP

// One wire setup.
#define ONE_WIRE_BUS 5  //READ IS ON PIN 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float OutCel=0; // Outside Celcius tobrien 20240410. May simply implement this instead of conversions.
float OutFah=0; // Outside Fahrenheit

// Setting up for Humidity sensor.
float InCel=0;  // Inside Celcius temp
float InFah=0;  // Outside Farenheit May not use.
float InHum=0;  // Inside Humidity 

// Setting Up Weight Sensor
long HiveWeight= 0;

//LED Testing tobrien 20240410 keep or remove?
int led = LED_BUILTIN;
int status = WL_IDLE_STATUS;

//Defines server port.
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:

  Wire.begin();     // This is to start the i2c bus I believe
  mySHTC3.begin();  // This calls the SHTC3 sensor to start
  rtc.begin();      // This calls the RTC to start
  rtc.set24Hour();  // This sets RTC to 24 hour clock
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // Setting up for the Scale. 
  
  Serial.begin(9600);
  while (!Serial){
    ; //wait for serial port to connect. Needed for Native USB  Port only -- Huh?
    }

    Serial.println("Access Point Web Server");

    pinMode(led, OUTPUT); //Set pin Mode

    // Check for WiFi Module
    if (WiFi.status() == WL_NO_MODULE){
      Serial.println("Communication with Wifi Module failed!");
      //Don't continue
      while(true);
      }

      String fv = WiFi.firmwareVersion();
      if (fv < WIFI_FIRMWARE_LATEST_VERSION){
        Serial.println("Please upgrade the firmware");
        }

        //print the network name (SSID);
        Serial.print("Creating access point named: ");
        Serial.println(ssid);

        // Create open network. Change this line if creating a WEP network.
        status = WiFi.beginAP(ssid, pass);
        if (status != WL_AP_LISTENING){
          Serial.println("Creating access point failed");
          //Don't continue
          while(true);
          
          }

          //Wait 10 seconds for connection
          delay(10000);

          // start web server on port 80.
          server.begin();

          //you are connected now print the status
          printWiFiStatus();
}

void loop() {
  // put your main code here, to run repeatedly:


  ////////////////////////////////////////////////////
  //  This is the Wifi AP
  ////////////////////////////////////////////////////
  // compare the previous status to the current status
  if (status != WiFi.status()){
    //it had changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED){
      //a device has connected to the AP
      Serial.println("Device connected to AP");
      }else{
      // a device had disconnected from the AP
      Serial.println("Device disconnected from the AP");
        }
    }

    WiFiClient client = server.available(); // listen for incoming clients

    if (client){                      // if you get a client,
      Serial.println("new client");  // print a message out the serial port
      String currentLine = "";        // make a String to hold incoming data from the client
      while (client.connected()){     // loop while the client's connected
        if (client.available()){      // if there's bytes to read from the client,
          char c = client.read();     //read a byte then
          Serial.write(c);            // print it out the serial monitor
          if (c == '\n'){             // if the byte is a newline character
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length()==0){
               // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("");
            
            // the content of the HTTP response follows the header:
              client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
              client.print("Click <a href=\"/H\">here</a> turn the LED off<br>");

              //int randomReading = analogRead(A1);
              //client.print("Random reading from analog pin: ");
              //client.println(randomReading);
              
              //client.print(" ");
              //client.print(currentTime);
              //client.print(" ");
              
              //TOBrien implement the printing of the Data to the web interface
              client.println(String(rtc.stringDateUSA()));
              client.println(String(rtc.stringTime()));
              client.print("<br>Outside Temperature = ");
              client.println(OutCel);
              client.print("<br>Inside Relative Humidty = ");
              client.print(mySHTC3.toPercent());
              client.println("% <br>");
              client.print("Inside Temperature = ");
              client.print(mySHTC3.toDegF());
              client.println(" deg F"); //Need to change to C
              client.println("<br>Weight");
//              client.println(reading());

              //HTTP response ends with a blank line.
              client.println();
              //break out the while loop
              break;
              }else{ 
                // if you got a newline then clear current line
                currentLine = "";
                }
            
            }else if (c != '\r'){
                                      // if you got anything else but a carriage return character,
              currentLine += c;      // add it to the end of the currentLine
              }

              //Check to see if client requests was Get /H or Get /L
              if (currentLine.endsWith("GET /H")){
                digitalWrite(led, HIGH);
              }
              if (currentLine.endsWith("GET /L")){
                digitalWrite(led, LOW);
                }
           }
        }
        // close the connectoin
        client.stop();
        Serial.println("Client disconnected");
      }

      //Date and Time
      myTime();
      
      //Outside temp in C
      OutsideTemp();  // This should be my function to check outside temp.

      //Inside hive monitoring
      SHTC3_Status_TypeDef result = mySHTC3.update(); //Update the sensor
      //InsideHive();
      
    //Hive Weight
    if (scale.is_ready()){
      long HiveWeight = scale.read();
    }



      // Lets write some data to OpenLog Below is an example
        /*    DATE,TIME-24:00,% Humidity,InternalTemp(C),OutsideTemp(C),Weight(lbs)
            20240420,00:20,24,31,1,95
            20240420,01:20,24,31,1,95
            20240420,02:20,24,31,1,95
            20240420,03:20,24,31,1,95
      */
      myLog.begin();
      // Printing this string to the OpenLog
      myLog.println(String(rtc.stringDateUSA())+","+String(rtc.stringTime())+","+String(mySHTC3.toPercent())+","+String(mySHTC3.toDegC())+","+String(OutCel)+",weight");
      // Printing the same string to Serial output so I can verify it      
      //Serial.println(String(rtc.stringDateUSA())+","+String(rtc.stringTime())+","+String(mySHTC3.toPercent())+","+String(mySHTC3.toDegC())+","+String(OutCel)+",weight");
      //
      // Just leaving this here since I am getting a declareation error. 
      Serial.println(String(rtc.stringDateUSA())+","+String(rtc.stringTime())+","+String(mySHTC3.toPercent())+","+String(mySHTC3.toDegC())+","+String(OutCel)+","+HiveWeight);  
      //
      myLog.syncFile();
}

void printWiFiStatus(){
  //print the ssid of the net you are connected to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your wifi shields IP Address
  IPAddress ip =  WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  }
 
void OutsideTemp(){
  // Function for getting the outside temperature. Use this in void loop.
  sensors.requestTemperatures();
  OutCel=sensors.getTempCByIndex(0); //Get Outside C from Onewire.
  
  //Serial.print(" Outside C = "); // TOBrien 20240412 Commented out since I should see it on the web UI
  //Serial.print(OutCel);       // TOBrien 20240412 Commented out since I should see it on the web UI
  //
  // TOBrien 20240410 Maybe I can put the delay up higher so I am calling the functions without the delays.
  // Have to wait to test.
  //
  // 3 Seconds  Testing
  //delay(3000);

  //Mathing the AP 
  delay(10000);
  // 3 Minutes  First Field Testing
  //delay(180000);
  // One hour
  //delay(3600000);

}

void myTime(){
//Updating the time here
//
// Trying to decide how I want to do this. I can either just send the entire date from RTC which would be the easy way
// I could also put it in the format that I want Year-Month-Day-HH:MM:SS and either send that as seperate fields 
// in the CSV file or at least order it based on the date and then time 

// I may start it out the easy way and then look at the data and see what I like, dislike 

  rtc.updateTime();
  if (rtc.updateTime() == true) //Updates the time variables from RTC
  {
      String logDate = rtc.stringDateUSA();
      String logTime = rtc.stringTime();

  }

  // 3 Seconds Testing
  //delay(3000);
  delay(10000);
  // 3 Minutes First field testing
  //delay(180000);
  // One hour
  //delay(3600000);
}


void DataManage(){
  // I think this is where I want to be able to manage files 
  // Roll Files based on size 
  // Can I date stamp them YearMonthDay.csv when they are rolled?
  // Should this run after or before the data section? 
}


