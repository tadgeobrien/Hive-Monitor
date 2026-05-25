// Taken from 
// https://create.arduino.cc/projecthub/iotboys/how-to-use-ds18b20-water-proof-temperature-sensor-2adecc
// https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806

#include <OneWire.h>  // Takes in the data.
#include <DallasTemperature.h>  //Does calculations and conversion.

#define ONE_WIRE_BUS 5  //READ IS ON PIN 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celcius=0;
float Fahrenheit=0;
void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
}

void loop(void)
{ 
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);
  // Removing Celcius from Production. I wouldn't use it but someone else might.
  // Likely have to work through the Python code to make it more functional.
  //Serial.print(" C  "); 
  //Serial.print(Celcius);
  Serial.print(" F  ");
  Serial.println(Fahrenheit);
  delay(1000);  //Testing - This is in milliseconds so it is 5 seconds.
  //delay(300000);  //Production - This is 5 minutes
}

// Could you print the actual values to a file/database that would bulid RRD type graphs?
// Have it printing via Python see /c/Users/to'brien/Documents/Git-Projects/Arduino/Aquaponics/reading-serial.py
