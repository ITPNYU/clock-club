/*
  Rotary Encoder Time Set

  Sets the time using a rotary encoder and a pushbutton
  to set hours, minutes, and seconds. Pushing the button
  changes the property that you are changing.

  circuit:
  Arduino SAMD board (MKR series or Nano 33 IoT)

  Encoder attached to pins 2 and 3. Pushbutton attached to pin 4.
  Other side of pushbutton is connected to ground.
  Change pin numbers to suit your board.

  created 14 Dec 2019
  by Tom Igoe
*/
#include <Encoder.h>
#include <RTCZero.h>

const int buttonPin = 4;    // pushbutton pin
Encoder knob(6, 7);        // encoder on pins 2 and 3
int lastButtonState = LOW;  // last button state
int lastKnobState = -1;     // last knob state
int steps = 0;              // encoder step count

RTCZero rtc;
int currentProperty = 0;    // time property being changed
int lastSecond = 0;         // rtc.getSeconds()' previous value

void setup() {
  // initialize button pin and Serial and keyboard:
  pinMode(buttonPin, INPUT_PULLUP);
  rtc.begin();
  rtc.setTime(0, 0, 0);
  Serial.begin(9600);

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
    printTime();
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
  printTime();
}

void printTime() {
  // print the time:
  if (rtc.getHours() < 10) Serial.print("0");    // leading zero
  Serial.print(rtc.getHours());
  Serial.print(":");
  if (rtc.getMinutes() < 10) Serial.print("0");  // leading zero
  Serial.print(rtc.getMinutes());
  Serial.print(":");
  if (rtc.getSeconds() < 10) Serial.print("0");  // leading zero
  Serial.println(rtc.getSeconds());
}
