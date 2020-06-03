
/*
  A desk/bedside clock.
  Built on an Arduino 33 IoT, but can work with any Arduino-compatible
  that uses a SAMD processor (for the RTC library).

  created 8 Jan 2020
  modified 16 Jan 2020
  by Tom Igoe
*/

#include <Encoder.h>        // encoder library
#include <RTCZero.h>        // real time clock library
#include "SPI.h"
#include "TFT_22_ILI9225.h" // display library

// display pins:
#define TFT_RST 9
#define TFT_RS  8
#define TFT_CS  10
#define TFT_LED 0   // 0 if wired to +V directly
// note the SPI MOSI (pin 11) and SPI CLK (pin 13) are used as well.
TFT_22_ILI9225 screen = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

// GPIO pins:
Encoder knob(2, 3);             // encoder on pins 2 and 3
const int encoderButton =  A7;  // encoder button (time set)
const int DSTButton = A5;       // front panel button 1 (daylight savings)
const int dimButton = A1;       // front panel button 2 (screen dim)
const int dimLED = 5;           // button 1 LED: screen dim
const int dstLED = 6;           // button 2 LED: daylight savings toggle

// brightness levels for the LEDs:
int dimLEDBrightness = 0;
int dstLEDBrightness = 0;

// colors for the display:
// used yellow and blue to be most readable by colorblind users;
// red for setting the hands was invisible to the test subject.
const long brightColor = 0x1247FF;
const long dimColor = 0x09236F;
const long settingColor = COLOR_YELLOW;
long fillColor = brightColor;

// button and knob states:
int lastButtonState = LOW;  // last button state
int lastKnobState = -1;     // last knob state
int steps = 0;              // encoder step count

// pressed states for the buttons:
int encoderButtonPressed = false;
int DSTButtonPressed = false;
int dimButtonPressed = false;

// button debounce delay, in ms:
int debounceDelay = 4;

// states from the buttons:
boolean displayDimmed = false;
boolean daylightSavings = false;

// realtime clock:
RTCZero rtc;
int currentProperty = 0;    // time property being changed
int lastSecond = 0;         // rtc.getSeconds()' previous value

// starting and ending positions of the hands:
int hands[3][4] =
{ {90, 120, 90, 90},  // hour
  {90, 120, 90, 60},  // minute
  {90, 120, 90, 50}   // second
};

void setup() {
  Serial.begin(9600);

  // initialize the display
  screen.begin();
  // clear the screen:
  screen.clear();

  // init pushbuttons
  pinMode(encoderButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderButton), encoderButtonChange, FALLING);
  pinMode(dimButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(dimButton), dimButtonChange, FALLING);
  pinMode(DSTButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DSTButton), DSTButtonChange, FALLING);

  // init LEDs
  pinMode(dimLED, OUTPUT);
  pinMode(dstLED, OUTPUT);

  // init RTC
  rtc.begin();
  rtc.setTime(0, 0, 0);
}

void loop() {

  // read pushbuttons, get change
  if (encoderButtonPressed) {
    // increment currentProperty:
    currentProperty++;
    // limit it to three possible values (h, m, s)
    currentProperty %= 4;
    Serial.println("timeset");
    encoderButtonPressed = false;
  }
  // button 1 changes the brightness of the display:
  if (dimButtonPressed) {
    Serial.println("dim");
    dimLEDBrightness = 255;
    displayDimmed = !displayDimmed;
    dimButtonPressed = false;
  }
  // button 2 sets daylight savings:
  if (DSTButtonPressed) {
    Serial.println("DST");
    dstLEDBrightness = 255;
    daylightSavings = !daylightSavings;
    if (daylightSavings) {
      if (rtc.getHours() == 0) { // at 0 hour, DST = 23:00
        rtc.setHours(23);        // to avoid -1
      } else {      // otherwise DST = current hour -1
        rtc.setHours(rtc.getHours() - 1);
      }
    } else {        // standard time = DST + 1
      rtc.setHours(rtc.getHours() + 1);
    }
    DSTButtonPressed = false;
  }

  // fade the front buttons if they are on:
  analogWrite(dimLED, dimLEDBrightness);
  analogWrite(dstLED, dstLEDBrightness);
  dstLEDBrightness = max(dstLEDBrightness--, 0);
  dimLEDBrightness = max(dimLEDBrightness--, 0);

  // read encoder, get change
  int knobState = knob.read();

  // compare current and last knob state:
  int knobChange = knobState - lastKnobState;
  // if it's changed by 4 or more (one step):
  if (abs(knobChange) >= 4) {
    // get the direction (-1 or 1):
    int knobDirection = (knobChange / abs(knobChange));
    // invert it (because we're turning the knob from the back, 
    // when looking at the clock face:
    knobDirection = -knobDirection;
    // use the change to change the current time property:
    timeSet(currentProperty, knobDirection);
    Serial.println(knobDirection);
    // save knobState for next time through loop:
    lastKnobState = knobState;
  }
  // print the time once a second:
  if (rtc.getSeconds() != lastSecond) {
    displayWrite(getTimeStamp());
    // save current second for future comparison:
    lastSecond = rtc.getSeconds();
  }
}

// button press handlers. If the button goes low,
// debounce, then read for current state:
void encoderButtonChange() {
  delay(debounceDelay);
  if (digitalRead(encoderButton) == LOW) {
    encoderButtonPressed = true;
  }
}

void dimButtonChange() {
  delay(debounceDelay);
  if (digitalRead(dimButton) == LOW) {
    dimButtonPressed = true;
  }
}

void DSTButtonChange() {
  delay(debounceDelay);
  if (digitalRead(DSTButton) == LOW) {
    DSTButtonPressed = true;
  }
}

// set the time:
void timeSet(int thisProperty, int changeValue) {
  int setting;
  switch (thisProperty) {
    case 0:   // nothing; time is set now
      break;
    case 1:   // hours
      setting = rtc.getHours() + changeValue;
      if (setting > 23) setting = 0;
      if (setting < 0) setting = 23;
      rtc.setHours(setting);
      break;
    case 2:   // minutes
      setting = rtc.getMinutes() + changeValue;
      if (setting > 59) setting = 0;
      if (setting < 0) setting = 59;
      rtc.setMinutes(setting);
      break;
    case 3:   // seconds
      setting = rtc.getSeconds() + changeValue;
      if (setting > 59) setting = 0;
      if (setting < 0) setting = 59;
      rtc.setSeconds(setting);
      break;
  }

  // update display:
  displayWrite(getTimeStamp());
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

void displayWrite(String message) {
  // dimmed display is a darker color:
  if (displayDimmed) {
    fillColor = dimColor;
  } else {
    fillColor = brightColor;
  }
  // draw the circle 2px thick:
  screen.drawCircle(90, 120, 80, fillColor);
  screen.drawCircle(90, 120, 79, fillColor);
  // draw hour hand:
  drawHand(0);
  // minute hand:
  drawHand(1);
  // second hand:
  drawHand(2);
}

// calculate hand positions:
void drawHand(int handNumber) {
  float angle = 0;      // angle in radians
  int handLength = 0;   // length of each hand
  float rads = 2 * PI;  // 2PI radians = 360 degrees

  // which hand are we setting?
  switch (handNumber) {
    case 0:   // the hour hand
      angle = (rtc.getHours() / 12.0 * rads);
      handLength = 30;
      break;
    case 1:  // the minute hand
      angle = (rtc.getMinutes()  / 60.0 * rads);
      handLength = 50;
      break;
    case 2:  // the second hand
      angle = (rtc.getSeconds() / 60.0 * rads);
      handLength = 60;
      break;
  }
  // color to set each hand to:
  long thisColor;
  // if the property currently to be set is this hand,
  // then make it red:
  if (currentProperty == handNumber + 1) {
    thisColor = settingColor;
  } else {
    thisColor = fillColor;
  }
  // blank the old line:
  screen.drawLine(hands[handNumber][0], hands[handNumber][1],
                  hands[handNumber][2], hands[handNumber][3], COLOR_BLACK);
  // calculate new line:
  hands[handNumber][2] = 90 + handLength * cos(angle);
  hands[handNumber][3] = 120 + handLength * sin(angle);
  // draw new line:
  screen.drawLine(hands[handNumber][0], hands[handNumber][1],
                  hands[handNumber][2], hands[handNumber][3], thisColor);

}
