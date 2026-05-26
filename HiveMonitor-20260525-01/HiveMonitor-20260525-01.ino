//TOBRIEN 20260525 
// I think I am going to redo a lot of this. I am going to start with just the serial printing and getting logs to openlog.

// Wifi Library
#include <WiFiNINA.h>


//Real Time Clock
#include <SparkFun_RV8803.h>


//Hive Inside Temp and Humidity
#include <SparkFun_SHTC3.h>     //Using for inside Humidity and Temp
SHTC3 mySHTC3;    // Declare an instance of the SHTC3 class

//float InCel=0;  // Inside Celcius temp
//float InFah=0;  // Inside Farenheit May not use.
//float InHum=0;  // Inside Humidity 


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

  //Inside Hive Temp
  Wire.begin();  // Dependency for SHTC3 Sensor.
  mySHTC3.begin();  // This calls the SHTC3 sensor to start


  //Outside Hive Temp
  sensors.begin();  // This is for OneWire using DallasTemp.



  
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  //Wifi Stuff Will Go here someday


  // Inside Hive Inside Temp and Humidity
  SHTC3_Status_TypeDef result = mySHTC3.update(); //Update the sensor


  
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
  myLog.println(String(mySHTC3.toPercent())+","+String(mySHTC3.toDegC())+","+(OutCel));// FOR ADDING WEIGHT WHEN READY


  // Serial Print 
  Serial.println("Inside Humidity Percent "+String(mySHTC3.toPercent())+", Inside Degrees Cel "+String(mySHTC3.toDegC())+","+(String("Outside Temp C.")+OutCel));// FOR ADDING WEIGHT WHEN READY

  myLog.syncFile();

// This is what I was working on in the past. It seemed to work, but I may need to tweak it.
//  Serial.println(String(rtc.stringDateUSA())+","+String(rtc.stringTime())+","+String(mySHTC3.toPercent())+","+String(mySHTC3.toDegC())+","+String(OutCel)+","+String(scale.read()));// FOR ADDING WEIGHT WHEN READY

delay(3000); // TOBrien 20260525 Eventually I think I have to change this.

}
