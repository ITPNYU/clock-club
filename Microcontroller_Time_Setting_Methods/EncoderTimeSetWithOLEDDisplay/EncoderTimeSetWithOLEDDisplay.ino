/*
  Rotary Encoder Time Set with OLED

  Sets the time using a rotary encoder and a pushbutton
  to set hours, minutes, and seconds. Pushing the button
  changes the property that you are changing.
  Sets the time on an OLED screen

  circuit:
  - Arduino SAMD board (MKR series or Nano 33 IoT)
  - SSD1306 OLED screen
  - Encoder attached to pins 2 and 3. Pushbutton attached to pin 4.
  Other side of pushbutton is connected to ground.
  Change pin numbers to suit your board.

  created 14 Dec 2019
  modified 2 Jun 2020
  by Tom Igoe
*/
#include <Encoder.h>
#include <RTCZero.h>

const int buttonPin = 4;    // pushbutton pin
Encoder knob(2, 3);         // encoder on pins 2 and 3
int lastButtonState = LOW;  // last button state
int lastKnobState = -1;     // last knob state
int steps = 0;              // encoder step count

RTCZero rtc;
int currentProperty = 0;    // time property being changed
int lastSecond = 0;         // rtc.getSeconds()' previous value

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTCZero.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {

  Serial.begin(9600);
  // initialize button pin and Serial and keyboard:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize clock:
  rtc.begin();
  rtc.setTime(0, 0, 0);

  // initialize the display library:
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println("display setup failed");
    while (true);
  }
}

void loop() {
  // read the sensors:
  int buttonState = digitalRead(buttonPin);
  int knobState = knob.read();

  // if the button has changed:
  if (buttonState != lastButtonState) {
    // debounce the button:
    delay(10);
    // if button is pressed:
    if (buttonState == LOW) {
      // increment currentProperty:
      currentProperty++;
      // limit it to three possible values (h, m, s)
      currentProperty %= 4;
    }
    // save current state for next time through the loop:
    lastButtonState = buttonState;
  }

  // compare current and last knob state:
  int knobChange = knobState - lastKnobState;
  // if it's changed by 4 or more (one step):
  if (abs(knobChange) >= 4) {
    // get the direction (-1 or 1):
    int knobDirection = (knobChange / abs(knobChange));
    // use the change to change the current time property:
    changeProperty(currentProperty, knobDirection);
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

void changeProperty(int thisProperty, int changeValue) {
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
  displayWrite(getTimeStamp());
}


void displayWrite(String message) {
  display.clearDisplay();
  display.setRotation(180);
  // if there's a current property, 
  // draw a rect around it:
  if (currentProperty > 0) {
    int multiplier = currentProperty - 1;
    int diff = ( multiplier * 24) + multiplier * 12;
    display.drawRect(diff, 0, 24, 20, 64);
  }
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(message);
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
