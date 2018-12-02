/*
  Simple digital clock
  Sets the realtime clock on any of the MKR or M0 boards
  using the compile time and compile date.
  Prints the time once per second.
  prints the date once per minute.

  This sketch is designed as the basis for many different clock projects.

  This clock uses an  ePaper display, and the library
  that drives it. You can replace this display with any
  other display library. It was tested with a SparkFun ePaper display
  and the Adafruit ePaper library:

  https://github.com/adafruit/Adafruit_EPD
  https://www.sparkfun.com/products/14892

  created 30 Nov. 2018
  by Tom Igoe
*/

#include <RTCZero.h>
#include "Adafruit_EPD.h"
#include <Fonts/FreeSans12pt7b.h>

#define EPD_CS      1
#define EPD_DC      0
#define SRAM_CS     2
#define EPD_RESET   4
#define EPD_BUSY    5

Adafruit_IL0373 ePaper(152, 152 , EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

RTCZero rtc;      // instance of the realtime clock

void setup() {
  Serial.begin(9600);
  ePaper.begin();
  ePaper.setFont(&FreeSans12pt7b);
  ePaper.clearBuffer();

  // initialize the realtime clock:
  rtc.begin();
  setTimeFromCompile();
  setDateFromCompile();
  displayWrite(getTimeStamp());
}

void loop() {
  if (rtc.getSeconds() == 0) {
    showTime();
  } 
}

void showTime() {
  Serial.println(getTimeStamp());
  displayWrite(getTimeStamp());
}


void displayWrite(String message) {
  ePaper.clearBuffer();
  ePaper.fillScreen(EPD_WHITE);
  ePaper.setTextColor(EPD_BLACK);
  ePaper.setCursor(20, ePaper.height() / 2);
  ePaper.println(message);
  ePaper.display();
}

// realtime clock interrupt service routine:
void showDate() {
  displayWrite(getDateStamp());
}

// format the time as hh:mm:ss
String getTimeStamp() {
  String timestamp = "";
  if (rtc.getHours() <= 9) timestamp += "0";
  timestamp += rtc.getHours();
  timestamp += ":";
  if (rtc.getMinutes() <= 9) timestamp += "0";
  timestamp += rtc.getMinutes();
  return timestamp;
}

// format the date as dd:mm:yy
String getDateStamp() {
  String dateStamp = "";
  if (rtc.getDay() <= 9) dateStamp += "0";
  dateStamp += rtc.getDay();
  dateStamp += "-";
  if (rtc.getMonth() <= 9) dateStamp += "0";
  dateStamp += rtc.getMonth();
  dateStamp += "-";
  dateStamp += rtc.getYear();
  return dateStamp;
}

// set the rtc time from the compile time:
void setTimeFromCompile() {
  // get the compile time string:
  String compileTime = String(__TIME__);
  // break the compile time on the colons:
  int h = compileTime.substring(0, 2).toInt();
  int m = compileTime.substring(3, 5).toInt();
  int s = compileTime.substring(6, 8).toInt();

  // set the time from the derived numbers:
  rtc.setTime(h, m, s);
}

// set the rtc time from the compile date:
void setDateFromCompile() {
  String months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
                    };
  // get the compile date:
  String compileDate = String(__DATE__);

  // get the date substring
  String monthStr = compileDate.substring(0, 3);

  int m = 0;    // variable for the date as an integer
  // see which month matches the month string:
  for (int i = 0; i < 12; i++) {
    if (monthStr == months[i]) {
      // the first month is 1, but its array position is 0, so:
      m = i + 1;
      // no need to continue the rest of the for loop:
      break;
    }
  }

  // get the day and year as substrings, and convert to numbers:
  int d = compileDate.substring(4, 6).toInt();
  int y = compileDate.substring(9, 11).toInt();
  // set the date from the derived numbers:
  rtc.setDate(d, m, y);
}
