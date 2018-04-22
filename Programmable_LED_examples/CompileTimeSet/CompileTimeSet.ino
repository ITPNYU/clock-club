/*
  Compile Time Set

  The C compiler used by the Arduino IDE has two special strings,
  __TIME__ and __DATE__. These return the time and date of the computer
  that compiled the sketch (i.e. your laptop). The strings look like this:

  09:55:33
  Apr 22 2018

  created 28 May 2016
  updated 22 April 2017
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

  // get the time from the compiler. __TIME__ returns
  // a string of the time the sketch was compiled, as hh:mm:ss
  // this routine takes the substrings, hh, mm, and ss and converts
  // them to integers:
  String compileTime = __TIME__;
  Serial.println(__TIME__);
  Serial.println(__DATE__);
  hours = compileTime.substring(0, 2).toInt();    // convert hours to an int
  minutes = compileTime.substring(3, 5).toInt();  // convert minutes to an int
  seconds = compileTime.substring(6, 8).toInt();  // convert seconds to an int
}

void loop() {
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
    if (hours > 12) {     // rollover hours
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


