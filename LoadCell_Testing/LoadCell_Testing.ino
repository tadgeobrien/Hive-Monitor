#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2; //blue
const int LOADCELL_SCK_PIN = 3;  // white blue

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(1000);
  
}





/*
Some of the results

HX711 reading: -2052591
HX711 reading: -1669633
HX711 reading: -458928
HX711 reading: -126968
HX711 reading: -127797
HX711 reading: -127147
HX711 reading: -131626
HX711 reading: -127915
HX711 reading: -128087
HX711 reading: -127718
HX711 reading: -127512
HX711 reading: -127317

 */
