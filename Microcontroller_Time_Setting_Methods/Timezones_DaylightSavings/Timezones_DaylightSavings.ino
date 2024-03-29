/*

  A variety of time-setting methods:
    Setting the time from the network using WiFi.getTime
    Calculating local time from time zone
    Calculating day of week from epoch
    Calculating daylight savings time from time zone and epoch

  Circuit:
    Arduino MKR1000 or MKR1010, or Nano 33 IoT 
    (change to WiFiNINA library for the latter two)

  Add SECRET_SSID and SECRET_PASS constants in a separate arduino_secrets.h file.

  created 11 Mar 2019
  modified 9 Apr 2023
  by Tom Igoe
*/

#include <SPI.h>
// #include <WiFi101.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include "arduino_secrets.h"

RTCZero rtc;        // the realtime clock instance
int timeZone = -5;  // your time zone relative to UTC; -5 is US Eastern time

void setup() {
  Serial.begin(9600);
  // wait 3 seconds for serial monitor to open
  if (!Serial) delay(3000);

  // initialize the realtime clock:
  rtc.begin();

  // while you're not connected to a WiFi AP,
  // try to connect:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(SECRET_SSID);   // print the network name (SSID)
    WiFi.begin(SECRET_SSID, SECRET_PASS); // try to connect
    delay(2000);
  }

  // When you're connected, print out the device's network status:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // get the time from the network:
  unsigned long epoch;
  do {
    Serial.println("Trying to get time...");
    epoch = WiFi.getTime();
    delay(500);
  } while (epoch == 0);

  // print the epoch once you have it:
  Serial.print("Epoch received: ");
  Serial.println(epoch);
  rtc.setEpoch(epoch);

  // get the day of the week. Unix epoch time is the number of seconds
  // since Jan 1 1970. There are 86400 seconds in a day. So
  // days = epoch /86400, and day of week = days % 7. And
  // Jan 1 1970 was a Thursday, so add 4:

  int dayOfWeek = ((epoch / 86400) + 4) % 7;
  String dayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  Serial.print("Day of week: ");
  Serial.println(dayNames[dayOfWeek]);

  // if daylight savings, spring forward:
  timeZone = timeZone + daylightSavings(dayOfWeek);

  Serial.println("time difference from GMT: " + String(timeZone));
  // if the GMT hour value is greater than the timeZone difference:
  if (rtc.getHours() >= abs(timeZone)) {
    rtc.setHours(rtc.getHours() + timeZone);
    // if the GMT hour is less than the timeZone difference,
    // then you need to add 24 hours to it:
  } else {
    rtc.setHours(24 + rtc.getHours() + timeZone);
  }

  // print the time:
  Serial.print("Time: " );
  Serial.println(getTimeString(rtc.getHours(),
                               rtc.getMinutes(),
                               rtc.getSeconds()));
}

void loop() {

}

// get the time as a string HH:MM:SS:
String getTimeString(int h, int m, int s) {
  String now = "";
  if (h < 0) now += "0";
  now += h;
  now += ":";
  if (m < 0) now += "0";
  now += m;
  now += ":";
  if (s < 0) now += "0";
  now += s;
  return now;
}

// Calculate daylight savings days in the US.
// DST starts on the second Sunday in March
// and standard time starts on the first Sunday in November.

int daylightSavings(int weekDay) {
  int springForward = 0;
  //January, February, and December are standard time

  //April to October are daylight savings:
  if (rtc.getMonth() > 3 && rtc.getMonth() < 11) {
    springForward = 1;
  }
  // calculate the day of the month of the previous sunday
  // from today:
  int lastSunday = rtc.getDay() - weekDay;

  // In March, daylight savings starts on the second sunday,
  // i.e. after the 8th:
  if (rtc.getMonth() == 3 && lastSunday >= 8) {
    springForward = 1;
  }
  //In november we must be before the first sunday to be dst.
  //That means the previous sunday must be before the 1st.
  if (rtc.getMonth() == 11 && lastSunday <= 0) {
    springForward = 1;
  }
  return springForward;
}
