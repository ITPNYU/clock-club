/*
  Creates a clock using a string of 60 neoPixels. Uses RTCZero lib for time,
  So it needs a MKR1000, Zero, or other M0 based board.

  Uses Adafruit's NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel

  created 28 May 2016
  modified 14 Aug 2016
  by Tom Igoe
*/
#include <Adafruit_NeoPixel.h>
#include <RTCZero.h>
#include <Encoder.h>

const int neoPixelPin = 5;  // control pin
const int numPixels = 72;    // number of pixels
const int buttonPin = 8;

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, neoPixelPin, NEO_GRB + NEO_KHZ800);

Encoder encoder(6, 7);
int mode = 0;     // setting mode: 0 = set, 1 = hour, 2 = min, 3 = sec
int lastButton = HIGH;
int lastEncoder = 0;

RTCZero rtc;
unsigned int hours, minutes, seconds;

// colors
long hourColor = 0xAA77FF;
long secondColor = 0xFFFFFF;

long lastTick = 0; // Last second when the LEDs changed

void setup() {
  Serial.begin(9600);
  // get the time from the compiler. __TIME__ returns
  // a string of the time the sketch was compiled, as hh:mm:ss
  String compileTime = __TIME__;
  hours = compileTime.substring(0, 2).toInt();    // convert hours to an int
  minutes = compileTime.substring(3, 5).toInt();  // convert minutes to an int
  seconds = compileTime.substring(6, 8).toInt();  // convert seconds to an int

  rtc.begin(); // initialize RTC
  rtc.setTime(hours, minutes, seconds);
  pinMode(buttonPin, INPUT_PULLUP);

  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // Initialize all pixels to 'off'
}

void loop() {
  // count the milliseconds, update second when 1000ms have passed:
  if (rtc.getSeconds() != lastTick) {
    lastTick = rtc.getSeconds();

    strip.clear();
    setHands(rtc.getHours() % 12, rtc.getMinutes(), rtc.getSeconds());
    // refresh the strip
  }
  int button = digitalRead(buttonPin);
  if (button != lastButton) {
    if (button == LOW) {
      mode++;
      if (mode > 3) {
        // all three times set; set RTC:
        rtc.setTime(hours, minutes, seconds);
        mode = 0;
      }
    }
  }
  lastButton = button;

  int encoderPos = encoder.read() / 4;  // need to /4 to get each click to be 1
  int diff = encoderPos - lastEncoder;  // get difference

  if (mode > 0 && diff != 0) {
    switch (mode) {
      case 1:   // hour
        hours = constrain(hours + diff, 0, 11);
        break;
      case 2:   // minute
        minutes = constrain(minutes + diff, 0, 59);
        break;
      case 3:   // second
        seconds = constrain(seconds + diff, 0, 59);
        break;
    }
    setHands(hours, minutes, seconds);

  }
  lastEncoder = encoderPos;
}

void setHands(int h, int m, int s) {
  // calculate the beginning of the hour segment:
  int hourPosition = (h) + 60;      // the outside pixels
  strip.setPixelColor(hourPosition, hourColor);
  strip.setPixelColor(m, hourColor);   // set minute pixel
  strip.setPixelColor(s, secondColor);   // set second pixel
  strip.show();
}

void printTime() {
  Serial.print(rtc.getHours());
  Serial.print(":");
  Serial.print(rtc.getMinutes());
  Serial.print(":");
  Serial.println(rtc.getSeconds());
}


