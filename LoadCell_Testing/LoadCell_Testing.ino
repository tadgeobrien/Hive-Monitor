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