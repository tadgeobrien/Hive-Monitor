#include <HX711.h>
#include <OneWire.h>
#include <WiFiNINA.h>


//Wifi Access Point need to be 8 Characters.
char ssid[] = ""
char pass[] = ""
int keyIndex = 0;

WiFiServer server(80);

//HX711 Wiring
//DAT Pin 3

//CLK Pin 2


// One Wire DS18bs20 wiring



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // Need a TARE function
  
  //Check for weight at hour intervals 


  //Test line for weight every second.


  //Check for Temp at hour intervals 

  //Test line for Temp every second.


  //Check for Humidity at hour intervals 

  //Test line for Humidity every second.


}
