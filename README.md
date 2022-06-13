# Hive-Monitor
Creating a simple bee hive monitoring system for a public garden space. Likely using Arduino and maybe a Rasberry Pi. 

# Goal

Do you look at something like this for easy logging an implementation? [SparkFun OpenLog Artemis (without IMU)](https://www.sparkfun.com/products/19426). You then become a bit locked into a specific type of thing. Also would need to change to a board similar to the  [SparkFun Thing Plus - ESP32 WROOM (Micro-B)](https://www.sparkfun.com/products/15663)


# To Do
- [ ] Build a power profile and how to charge the battery. 
- [ ] Decide on whether to leverage QWICC from Sparkfun.
- [ ] Decide on where to put enclosure.
- [ ] Decide on wiring paths (think about how you will add/remove supers and lengths of cabling)



# BOM
* [Arduino Uno Wifi Rev 2](https://docs.arduino.cc/hardware/uno-wifi-rev2) Quantity 1
* [SparkFun Humidity Sensor Breakout - SHTC3 (Qwiic)](https://www.sparkfun.com/products/16467) Quantity 1
* [SparkFun Load Sensor Combinator](https://www.sparkfun.com/products/13878) Quantity 1
* [SparkFun Load Cell Amplifier - HX711](https://www.sparkfun.com/products/13879) Quantity 1
* [Load Sensor - 50kg (Generic)](https://www.sparkfun.com/products/10245) Quantity 4
* [Temperature Sensor - Waterproof (DS18B20)](https://www.sparkfun.com/products/11050) Quantity 1
* [SparkFun Air Quality Breakout - CCS811](https://www.sparkfun.com/products/14193) Quantity 1

# Physical Design Docs
Thinking this would be any CAD files or drawings. 


# Battery and Solar Requirements
* [LiFePO4 Battery](https://www.amazon.com/LiFePO4-Battery-Miady-Rechargeable-Maintenance-Free/dp/B089VXSBC6/?th=1) similar to this? 
* [Crowd Supply makerPower Solar](https://www.sparkfun.com/products/16352) seems like the right fit. Only question is how would it be designed for a lead battery vs. the lithium iron? 
* [SparkFun Sunny Buddy - MPPT Solar Charger](https://www.sparkfun.com/products/12885) Would this work at all? Designed for a single cell LiPo battery. 
* May need to have a lenght of cable for powering things. Not sure how I would do this. Most likely send the power from the panel to the inverter close to the actual sensors. 
