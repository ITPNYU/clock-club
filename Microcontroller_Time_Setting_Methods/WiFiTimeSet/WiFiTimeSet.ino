/*

    Setting the time using WiFi.getTime();

    WiFi.getTime() connects to network time servers and gets the
    UNIX epoch (seconds since 1/1/1970, 00:00:00). It then sets
    the realtime clock epoch with that time

    Works on MKR1000, MKR1010, Nano 33 IoT

    Make sure to add a file, arduino_secrets.h, with:
    #define SECRET_SSID ""    //  your network SSID (name)
    #define SECRET_PASS ""    // your network passwordx

    created 30 April 2019
    modified 26 Apr 2021
    by Tom Igoe
*/
#include <SPI.h>
//#include <WiFi101.h>    // use this for MKR1000
#include <WiFiNINA.h> // use this for MKR1010
#include <RTCZero.h>
#include "arduino_secrets.h"

RTCZero rtc;
int reconnects = 0; // how many times you've reconnected to the network
int lastSecond;     // last second value, for watching passing seconds

unsigned long startTime;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);
  rtc.begin();
  connectToNetwork();
}

void loop() {
  // if you disconnected from the network, reconnect:
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    connectToNetwork();
  }

  // when the second has changed, print the time:
  if (rtc.getSeconds() != lastSecond) {
    Serial.print(getTimeStamp());
    Serial.println(" " + getDateStamp());
    lastSecond = rtc.getSeconds();
    // get the total uptime of the device:
    Serial.println(getUptime(1));
  }
}


void connectToNetwork() {
  // try to connect to the network:
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect to: " + String(SECRET_SSID));
    //Connect to WPA / WPA2 network:
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(2000);
  }
  Serial.println("connected to: " + String(SECRET_SSID));
  // You're connected, turn on the LED:
  digitalWrite(LED_BUILTIN, HIGH);

  // set the time from the network:
  unsigned long epoch;
  do {
    Serial.println("Attempting to get network time");
    epoch = WiFi.getTime();
    delay(2000);
  } while (epoch == 0);

  rtc.setEpoch(epoch);
  startTime = epoch;

  // increment the reconnect count:
  reconnects++;
  Serial.println(getTimeStamp());
  IPAddress ip = WiFi.localIP();
  Serial.print(ip);
  Serial.print("  Signal Strength: ");
  Serial.println(WiFi.RSSI());
}


// format the time as hh:mm:ss
String getTimeStamp() {
  String timestamp = "";
  if (rtc.getHours() <= 9) timestamp += "0";
  timestamp += rtc.getHours();
  timestamp += ":";
  if (rtc.getMinutes() <= 9) timestamp += "0";
  timestamp += rtc.getMinutes();
  timestamp += ":";
  if (rtc.getSeconds() <= 9) timestamp += "0";
  timestamp += rtc.getSeconds();
  timestamp += " GMT";
  return timestamp;
}


// format the time as hh:mm:ss
String getDateStamp() {
  String timestamp = "";
  if (rtc.getDay() <= 9) timestamp += "0";
  timestamp += rtc.getDay();
  timestamp += "/";
  if (rtc.getMonth() <= 9) timestamp += "0";
  timestamp += rtc.getMonth();
  timestamp += "/";
  if (rtc.getYear() <= 9) timestamp += "0";
  timestamp += rtc.getYear();
  return timestamp;
}


// format uptime:
String getUptime(int format) {
  unsigned long upNow = rtc.getEpoch() - startTime;
  int upSecs = upNow % 60;
  int upMins = (upNow % 3600L) / 60;
  int upHours = (upNow % 86400L) / 3600;
  int upDays = (upNow % 31556926L) / 86400L;
  String uptime = format2Digits(upDays);
  if (format == 0) { // short
    uptime += ":";
    uptime += format2Digits(upHours);
    uptime += ":";
    uptime += format2Digits(upMins);
    uptime += ":";
    uptime += format2Digits(upSecs);
  } else { // long
    uptime += " days, ";
    uptime += format2Digits(upHours);
    uptime += ": ";
    uptime += format2Digits(upMins);
    uptime += ": ";
    uptime += format2Digits(upSecs);
  }
  return uptime;
}

// format digit string:
String format2Digits(int number) {
  String result = "";
  if (number < 10) {
    result += "0";
  }
  result += String(number);
  return result;
}
