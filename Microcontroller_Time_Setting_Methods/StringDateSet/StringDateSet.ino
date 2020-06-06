/*
  String Time Set

  This example uses data input from the serial port to set the time.
  The input string from the serial port should look like this:

  1/1/2020

  created 22 April 2018
  updated 11 Jan 2020
  by Tom Igoe
*/
#include <RTCZero.h>
// time
int day = 0;
int month = 0;
int year = 0;
long lastCount = 0; // count of millis since last second

RTCZero rtc;

void setup() {
  Serial.begin(9600);   // initialize serial communication
  while (!Serial);      // stop everything until serial monitor is open
  Serial.setTimeout(10);
  rtc.begin();
}

void loop() {
  // to get the time on a POSIX (MacOS, Linux, et. al) command line, type:
  // date "+%H:%M:%S"
  // this will give you a string formatted like the compiler __TIME__ string:

  if (Serial.available() > 8) {   // full time string is 8 characters: HH:MM:SS
    day = Serial.parseInt();    // convert day to an int
    month = Serial.parseInt();  // convert month to an int
    year = Serial.parseInt();  // convert year to an int

    rtc.setDate(day, month, year);
    // print the date:
    if (rtc.getDay() < 10) Serial.print("0");    // leading zero
    Serial.print(rtc.getDay());
    Serial.print("/");
    if (rtc.getMonth() < 10) Serial.print("0");  // leading zero
    Serial.print(rtc.getMonth());
    Serial.print("/");
    if (rtc.getYear() < 10) Serial.print("0");  // leading zero
    Serial.println(rtc.getYear());
  }
}
