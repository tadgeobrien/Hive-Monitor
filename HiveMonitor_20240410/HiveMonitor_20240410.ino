//T OBRIEN 20240409
// Taken from https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-web-server-ap-mode/
//
// So now can I modify this so that I am passing sensor data to the page? 
//
//  - Onewire is for external temperature of the hive. Still need to figure out
//    where I would want to put the sensor itself.
//


#include <WiFiNINA.h>  //Wifi Library
#include <OneWire.h>  // Takes in the data.
#include <DallasTemperature.h>  //Does calculations and conversion.

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

//LED Testing tobrien 20240410 keep or remove?
int led = LED_BUILTIN;
int status = WL_IDLE_STATUS;

//Defines server port.
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
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
      Serial.println("newe client");  // print a message out the serial port
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

              int randomReading = analogRead(A1);
              client.print("Random reading from analog pin: ");
              client.print(randomReading);

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

      OutsideTemp();  // This should be my function to check outside temp.
/*
  // TOBrien 20240410
  // Simple Onewire data print to serial.
  // Only doing Celcius at this point. Don't know if I want to implement Farenheit.TOBrien 20240410
  // Eventually need to make this so that I am sending this data every hour to the
  // Openlog SD card. 
  // TOBrien 20240410 Wondering if I can simply create a function with the delay that would then 
  // eliminate any potential sampling time problems?
  sensors.requestTemperatures();
  OutCel=sensors.getTempCByIndex(0); //Get Outside C from Onewire.
  Serial.print(" Outside C  ");
  Serial.println(OutCel);
  delay(1000);  //Testing - This is in milliseconds so it is 1 seconds.
  //delay(3600000);  //Production - This is 1 Hour. Also have a feeling that this messes up your sampling some how as it is in the void. 

*/
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
  Serial.print(" Outside C  ");
  Serial.println(OutCel);
  delay(1000);  //Testing - This is in milliseconds so it is 1 seconds.
  //delay(3600000);  //Production - This is 1 Hour. Also have a feeling that this messes up your sampling some how as it is in the void. 
}

  
