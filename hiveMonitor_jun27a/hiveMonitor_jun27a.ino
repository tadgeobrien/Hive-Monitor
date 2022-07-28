#include <HX711.h>
#include <OneWire.h>
#include <DallasTemperature.h>  //Does calculations and conversion.
//#include <WiFiNINA.h>


//Wifi Access Point need to be 8 Characters.
//char ssid[] = ""
//char pass[] = ""
//int keyIndex = 0;

//WiFiServer server(80);

//HX711 Wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;
HX711 scale;


// One Wire DS18bs20 wiring
#define ONE_WIRE_BUS 5 // Read is on pin 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature hiveTemp(&oneWire); // Set the variable sensors of inside hive temp

float Celcius = 0;
float Fahrenheit = 0;


void setup() {
  // put your setup code here, to run once:
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  hiveTemp.begin();
}

void loop() {
  // Need a TARE function ( add tare button???)
  
  
  //Check for weight at hour intervals 

  //Test line for weight every second.


  // Put Scale in sleep mode??



  //Check for Hive Temp at hour intervals 
  hiveTemp.requestTemperatures(); 
  Celcius=hiveTemp.getTempCByIndex(0);
  Serial.print(" F  ");
  Serial.println(Fahrenheit);
  delay(1000);  //Testing - This is in milliseconds so it is 5 seconds.
  
  //Test line for Hive Temp every second.





  //Check for Hive Humidity at hour intervals 

  //Test line for Hive Humidity every second.


  //Check for Outside Temp at hour intervals 
  
  //Test line for Outside Temp every second.


//// Onewire Hive Temperature

  


}
