#include <Wire.h>

#include <SparkFun_SHTC3.h>
SHTC3 humid;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
Serial.println("Testing Humidity");
Wire.begin();
humid.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

//Serial.print("RH = "); 
//Serial.print(humid.toPercent());                        // "toPercent" returns the percent humidity as a floating point number
//Serial.print("%, T = "); 
//Serial.print(humid.toDegF());                           // "toDegF" and "toDegC" return the temperature as a flaoting point number in deg F and deg C respectively 
//Serial.println(" deg F"); 

  Serial.println(humid.getMode());
    
    delay(1000);
}
