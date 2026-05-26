//TOBRIEN 20260525 
// I think I am going to redo a lot of this. I am going to start with just the serial printing and getting logs to openlog.

//Hive Inside Temp and Humidity



// Hive Outside Temp.
#include <OneWire.h>            // Takes in the data.
#include <DallasTemperature.h>  //Does calculations and conversion.
#define ONE_WIRE_BUS 5  //READ IS ON PIN 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float OutCel=0; // Outside Temp in Celcius


// Openlog information.
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
OpenLog myLog;    // Declare an instance of the OpenLog class


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Reading the serial monitor.

  //Outside Temp
  sensors.begin();  // This is for OneWire using DallasTemp.

  
}

void loop() {
  //Wifi Stuff Will Go here someday
  
  //Hive Outside Temp.
  sensors.requestTemperatures(); 
  OutCel=sensors.getTempCByIndex(0);

//DATA FORMAT
      // Lets write some data to OpenLog Below is an example
        /*    DATE,TIME-24:00,% Humidity,InternalTemp(C),OutsideTemp(C),Weight(lbs)
            20240420,00:20,24,31,1,95
            20240420,01:20,24,31,1,95
            20240420,02:20,24,31,1,95
            20240420,03:20,24,31,1,95
      */



  // Sending to OpenLog
  myLog.begin();
  myLog.println(OutCel);// FOR ADDING WEIGHT WHEN READY

  


  // Serial Print 
  Serial.println((String("Outside Temp ")+OutCel));// FOR ADDING WEIGHT WHEN READY

  myLog.syncFile();


// This is what I was working on in the past. It seemed to work, but I may need to tweak it.
//  Serial.println(String(rtc.stringDateUSA())+","+String(rtc.stringTime())+","+String(mySHTC3.toPercent())+","+String(mySHTC3.toDegC())+","+String(OutCel)+","+String(scale.read()));// FOR ADDING WEIGHT WHEN READY

delay(3000);

}
