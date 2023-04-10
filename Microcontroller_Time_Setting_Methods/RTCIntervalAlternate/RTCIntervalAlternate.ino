/*
  Waiting for a random interval in seconds, using the RTC
  The setAlarmTime function in the RTCZero library only allows
  for matching once a minute, at the most frequent. Sometimes you need
  to match once every few seconds. This shows you how. 
 
 created  9 Apr 2023
 by Tom Igoe
 */

#include <RTCZero.h>

RTCZero rtc;  // library for the Realtime Clock

// the interval between reads:
const int interval = 7;
// the last time you read, in seconds:
int lastSecond = 0;
int elapsedTime = 0;

void setup() {
  // start serial:
  Serial.begin(9600);
  // wait 3 seconds for serial port to open:
  if (!Serial) delay(3000);
  // start the realtime clock:
  rtc.begin();
  rtc.setTime(0, 0, 43);
}

void loop() {
  // get the current seconds:
  int thisSecond = rtc.getSeconds();
  // check for change:
  int change = thisSecond - lastSecond;
  // if the change is negative, combine the remainder of
  // the last minute and what's passed of this minute:
  if (change < 0) {
    change = (60 - lastSecond) + thisSecond;
  }
  // see if the interval has passed:
  if (change >= interval) {
    Serial.print(interval);
    Serial.print(" seconds have passed. Current second: ");
    Serial.println(thisSecond);
    // update lastSecond:
    lastSecond = thisSecond;
  }
}
