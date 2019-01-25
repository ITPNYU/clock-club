/*
  Text-to-speechj digital clock
  Sets the realtime clock on any of the MKR or M0 boards
  using the compile time and compile date.
  Speaks the time once per second.
  Speaks the date once an hour.


  This sketch is designed as the basis for many different clock projects.

  This clock uses the serial1 port for output. It is connected to
  an Emic2 text-to-speech module (https://www.sparkfun.com/products/11711)

  created 25 Jan 2019
  by Tom Igoe
*/

#include <RTCZero.h>

RTCZero rtc;      // instance of the realtime clock
int thisSecond;   // variable to look for seconds change
String months[] = {"January", "February", "March", "April", "May",
                   "June", "July", "August", "September", "October",
                   "November", "December"
                  };

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  // initialize the realtime clock:
  rtc.begin();
  setTimeFromCompile();
  setDateFromCompile();

  // set alarm to show the date once a minute:
  rtc.setAlarmTime(0, 0, 59);
  rtc.enableAlarm(rtc.MATCH_SS);
  rtc.attachInterrupt(showDate);
  // set the word rate at 400 words per minute (can go 75 - 600 wpm):
  Serial1.println("W400");
  // set the voice (Frail Frank):
  Serial1.println("N6");
  // set the volume:
  Serial1.println("V18");
  // delay to get commands through:
  delay(1000);
  Serial1.println("S" + getTimeStamp());
}

void loop() {
  // every five seconds:
  if  (rtc.getSeconds() != thisSecond && rtc.getSeconds() % 5 == 0) {
    // Speak the time on the Emic2:
    Serial1.println("S" + getTimeStamp());

    // save current time for next loop:
    thisSecond = rtc.getSeconds();
  }
}


// realtime clock interrupt service routine:
void showDate() {
  Serial1.println("S" + getDateStamp());
}

// format the time as hh mm ss, easiest for text-to-speech:
String getTimeStamp() {
  String timestamp = "";
  if (rtc.getHours() <= 9) timestamp += "0";
  timestamp += rtc.getHours();
  timestamp += " ";
  if (rtc.getMinutes() <= 9) timestamp += "0";
  timestamp += rtc.getMinutes();
  timestamp += " ";
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
  //if (rtc.getMonth() <= 9) dateStamp += "0";
  dateStamp += months[rtc.getMonth() - 1];
  dateStamp += ", Two thousand ";
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
//  String months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
//                     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
//                    };
  // get the compile date:
  String compileDate = String(__DATE__);

  // get the date substring
  String monthStr = compileDate.substring(0, 3);

  int m = 0;    // variable for the date as an integer
  // see which month matches the month string:
  for (int i = 0; i < 12; i++) {
    String monthShort = months[i].substring(0,3);
    if (monthStr == monthShort) {
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
