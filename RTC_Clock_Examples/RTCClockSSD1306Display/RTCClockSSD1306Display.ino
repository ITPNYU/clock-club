/*
  Simple digital clock
  Sets the realtime clock on any of the MKR or M0 boards
  using the compile time and compile date.
  Prints the time once per second.
  prints the date once per minute.

  This sketch is designed as the basis for many different clock projects.

  This clock uses an  SSD1306 OLED display, and the library
  that drives it. You can replace this display with any
  other display library.

  created 25 Nov. 2018
  by Tom Igoe
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTCZero.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTCZero rtc;      // instance of the realtime clock
int thisSecond;   // variable to look for seconds chang

void setup() {
  Serial.begin(9600);
  // initialize the display library:
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println("SSD1306 setup failed");
    while (true);
  }

  // initialize the realtime clock:
  rtc.begin();
  setTimeFromCompile();
  setDateFromCompile();

  // set alarm to show the date once a minute:
  rtc.setAlarmTime(12, 0, 00);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(showDate);
}

void loop() {
  if (thisSecond != rtc.getSeconds()) {
    // on the zero second, skip the rest of the loop():
    if (rtc.getSeconds() == 0) return;

    // display the time:
    Serial.println(getTimeStamp());
    displayWrite(getTimeStamp());

    // save current time for next loop:
    thisSecond = rtc.getSeconds();
  }
}

void displayWrite(String message) {
  display.clearDisplay();
  display.setRotation(180);
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}

// realtime clock interrupt service routine:
void showDate() {
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(getDateStamp());
  display.display();
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
