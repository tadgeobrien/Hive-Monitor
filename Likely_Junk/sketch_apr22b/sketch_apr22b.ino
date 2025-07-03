


//  #include libraries for 
//    RTC qwiic
//    OpenLog qwiic
//    SHTC3 Humidity Temp qwiic
//    Onewire
//    Dallas
//    Serial
//    Wire



//Declare any Classes
RV1805 rtc;       // Declare an instance of the RV1805 class
SHTC3 mySHTC3;    // Declare an instance of the SHTC3 class
OpenLog myLog;    // Declare an instance of the OpenLog class


//Declare any ...


void setup() {
  // put your setup code here, to run once:


  //Set any start code
  Serial.begin(9600);
  Serial.println("Hive Monitoring Starting...")

}

void loop() {
  // put your main code here, to run repeatedly:
  
/* 
  Update the Humidity and temperature on the SHTC3
  Update the Temp on the Onewire
  Update the weight on the scale
  Get the time.
  Write all of this to OpenLog along with a date stamp
  
  Sleep for an hour and do it all again.

  When I get to X size or X date log roll my log and start a new file?
  Think I would like a new date. Monthly logs would be nice then I am only dealing with 12 files a year.

*/

/*
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
  


  */
  
}