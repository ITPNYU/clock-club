/*

    Setting the time using WiFi.getEpoch();

    WiFi.getEpoch() connects to network time servers and gets the
    UNIX epoch (seconds since 1/1/1970, 00:00:00). It then sets
    the realtime clock epoch with that time. Once an hour it checks to see
    how much the time has drifted from the network time.

    Works on MKR1000, MKR1010

    Make sure to add a file, arduino_secrets.h, with:
    #define SECRET_SSID ""    //  your network SSID (name)
    #define SECRET_PASS ""    // your network password

    created 29 May 2019
    by Tom Igoe
*/
#include <SPI.h>
//#include <WiFi101.h>    // use this for MKR1000
#include <WiFiNINA.h> // use this for MKR1010
#include <RTCZero.h>
#include <SD.h>
#include "arduino_secrets.h"

#define SD_CHIP_SELECT 4

RTCZero rtc;
unsigned long epoch;      // the network time epoch
unsigned long drift = 0;  // number of seconds of RTC clock drift
int reconnects = 0;       // how many times you've reconnected to the network

// log file to write to on the SD card:
String logFile = "DATALOG.CSV";
// whether the SD card is accessible
bool SDAvailable = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);

  // initialize SD card:
  SDAvailable = SD.begin(SD_CHIP_SELECT);
  // print to serial port to check if card is working:
  Serial.println("Card present: " + String(SDAvailable));
  // if card is working, print to it. otherwise, print to serial:
  if (SDAvailable) {
    File dataFile = SD.open(logFile, FILE_WRITE);
    dataFile.print("RTC date:,");
    dataFile.print("RTC time:,");
    dataFile.println("RTC epoch:,");
    dataFile.println("Network epoch:,");
    dataFile.println("Time drift (seconds):");
    dataFile.close();
  }
  rtc.begin();
  connectToNetwork();
  if (rtc.getEpoch() > 0) {
    // set alarm time:
    rtc.setAlarmTime(0, 0, 0);
    // set alarm to go off hourly:
    rtc.enableAlarm(rtc.MATCH_MMSS);
    // set alarm interrrupt:
    rtc.attachInterrupt(checkDrift);
  }
}

void loop() {
  // if you disconnected from the network, reconnect:
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    connectToNetwork();
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
    delay(1000);
  } while (epoch == 0);

  rtc.setEpoch(epoch);

  // increment the reconnect count:
  reconnects++;
  Serial.println(getTimeStamp());
  IPAddress ip = WiFi.localIP();
  Serial.print(ip);
  Serial.print("  Signal Strength: ");
  Serial.println(WiFi.RSSI());
}

void checkDrift() {
  // set the time from the network:
  do {
    if (Serial) {
      Serial.println("Attempting to get network time");
    }
    epoch = WiFi.getTime();
    delay(1000);
  } while (epoch == 0);

  // calculate the drift using the epoch from the network
  // and the RTC epoch:
  drift = epoch - rtc.getEpoch();
  logData();
  if (Serial) {
    Serial.print("Clock drift: ");
    Serial.println(drift);
  }
}

void logData() {
  // if SD card is reachable, write to it:
  if (SDAvailable) {
    // open SD card file:
    File dataFile = SD.open(logFile, FILE_WRITE);
    dataFile.print(getDateStamp() + ",");
    dataFile.print(getTimeStamp() + ",");
    dataFile.print(String(rtc.getEpoch()) + ",");
    dataFile.print(String(epoch) + ",");
    dataFile.println(String(drift));
    // close SD card file:
    dataFile.close();
  }
}

// format the date as dd-mm-yyyy
String getDateStamp() {
  String dateStamp = "";
  if (rtc.getDay() <= 9) dateStamp += "0";
  dateStamp += rtc.getDay();
  dateStamp += "-";
  if (rtc.getMonth() <= 9) dateStamp += "0";
  dateStamp += rtc.getMonth();
  dateStamp += "-20";
  if (rtc.getYear() <= 9) dateStamp += "0";
  dateStamp += rtc.getYear();
  return dateStamp;
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
  timestamp += " UTC";
  return timestamp;
}
