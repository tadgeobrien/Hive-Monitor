# Development Log

20250703 @ 18:02 - 
  TOBrien made a copy of the old hive monitor from 2024 and tried to get the weight to print. Currenlty not getting weight to print, but also appears that the one wire (external temp) is broken as I am seeing 
  -127 as a value. It was working before, but I have no idea what code I was actually running. I think I am going to make a text weight set of code and see if I can get that working with out anything else. 


# Hive Montitor

NOTE--- I used the Sparkfun Qwiic shield which was originaly designed for the Uno. However the Uno Wifi Rev2 that I have has two pins that are different. 
        So to solve this the following has to be done. (https://forum.sparkfun.com/viewtopic.php?f=105&t=56000&p=227024&hilit=qwiic+shield+Qwiic+Shield+Uno+WiFi+V2#p227642)
        
        The pins not going in all the way is normal, it's caused by the USB connector being higher than normal.
        We haven't tested the Qwiic Shield on the Uno WiFi V2 but it should work with this small change:
            Connect a jumper wire from A5 to SCL
            Connect a jumper wire from A4 to SDA

        The reason for the jumper wires is that the shield was made for the regular non WiFi Uno where the I2C pins are on A4 and A5 and the Uno WiFi V2 moves those pins over to the other side of the board. With the jumpers in place, the shield will work even though it doesn't sit flush with the Arduino. 

Of course now they have the Uno R4 Wifi which has a Qwiic connector built in GRRRR https://store-usa.arduino.cc/products/uno-r4-wifi .

## Goal

Create a simple set of sensors to monitor a beehive of mine. It will be solar powered and not connected to any network. 
The sensors that I will be using are as follows:
* Weight Measure
* Inside Temperature and Humidity Measure
* Outside Temperature Measure

## To Dos
- [ ] Do I need a way to update the current data on the webpage from the webpage without adding to the Openlog file?
- [ ] Implement Weight measures (may leave with weight errors currently.) https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all#installing-the-hx711-arduino-library-and-examples https://github.com/bogde/HX711/
- [ ] Implement battery power reading on webpage and openlog?
- [ ] Implement solar power 
- [ ] Implement way to download Data from web page
- [ ] Have RTC implemented on website
- [X] Have Openlog recieving all current values of data
- [X] Have Openlog implemented and getting data
- [X] Have RTC working
- [X] Have Inside temp and humidity report on website
- [X] Have Inside humidity working
- [X] Have Inside temp working 
- [X] Have Outside temp appear on webpage.
- [X] Set up Onewire for outside temperature 
- [X] Set up an Webserver and wireless connection to the Arduino. 



## CSV Structure

CSV Structure should look like this. 
(24 entries per day and role log monthly would give at most 744 points of data.)
Could scale up if needed in the future.

Not sure if the date will go as I want, but I should try. Also not sure exactly if I would want it like
this or break it out Year,Month,Day,Hour,Minute,

DATE,TIME-24:00,% Humidity,InternalTemp(C),OutsideTemp(C),Weight(lbs)
20240420,00:20,24,31,1,95
20240420,01:20,24,31,1,95
20240420,02:20,24,31,1,95
20240420,03:20,24,31,1,95
20240420,04:20,24,31,1,95
20240420,05:20,24,31,1,95
20240420,06:20,24,31,1,95
20240420,07:20,24,31,1,95
20240420,08:20,24,31,1,95
20240420,09:20,24,31,1,95
20240420,10:20,24,31,1,95
20240420,11:20,24,31,1,95
20240420,12:20,24,31,1,95
20240420,13:20,24,31,1,95
20240420,14:20,24,31,1,95
20240420,15:20,24,31,1,95
20240420,16:20,24,31,1,95
20240420,17:20,24,31,1,95
20240420,18:20,24,31,1,95
20240420,19:20,24,31,1,95
20240420,20:20,24,31,1,95
20240420,21:20,24,31,1,95
20240420,22:20,24,31,1,95
20240420,23:20,24,31,1,95
  
### CSV Example 20250703  
07/03/2025,17:37:23,72.45,23.56,23.00,weigth
07/03/2025,17:37:43,72.44,23.55,23.00,weigth
07/03/2025,17:38:04,72.43,23.52,23.00,weigth
07/03/2025,17:38:25,72.41,23.52,23.00,weigth
07/03/2025,17:38:45,72.38,23.52,22.94,weigth
07/03/2025,17:39:06,72.36,23.52,23.00,weigth
07/03/2025,17:39:26,72.42,23.51,23.00,weigth
07/03/2025,17:39:47,72.45,23.51,23.00,weigth
07/03/2025,17:40:08,72.43,23.53,23.00,weigth

  */

# I2C addresses in Use
I think I need to verify all of these, but I don't think that this is why OpenLog isn't working. 
* RTC 0x32
* OpenLog 0x2A (42)

# Arduino Code

## Variables
* OutCel is for outside temperature in Celsius.
* OutFah is for the outside temp in Farenheit. May not even implement this to start.
* InCel is for the inside temperature coming from the humidity sensor in Celsius
* InFah is for the inside temperature coming from the humidity sensor in Farenheit. May not even implement to start.
* InHum is for the inside humidity. Not sure of the measurement.

## Functions
* void printWiFiStatus()
* void OutsideTemp()
* void InsideTemp()
* void InsideHumidity()

## Pinouts

# Hardware Notes

## Bill of Materials (BOM)
Maybe I should make this a table :)

* Arduino Uno Wifi R2
* [Real Time Clock Sparkfun BOB-16281](https://learn.sparkfun.com/tutorials/real-time-clock-module---rv-8803-qwiic-hookup-guide)
* [Humidity Sensor SparkFun SEN-16467](https://learn.sparkfun.com/tutorials/sparkfun-humidity-sensor-breakout---shtc3-qwiic-hookup-guide)
* Onewire Temperature sensor
* [Sparkfun Qwiix OpenLog](https://learn.sparkfun.com/tutorials/qwiic-openlog-hookup-guide)
* Sparkfun QWICC shield for Arduino
* Load Cells

### OLD BOM Stuff
* [Arduino Uno Wifi Rev 2](https://docs.arduino.cc/hardware/uno-wifi-rev2) Quantity 1
* [SparkFun Load Sensor Combinator](https://www.sparkfun.com/products/13878) Quantity 1
* [SparkFun Load Cell Amplifier - HX711](https://www.sparkfun.com/products/13879) Quantity 1
* [Load Sensor - 50kg (Generic)](https://www.sparkfun.com/products/10245) Quantity 4
* [Temperature Sensor - Waterproof (DS18B20)](https://www.sparkfun.com/products/11050) Quantity 1
* [SparkFun Air Quality Breakout - CCS811](https://www.sparkfun.com/products/14193) Quantity 1
* 4 - [Load Sensor](https://www.sparkfun.com/products/10245) Double check what weight I ordered.
* 1 - [SparkFun Load Sensor Combinator](https://www.sparkfun.com/products/13878) Also can have a DS18B20 wired in to measure temperature for variance. Maybe helpful for the graphing in winter. Not sure how to configure that part of it yet.
* 1 - [SparkFun Load Cell Amplifier - HX711](https://www.sparkfun.com/products/13879)




# Load Cell Notes

Note: If you are hooking together four of the SparkFun Load Sensors using the Combinator board, you should position the four load sensors equidistant from each other, just like the bathroom scales shown in this tutorial.


## Load Cell Wiring
For load sensors, there isn't a set color coded standard. The hacked home scale can have different wire colors. Comparing the scale pictured above with the load sensor schematic, while the black wires matched, the red and white wires were swapped. Also, only two of the four sensors used a white wire for the 'center tap' of the load sensor, the other two used green. I connected the black wires to "-", the red to "+", and the white and green wires to "C".

To determine how to hook up your single strain gauge load cells to the combinator, measure the resistance with a multimeter between the three wires. You should find a larger resistance (close to double) between a pair. In our example, the resistance between red and black was 1.6 kΩ (i.e. 1600Ω), and the resistance between white/green and red was 800 Ω. Therefore, the center tap to the strain gauge is the white/green wire. The center tap or center pin of your strain gauge connects to the "C" pin on the combinator. The larger resistance wires (red and black in this example) connect to the "+" and "-" pins on the combinator.


## Tutorials
* [Load cell](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide?_ga=2.251188806.1397592904.1630879153-851011404.1618400912)




# OLD INFO BELOW Pre 20240410

# Hive-Monitor
Creating a simple bee hive monitoring system for a public garden space. Likely using Arduino and maybe a Rasberry Pi. (Basically Modelling after this [Makezine Article](https://makezine.com/projects/bees-sensors-monitor-hive-health). [The data I would like to look like this](http://everettsprojects.com/2012/12/31/arduino-super-graphing-data-logger/). I would like it if I could set it up as a hotspot that people could click on the data to view it. Ie connect to 490hive wireless and be directed to www.home.arpa where you can choose what to see ie. Hive Weight Hive Temperature Hive Humidity for last N days. 

Alternate ways to [view data..](https://www.electronicsforu.com/electronics-projects/graphical-data-display-arduino-html5).

# Goal

Do you look at something like this for easy logging an implementation? [SparkFun OpenLog Artemis (without IMU)](https://www.sparkfun.com/products/19426). You then become a bit locked into a specific type of thing. Also would need to change to a board similar to the  [SparkFun Thing Plus - ESP32 WROOM (Micro-B)](https://www.sparkfun.com/products/15663)


# To Do
- [ ] Build a power profile and how to charge the battery. 
- [ ] Decide on whether to leverage QWICC from Sparkfun.
- [ ] Decide on where to put enclosure. I think that mounting it to the hive base or in the quilt box would be the best option. If it is in the quilt box then the length for the load cells will be the longest. Likely look at using an rj45 to do that connection and running the wires back up. Should be able to do the load cell on a single rj45 cable. 
- [ ] Decide on wiring paths (think about how you will add/remove supers and lengths of cabling)



# BOM
I think I need to adjust this. Thinking more along the lines of QWIIC since it might be easier, even though it won't neccesarily be cheaper. 
(SEE FILE)

## OLD BOM Stuff
* [Arduino Uno Wifi Rev 2](https://docs.arduino.cc/hardware/uno-wifi-rev2) Quantity 1
* [SparkFun Load Sensor Combinator](https://www.sparkfun.com/products/13878) Quantity 1
* [SparkFun Load Cell Amplifier - HX711](https://www.sparkfun.com/products/13879) Quantity 1
* [Load Sensor - 50kg (Generic)](https://www.sparkfun.com/products/10245) Quantity 4
* [Temperature Sensor - Waterproof (DS18B20)](https://www.sparkfun.com/products/11050) Quantity 1
* [SparkFun Air Quality Breakout - CCS811](https://www.sparkfun.com/products/14193) Quantity 1

# Physical Design Docs
Thinking this would be any CAD files or drawings. 

# General Design Questions per Sensor or piece.
Thinking if you use RJ45 as connectors you'd want to look at [waterproof enclosures](https://www.amazon.com/Waterproof-Connector-Shielded-Ethernet-Tedgetal/dp/B095JZSGYG). [waterproof enclosure](https://www.homedepot.com/p/Revo-RJ45-Female-to-Female-Waterproof-IP-67-Outdoor-Coupler-ONC-1/310016205)

## Battery and Solar Requirements
* [LiFePO4 Battery](https://www.amazon.com/LiFePO4-Battery-Miady-Rechargeable-Maintenance-Free/dp/B089VXSBC6/?th=1) similar to this? 
* [Crowd Supply makerPower Solar](https://www.sparkfun.com/products/16352) seems like the right fit. Only question is how would it be designed for a lead battery vs. the lithium iron? 
* [SparkFun Sunny Buddy - MPPT Solar Charger](https://www.sparkfun.com/products/12885) Would this work at all? Designed for a single cell LiPo battery. 
* May need to have a lenght of cable for powering things. Not sure how I would do this. Most likely send the power from the panel to the inverter close to the actual sensors. (4mm pv cable for solar power. It is DC) I think that the distance would be about 20 feet or so for this application. Othe concerns would be grounding.

* [Open Source Solar System](https://opensource.com/article/22/12/open-source-solar-power-home) Just some notes on a solar system.


## Load Cells Requirements
In the one from Sparkfun he hacks a premade scale. I could go to a second hand store or buy one from amazon. I already have 4 load cells. So I could try to build a simple one with a square piece of plywood and some pressure treated 2x4s. I would build the square and put the cells in the corners then mount this inside of the hive stand. The accuracy of this is the biggest question. 

## Temperature and Humidity Requirements
* Needs to be able to measure both of these and I am thinking of placing them on the top of the hive. Would like to understand how best to build the enclosure to get decent readings. 

# Libraries Used

* [HXHX711 Arduino Library](https://github.com/bogde/HX711)
* [OneWire](https://www.arduino.cc/reference/en/libraries/onewire/)




# References Used
Here is a list of things like Youtube videos that I used for reference.

[Arduino Scale with HX711 and 50kg Bathroom Scale Load Cells | Step by Step Guide.](https://www.youtube.com/watch?v=LIuf2egMioA)

[Load Cell Amplifier HX711 Breakout Hookup Guide ](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide)


====

# Older Stuff from initial hive spy project.

# Maybe Helpful
* https://github.com/fubar2/piloadcell


# Wireless AP part
I want to make it so that basically it broadcasts an SSID that you can connect to and see what the Hive Spy has been collecting.

https://raspap.com/

or HospAPD  (This is likely going to be around longer I would think.)
https://learn.adafruit.com/setting-up-a-raspberry-pi-as-a-wifi-access-point/compiling-hostapd?view=all
https://hawksites.newpaltz.edu/myerse/2018/06/08/hostapd-on-raspberry-pi/
https://www.instructables.com/Raspberry-Pi-Wifi-Hotspot/


# Links for File Download

https://forum.arduino.cc/t/file-download-with-arduino-web-server/160140
https://forum.arduino.cc/t/download-files-on-the-wifiwebserver/692379

