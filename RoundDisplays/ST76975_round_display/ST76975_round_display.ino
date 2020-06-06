
/*
  Displays a clock on a DFRobot ST7687S round LCD display

  created 24 April 2019
  by Tom Igoe
*/

#include <DFRobot_ST7687S_Latch.h>
#include <SPI.h>
#include <RTCZero.h>

// output pins:
const int DISPLAY_CS = 4;
const int DISPLAY_RS = 5;
const int DISPLAY_WR = 3;
const int DISPLAY_LCK = 7;

// background color:
long bgColor = 0x335599;

// hand lengths:
int minuteHand = 40;
int secondHand = 50;
int hourHand = 25;

DFRobot_ST7687S_Latch screen(DISPLAY_CS, DISPLAY_RS, DISPLAY_WR, DISPLAY_LCK);
RTCZero rtc;

// last states of the second, minute, hour:
int lastSecond = 0;
int lastMinute = 0;
int lastHour = 0;

void setup() {
  screen.begin();
  rtc.begin();
  // set time and date from the compiler:
  setTimeFromCompile();
  setDateFromCompile();
  screen.fillScreen(bgColor);
}

void loop() {
  // redraw once per second:
  if (rtc.getSeconds() != lastSecond) {
    // if the hour has changed since last draw,
    // erase the old hour hand:
    if (rtc.getHours() != lastHour) {
      drawHand(lastHour, bgColor, hourHand, 12);
    }
    // draw the hour hand:
    drawHand(rtc.getHours(), 0xFFFFFF, hourHand, 12);
    lastHour = rtc.getHours() % 12;

    // if the minute has changed since last draw,
    // erase the old minute hand:
    if (rtc.getMinutes() != lastMinute) {
      drawHand(lastMinute, bgColor, minuteHand, 60);
    }
    // draw the minute hand:
    drawHand(rtc.getMinutes(), 0xFFFFFF, minuteHand, 60);
    lastMinute = rtc.getMinutes();

    // erase the old sedond hand:
    drawHand(lastSecond, bgColor, secondHand, 60);
    // draw the second hand:
    drawHand(rtc.getSeconds(), 0xFFFFFF, secondHand, 60);
    lastSecond = rtc.getSeconds();
  }
}

void drawHand(int handPosition, long handColor, int handLength, int divisions) {
  // calculate the angle based on the hand position:
  float angle = ((handPosition * 360.0) / divisions) ;
  // rotate 90 degrees counterclockwise:
  angle -= 90;
  // convert angle to radians:
  angle = angle * PI / 180;
  // calculate hand endpoint using Pythagorean theorem and hand length:
  float x = cos(angle) * handLength;
  float y = sin(angle) * handLength;
  // draw the line:
  screen.drawLine(0, 0, x, y, handColor);
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

// format the date as dd-mm-yyyy:
String getDateStamp() {
  String datestamp = "";
  if (rtc.getDay() <= 9) datestamp += "0";
  datestamp += rtc.getDay();
  datestamp += "-";
  if (rtc.getMonth() <= 9) datestamp += "0";
  datestamp += rtc.getMonth();
  // add century:
  datestamp += "-20";
  if (rtc.getYear() <= 9) datestamp += "0";
  datestamp += rtc.getYear();
  return datestamp;
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
  String months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
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
