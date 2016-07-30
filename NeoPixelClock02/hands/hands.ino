
#include <Adafruit_NeoPixel.h>

const int PIN = 5;
const int NUMPIXELS = 8;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
long handColor = 0x324B58;

void setup() {
  pixels.begin();
}

void loop() {
  minuteHand();
  pixels.show();
  delay(3000);
  hourHand();
  pixels.show();
  delay(3000);
}


void minuteHand() {
   pixels.clear();
  for (int p = 0; p < 8; p++) {
    pixels.setPixelColor(p, handColor);
  }
}

void hourHand() {
     pixels.clear();
  for (int p = 0; p < 4; p++) {
    pixels.setPixelColor(p, handColor);
  }
}

