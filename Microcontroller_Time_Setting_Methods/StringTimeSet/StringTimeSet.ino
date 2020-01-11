/*
  String Time Set

  This example uses data input from the serial port to set the time.
  The input string from the serial port should look like this:

  09:55:33

  to get the time on a POSIX (MacOS, Linux, et. al) command line, type:
  date "+%H:%M:%S"
  this will give you a string formatted like the compiler __TIME__ string

  created 22 April 2018
  updated 11 Jan 2020
  by Tom Igoe
*/
// time
int hours = 0;
int minutes = 0;
int seconds = 0;
long lastCount = 0; // count of millis since last second

void setup() {
  Serial.begin(9600);   // initialize serial communication
  while (!Serial);      // stop everything until serial monitor is open
  Serial.setTimeout(10);
}

void loop() {
  // to get the time on a POSIX (MacOS, Linux, et. al) command line, type:
  // date "+%H:%M:%S"
  // this will give you a string formatted like the compiler __TIME__ string:

  if (Serial.available() > 8) {   // full time string is 8 characters: HH:MM:SS
    hours = Serial.parseInt();    // convert hours to an int
    minutes = Serial.parseInt();  // convert minutes to an int
    seconds = Serial.parseInt();  // convert seconds to an int
  }

  // count the milliseconds, update second when 1000ms have passed:
  if (millis() - lastCount > 1000) {
    seconds++;
    lastCount = millis();

    if (seconds > 59) {   // rollover seconds and update minutes
      seconds = 0;
      minutes++;
    }
    if (minutes > 59) {   // rollover minutes and update hours
      minutes = 0;
      hours++;
    }
    if (hours > 23) {     // rollover hours
      hours = 0;
    }
    // print the time:
    if (hours < 10) Serial.print("0");    // leading zero
    Serial.print(hours);
    Serial.print(":");
    if (minutes < 10) Serial.print("0");  // leading zero
    Serial.print(minutes);
    Serial.print(":");
    if (seconds < 10) Serial.print("0");  // leading zero
    Serial.println(seconds);
  }
}
