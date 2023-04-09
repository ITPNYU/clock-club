/*
  String Time Set

  This example uses data input from the serial port to set the time.
  The input string from the serial port should look like this:

  09:55:33

  to get the time on a POSIX (MacOS, Linux, et. al) command line, type:
  date "+%H:%M:%S"
  this will give you a string formatted like the compiler __TIME__ string

  created 22 April 2018
  updated 9 Apr 2023
  by Tom Igoe
*/
#include <RTCZero.h>

RTCZero rtc;
int lastSecond = 0;

void setup() {
  Serial.begin(9600);  // initialize serial communication
  // wait 3 secs for serial monitor to open:
  if (!Serial) delay(3000);
  rtc.begin();
}

void loop() {
  // to get the time on a POSIX (MacOS, Linux, et. al) command line, type:
  // date "+%H:%M:%S"
  // this will give you a string formatted like so:
  // 11:34:56

  if (Serial.available() > 6) {       // full time string is 7 characters: HH:MM:SS
    int hours = Serial.parseInt();    // convert hours to an int
    int minutes = Serial.parseInt();  // convert minutes to an int
    int seconds = Serial.parseInt();  // convert seconds to an int
    // set the time:
    rtc.setTime(hours, minutes, seconds);
  }

  // print the date every second:
  if (rtc.getSeconds() != lastSecond) {
    if (rtc.getHours() < 10) Serial.print("0");  // leading zero
    Serial.print(rtc.getHours());
    Serial.print(":");
    if (rtc.getMinutes() < 10) Serial.print("0");  // leading zero
    Serial.print(rtc.getMinutes());
    Serial.print(":");
    if (rtc.getSeconds() < 10) Serial.print("0");  // leading zero
    Serial.println(rtc.getSeconds());
    // timestamp for next time through the loop:
    lastSecond = rtc.getSeconds();
  }
}
