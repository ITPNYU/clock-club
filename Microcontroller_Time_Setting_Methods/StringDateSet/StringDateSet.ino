/*
  String Time Set

  This example uses data input from the serial port to set the time.
  The input string from the serial port should look like this:

  1/1/2020

  created 22 April 2018
  updated 9 Apr 2023
  by Tom Igoe
*/
#include <RTCZero.h>

RTCZero rtc;

void setup() {
  Serial.begin(9600);        // initialize serial communication
  if (!Serial) delay(3000);  // wait 3 seconds for serial monitor to open
  rtc.begin();
}

void loop() {
  // to get the time on a POSIX (MacOS, Linux, et. al) command line, type:
  // date "+%y-%m-%d"
  // this will give you a string formatted like so:
  // 23-04-09

  if (Serial.available() > 6) {     // full time string is 7 characters: YY:MM:DD
    int year = Serial.parseInt();   // convert day to an int
    int month = Serial.parseInt();  // convert month to an int
    int day = Serial.parseInt();    // convert year to an int
                                    // set the date:
    rtc.setDate(day, month, year);
  }

  // print the date every 5 seconds:
  if (rtc.getDay() < 10) Serial.print("0");  // leading zero
  Serial.print(rtc.getDay());
  Serial.print("/");
  if (rtc.getMonth() < 10) Serial.print("0");  // leading zero
  Serial.print(rtc.getMonth());
  Serial.print("/");
  if (rtc.getYear() < 10) Serial.print("0");  // leading zero
  Serial.println(rtc.getYear());
  delay(5000);
}
