//  Print temp to serial
//  Print time to serial
//  Log both to Openlog as CSV
//

#include <OneWire.h>  // Takes in the data.
#include <DallasTemperature.h>  //Does calculations and conversion.
#include <SparkFun_RV8803.h>  //Real Time Clock 
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>

//RTC Clock set up
RV8803 rtc; 


// One wire setup.
#define ONE_WIRE_BUS 5  //READ IS ON PIN 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float OutCel=0; // Outside Celcius tobrien 20240410. May simply implement this instead of conversions.

//Open Log
OpenLog mylogger;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  mylogger.begin();

}


////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  
  // put your main code here, to run repeatedly:
  rtc.updateTime();
  String myTime = rtc.stringTime();

  sensors.requestTemperatures();
  OutCel=sensors.getTempCByIndex(0); //Get Outside C from Onewire.

  Serial.print(myTime);
  Serial.print(",");
  Serial.print(OutCel,2);  //Uncomment for printing to serial monitor
  Serial.println(",WTF");

  
  
  mylogger.print("Outside C");
  mylogger.println(OutCel);
  mylogger.syncFile();

   // Serial1 is for printing to Openlog
  mylogger.print(myTime);
  mylogger.print(",");
  mylogger.print(OutCel,2);  //Uncomment for printing to serial monitor
  mylogger.println(",");

  delay(1000);  //Testing - This is in milliseconds so it is 1 seconds.

  
}

 
