/*
   Clock setter from rotary encoder
   using Keyboard library

   Reads a rotary encoder, sends 'a' or 'd for every detent,
   and sends 's' when the button is pressed.

   Designed to set a clock. Works with the p5.js sketch in this same folder
  Only works on USB-native Arduinos.
  
   created 25 Oct 2021
   by Tom Igoe
*/

#include <Encoder.h>
#include <Keyboard.h>

// encoder on pins 2 and 3
Encoder myEncoder(2, 3);
// previous position of the encoder:
int lastPosition = 0;

// steps of the encoder's shaft:
int steps = 0;

const int buttonPin = 4;    // pushbutton pin
int lastButtonState = LOW;  // last button state
int debounceDelay = 5;       // debounce time for the button in ms
int settingMode = 0;        // settingMode = 0-3

void setup() {
  Keyboard.begin();
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  //  // if the button has changed:
  if (buttonState != lastButtonState) {
    // debounce the button:
    delay(debounceDelay);
    // if button is pressed:
    if (buttonState == LOW) {
      // button changed, send s to change modes:
      Keyboard.print("s");
    }
  }
  // save current button state for next time through the loop:
  lastButtonState = buttonState;

  // read the encoder:
  int newPosition = myEncoder.read();
  // compare current and last encoder state:
  int change = newPosition - lastPosition;
  // if it's changed by 4 or more (one detent step):
  if (abs(change) >= 4) {
    // get the direction (-1 or 1):
    int encoderDirection = (change / abs(change));

    // encoder changed, send a or s to change modes:
    if (encoderDirection == 1) {
      Keyboard.print("d");
    }
    if (encoderDirection == 1) {
      Keyboard.print("a");
    }
    // save encoder position for next time through loop:
    lastPosition = newPosition;
  }
}
