# Hive-Monitor
Creating a simple bee hive monitoring system for a public garden space. Likely using Arduino and maybe a Rasberry Pi. (Basically Modelling after this [Makezine Article](https://makezine.com/projects/bees-sensors-monitor-hive-health). [The data I would like to look like this](http://everettsprojects.com/2012/12/31/arduino-super-graphing-data-logger/). I would like it if I could set it up as a hotspot that people could click on the data to view it. Ie connect to 490hive wireless and be directed to www.home.arpa where you can choose what to see ie. Hive Weight Hive Temperature Hive Humidity for last N days. 

# Goal

Do you look at something like this for easy logging an implementation? [SparkFun OpenLog Artemis (without IMU)](https://www.sparkfun.com/products/19426). You then become a bit locked into a specific type of thing. Also would need to change to a board similar to the  [SparkFun Thing Plus - ESP32 WROOM (Micro-B)](https://www.sparkfun.com/products/15663)


# To Do
- [ ] Build a power profile and how to charge the battery. 
- [ ] Decide on whether to leverage QWICC from Sparkfun.
- [ ] Decide on where to put enclosure. I think that mounting it to the hive base or in the quilt box would be the best option. If it is in the quilt box then the length for the load cells will be the longest. Likely look at using an rj45 to do that connection and running the wires back up. Should be able to do the load cell on a single rj45 cable. 
- [ ] Decide on wiring paths (think about how you will add/remove supers and lengths of cabling)



# BOM
I think I need to adjust this. Thinking more along the lines of QWIIC since it might be easier, even though it won't neccesarily be cheaper. 

* [Arduino Uno Wifi Rev 2](https://docs.arduino.cc/hardware/uno-wifi-rev2) Quantity 1
* [SparkFun Humidity Sensor Breakout - SHTC3 (Qwiic)](https://www.sparkfun.com/products/16467) Quantity 1
* [SparkFun Load Sensor Combinator](https://www.sparkfun.com/products/13878) Quantity 1
* [SparkFun Load Cell Amplifier - HX711](https://www.sparkfun.com/products/13879) Quantity 1
* [Load Sensor - 50kg (Generic)](https://www.sparkfun.com/products/10245) Quantity 4
* [Temperature Sensor - Waterproof (DS18B20)](https://www.sparkfun.com/products/11050) Quantity 1
* [SparkFun Air Quality Breakout - CCS811](https://www.sparkfun.com/products/14193) Quantity 1
* [SparkFun OpenScale](https://www.sparkfun.com/products/13261)

# Physical Design Docs
Thinking this would be any CAD files or drawings. 

# General Design Questions per Sensor or piece.
Thinking if you use RJ45 as connectors you'd want to look at [waterproof enclosures](https://www.amazon.com/Waterproof-Connector-Shielded-Ethernet-Tedgetal/dp/B095JZSGYG). [waterproof enclosure](https://www.homedepot.com/p/Revo-RJ45-Female-to-Female-Waterproof-IP-67-Outdoor-Coupler-ONC-1/310016205)

## Battery and Solar Requirements
* [LiFePO4 Battery](https://www.amazon.com/LiFePO4-Battery-Miady-Rechargeable-Maintenance-Free/dp/B089VXSBC6/?th=1) similar to this? 
* [Crowd Supply makerPower Solar](https://www.sparkfun.com/products/16352) seems like the right fit. Only question is how would it be designed for a lead battery vs. the lithium iron? 
* [SparkFun Sunny Buddy - MPPT Solar Charger](https://www.sparkfun.com/products/12885) Would this work at all? Designed for a single cell LiPo battery. 
* May need to have a lenght of cable for powering things. Not sure how I would do this. Most likely send the power from the panel to the inverter close to the actual sensors. (4mm pv cable for solar power. It is DC) I think that the distance would be about 20 feet or so for this application. Othe concerns would be grounding.


## Load Cells Requirements


## Temperature and Humidity Requirements
* Needs to be able to measure both of these and I am thinking of placing them on the top of the hive. Would like to understand how best to build the enclosure to get decent readings. 


