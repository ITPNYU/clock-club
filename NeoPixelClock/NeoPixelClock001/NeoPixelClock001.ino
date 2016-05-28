/*
  Creates a clock using a string of 60 neoPixels. Blinkenlabs' BlinkyStrip works well for this.
  seconds is a white pixel
  minutes is a teal pixel
  hours is five purple pixels
  background is blue

  Uses Adafruit's NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel

  created 28 May 2016
  by Tom Igoe
*/
#include <Adafruit_NeoPixel.h>

const int neoPixelPin = 13;  // control pin
const int numPixels = 60;    // number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, neoPixelPin, NEO_GRB + NEO_KHZ800);

// colors
long blueish = 0x040324;
long whiteish = 0x434343;
long darkPurple = 0x0D0018;
long greenish = 0x091C12;

// time
int hours = 0;
int minutes = 0;
int seconds = 0;
long lastCount = 0; // count of millis since last second

void setup() {
  // get the time from the compiler. __TIME__ returns
  // a string of the time the sketch was compiled, as hh:mm:ss
  String compileTime = __TIME__;
  hours = compileTime.substring(0, 2).toInt();    // convert hours to an int
  minutes = compileTime.substring(3, 5).toInt();  // convert minutes to an int
  seconds = compileTime.substring(6, 8).toInt();  // convert seconds to an int

  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // Initialize all pixels to 'off'
}

void loop() {
  // count the milliseconds, update second when 1000ms have passed:
  if (millis() - lastCount > 1000) {
    seconds++;
    lastCount = millis();
  }
  if (seconds > 59) {   // rollover seconds and update minutes
    seconds = 0;
    minutes++;
  }
  if (minutes > 59) {   // rollover minutes and update hours
    minutes = 0;
    hours++;
  }
  if (hours > 12) {     // rollover hours
    hours = 0;
  }
    // loop over all the pixels, make them blue:
  for (int pixel = 0; pixel < numPixels; pixel++) {
    strip.setPixelColor(pixel, blueish);// set the color for this pixel
  }  
  
  // calculate the beginning of the hour segment:
  int hourPosition = (hours - 1) * 5;
  
  // loop over segment, make them purple:
  for (int p = hourPosition; p < hourPosition + 5; p++) {
    strip.setPixelColor(p, darkPurple);
  }
  strip.setPixelColor(minutes, greenish);   // set minute pixel
  strip.setPixelColor(seconds, whiteish);   // set second pixel
  
  strip.show();                             // refresh the strip
}


