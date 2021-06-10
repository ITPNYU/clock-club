/*
  Clock example for ePaper display
  Uses Adafruit EPD library: http://librarymanager/All#Adafruit_EPD

  Circuit:
   - 1.54-inch ePaper display connected to SPI pins, and connected to
   the pins listed below.

  created 20 Feb 2021
  by Tom Igoe
*/

#include "Adafruit_EPD.h"
#include "arduino_secrets.h"
#include "fonts.h"
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <ArduinoLowPower.h> // note: works only on SAMD boards
#include <RTCZero.h>         // note: works only on SAMD boards
#include <WiFiNINA.h>        // use this for MKR1010 and Nano 33 IoT

// pin numbers. In addition to these, the SPI pins
// must be connected, and note that EPD_CS is the SPI CS pin:
const int EPD_CS = 10;
const int EPD_DC = 9;
const int SRAM_CS = -1; // for boards without a frame buffer, set to -1
const int EPD_RESET = 7;
const int EPD_BUSY =  6;

// button constants and variables:
const int buttonPin = 3;
const int indicatorLED = A7;
const int debounceDelay = 10;
volatile bool buttonPressed = false;
long startingEpoch = 0;

/*
  You may need to use a different initializer depending on your screen.
  see
  https://github.com/adafruit/Adafruit_EPD/blob/master/examples/EPDTest/EPDTest.ino
  lines 19ff. for all the chipsets that the Adafruit EPD supports.
*/
// supports Adafruit's 1.54inch displays, Sparkfun's SparkX 1.54" display:
Adafruit_IL0373 display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

WiFiClient wifi;

RTCZero rtc;
String lastTime = "00:00";
String lastDate = "00/00/00";
int timeZone = -5;

void setup() {
  Serial.begin(9600);
   if (!Serial) delay(3000);
   
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode (indicatorLED, OUTPUT);
  // set WiFi radio into low power mode:
  //  WiFi.lowPowerMode();
  WiFi.setHostname(SECRET_HOSTNAME);
  // initialize the realtime clock:
  rtc.begin();
  // if not on the network,mtry to connect:
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
    getNetworkTime();
  }
  pinMode(buttonPin, INPUT_PULLUP);
  // wake up the processor when the button is pressed:
  LowPower.attachInterruptWakeup(digitalPinToInterrupt(buttonPin),
                                 buttonHandler, FALLING);
  // start the display:
  display.begin();
  // set the text color to black:
  display.setTextColor(EPD_BLACK);
}

void loop() {
  Serial.println("Awake");
  delay(100);
    digitalWrite(indicatorLED, HIGH);
  // if not on the network, try to connect:
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
    getNetworkTime();
  }
Serial.println(getUpTime());
  // show the time:
  displayTime();
  digitalWrite(indicatorLED, LOW);
  // disconnect the WiFi:
  if (WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect();
    // turn off the status LED:
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.println("going back to sleep");
  //   go back to sleep:
  LowPower.sleep();
}

void buttonHandler() {
  delay(debounceDelay);
  if (digitalRead(buttonPin) == LOW) {
    buttonPressed = true;
  }
}

void connectToWiFi() {
  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(SECRET_SSID);
    // Connect to WPA/WPA2 network:
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(2000);
  }
  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());
  // turn on LED to indicate connection:
  digitalWrite(LED_BUILTIN, HIGH);
}

void getNetworkTime() {
  // set the time from the network:
  unsigned long epoch;
  do {
    Serial.println("Attempting to get network time");
    epoch = WiFi.getTime();
    delay(1500);
  } while (epoch == 0);
  // set the time with the epoch value you got from the network:
  rtc.setEpoch(epoch);
  // adjust for timezone, as WiFi.getTime gets GMT:
  rtc.setHours(rtc.getHours() + timeZone);
  if (startingEpoch == 0) startingEpoch = rtc.getEpoch();
  Serial.println(getTimeStamp());
  Serial.println(getDateStamp());
}

void displayTime() {
  // clear the display:
  display.clearBuffer();
  // set large font:
  display.setFont(&FreeSansBold18pt7b);
  display.setCursor(30, 28);
  display.print(getTimeStamp());

  // change font to be smaller
  display.setFont(&FreeSans9pt7b);
  // move the cursor down:
  display.setCursor(34, 48);
  display.print(getDateStamp());

  // change font to be smaller
  display.setFont(&FreeSans9pt7b);
  display.setCursor(30, 80);
  display.print("Last check:");

  // change font to be smaller
  display.setFont(&FreeSansBold12pt7b);
  display.setCursor(38, 100);
  display.print(lastTime);
  display.setFont(&FreeSans9pt7b);
  display.setCursor(34, 120);
  display.print(lastDate);
  display.setCursor(20, 140);
  display.print(getUpTime());
  // push everything out to the screen:
  display.display();

  // save current time for next time:
  lastTime = getTimeStamp();
  lastDate = getDateStamp();
}

// format the time as hh:mm:ss
String getTimeStamp() {
  String timestamp = "";
  if (rtc.getHours() <= 9)
    timestamp += "0";
  timestamp += rtc.getHours();
  timestamp += ":";
  if (rtc.getMinutes() <= 9)
    timestamp += "0";
  timestamp += rtc.getMinutes();
  return timestamp;
}

// format the date as dd:mm:yy
String getDateStamp() {
  String dateStamp = "";
  if (rtc.getDay() <= 9)
    dateStamp += "0";
  dateStamp += rtc.getDay();
  dateStamp += "/";
  if (rtc.getMonth() <= 9)
    dateStamp += "0";
  dateStamp += rtc.getMonth();
  dateStamp += "/";
  dateStamp += rtc.getYear();
  return dateStamp;
}

String getUpTime() {
  long upSeconds = 0;
  long upMinutes = 0;
  long upHours = 0;
  long upDays = 0;

 upSeconds = rtc.getEpoch() - startingEpoch;
 Serial.println(upSeconds);
  if (upSeconds > 59) {
    upMinutes++;  
    upSeconds %=  60;
  }
  if (upMinutes > 59) {
    upHours++;
    upMinutes %= 60;
  }
  if (upHours > 23) {
    upDays++;
    upHours %= 24;
  }
  String result = String(upDays) + " days, ";
  result += String(upHours) + ":";
  result += String(upMinutes) + ":";
  result += String(upSeconds);
  return result;
}
