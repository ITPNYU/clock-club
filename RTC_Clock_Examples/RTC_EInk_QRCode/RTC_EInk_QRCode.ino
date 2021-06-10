
/*
  QR Code generator for eInk Display
   Displays a QR code on an eInk display
   Uses Adafruit EPD library: http://librarymanager/All#Adafruit_EPD
   and Richard Moore's qrcode library: http://librarymanager/All#qrcode
   Code is based on qrcode library example and Adafruit_EPD example.

   To test, enter a text string, then scan it with your mobile device

  created 8 Jan 2021
  by Tom Igoe
*/

#include "Adafruit_EPD.h"
#include "qrcode.h"
#include <RTCZero.h>

// pin numbers. In addition to these, the SPI pins
// must be connected, and note that EPD_CS is the SPI CS pin:
const int EPD_CS = 10;
const int  EPD_DC = 9;
const int  SRAM_CS = -1; //8;
const int  EPD_RESET = 7;
const int EPD_BUSY = 6; // optional. for faster response, attach this to a pin

// You may need to use a different initializer depending on your screen.
// This works for 1.54 inch x 1.54 inch displays:
// Adafruit_IL0373 display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
RTCZero rtc;      // instance of the realtime clock
int thisMinute;   // variable to look for seconds chang

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  // start the display:
  display.begin();
  display.clearBuffer();
  display.display();

 // initialize the realtime clock:
  rtc.begin();
  setTimeFromCompile();
  setDateFromCompile();
}

void loop() {
 if (thisMinute != rtc.getMinutes()) {
 
    // display the time:
    Serial.println(getTimeStamp());
    displayQRTime(getTimeStamp());

    // save current time for next loop:
    thisMinute = rtc.getMinutes();
  }
}

void displayQRTime(String message) {
  Serial.print("Message length: ");
  Serial.println(message.length());

  // Create the QR code
  QRCode qrcode;
  // See table at https://github.com/ricmoo/QRCode
  // or https://www.qrcode.com/en/about/version.html for
  // calculation of data capacity of a QR code. Current
  // settings will get you about 100 bytes:
  int qrVersion = 4;
  // can be ECC_LOW, ECC_MEDIUM, ECC_QUARTILE and ECC_HIGH (0-3, respectively):
  int qrErrorLevel = ECC_LOW;

  // allocate QR code memory:
  byte qrcodeBytes[qrcode_getBufferSize(qrVersion)];
  qrcode_initText(&qrcode, qrcodeBytes, qrVersion, qrErrorLevel, message.c_str());

  // QR Code block characteristics will depend on the display:
  // QR code needs a "quiet zone" of empty space around it, hence the offset:
  int offset = 20;
  int blockSize = (display.height() - (offset * 2)) / qrcode.size;
//  display.clearBuffer();
 display.fillScreen(EPD_WHITE);
 display.setCursor(offset*2, offset);
  display.setTextSize(2);
  display.setTextColor(EPD_BLACK);
  display.print(message);

  // read the bytes of the QR code and set the blocks light or dark, accordingly:
  // vertical loop:
  for (byte y = 0; y < qrcode.size; y++) {
    // horizontal loop:
    for (byte x = 0; x < qrcode.size; x++) {
      // caculate the block's X and Y positions:
      int blockX = (x * blockSize) + offset;
      int blockY = (y * blockSize) + offset * 2;
      // read the block value from the QRcode:
      int blockValue = qrcode_getModule(&qrcode, x, y);
      // set the default block color:
      int blockColor = EPD_WHITE;
      // if the block value is 1, set color to white:
      if (blockValue == 1) {
        blockColor = EPD_BLACK;
      }
      // display the block on the screen:
      display.fillRect(blockX, blockY, blockSize, blockSize, blockColor);
    }
  }
  // print the message and display it:
  Serial.println(message);
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
//  timestamp += ":";
//  if (rtc.getSeconds() <= 9) timestamp += "0";
//  timestamp += rtc.getSeconds();
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
