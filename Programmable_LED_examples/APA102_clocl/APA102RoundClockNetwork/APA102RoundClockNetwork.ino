/*
  Creates a clock using a string of 60 neoPixels. Uses RTCZero lib for time,
  So it needs a MKR1000, Zero, or other M0 based board.

  Uses Adafruit's NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel

  created 28 May 2016
  modified 12 Dec 2019
  by Tom Igoe
*/

#include <RTCZero.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <Adafruit_DotStar.h>
#include "arduino_secrets.h"

const int pixelCount = 60;    // number of pixels
// you need these only if you're using sotware SPI:
const int dataPin = 8;       // data pin
const int clockPin = 9;      // clock pin

// set up strip:
Adafruit_DotStar ring(pixelCount, dataPin, clockPin, DOTSTAR_BGR);

RTCZero rtc;
int timeZoneOffset = -5;
// colors
long hourColor = 0x000DEE;
long minuteColor = 0x1D88FF;
long secondColor = 0x77BBBB;
long secondFade;

long lastTick = 0; // Last second when the LEDs changed
boolean rising = 0;
void setup() {
  Serial.begin(9600);

  // while you're not connected to a WiFi AP:
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(SECRET_SSID);
    WiFi.begin(SECRET_SSID, SECRET_PASS); //   try to connect
    delay(2000);       // wait 2 seconds before trying again
  }
  printWifiStatus();
  delay(5000);
  int tries = 0;
  rtc.begin(); // initialize RTC
  long epoch = 0;
  while (epoch == 0 && tries < 5) {
    Serial.println("Trying to get time");
    epoch = WiFi.getTime();
    rtc.setEpoch(epoch);
    int localHour = rtc.getHours() + timeZoneOffset;
    rtc.setHours(localHour);
    delay(3000);
    tries++;
  }

  if (epoch == 0) {
    rtc.setTime(00, 00, 00);
  }
  printTime();
  ring.begin();    // initialize pixel ring
  ring.clear();    // turn all LEDs off
  ring.show();     // Initialize all pixels to 'off'
}

void loop() {
  // count the milliseconds, update second when 1000ms have passed:
  if (rtc.getSeconds() != lastTick) {
    lastTick = rtc.getSeconds();

    ring.clear();
    secondFade = secondColor;
    // calculate the beginning of the hour segment:
    int hourPosition = 59 - (rtc.getHours() % 12) * 5;     // every fifth pixel
    ring.setPixelColor(hourPosition, hourColor);
    ring.setPixelColor(59 - rtc.getMinutes(), minuteColor);   // set minute pixel
    ring.setPixelColor(59 - rtc.getSeconds(), 0);  // set second pixel
    rising = true;
  } else {
    // subtract from the color:
    secondFade = ring.getPixelColor(59 - rtc.getSeconds());
    if (rising && (secondFade <= secondColor)) {
      secondFade = secondFade + 0x0A0F0F;
    } else {

      secondFade = secondFade - 0x0A0F0F;
      secondFade = max(secondFade, 0);
      rising = false;
    }
    ring.setPixelColor(59 - rtc.getSeconds(), secondFade);  // set second pixel
  }
  ring.show();                             // refresh the strip

}

void printTime() {
  Serial.print(rtc.getHours());
  Serial.print(":");
  Serial.print(rtc.getMinutes());
  Serial.print(":");
  Serial.println(rtc.getSeconds());
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
