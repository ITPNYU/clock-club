/*
   Clock setter from rotary encoder

   Reads a rotary encoder, sends -1 or 1 for every detent,
   and sends 0-3 when the button is pressed.

   Designed to set a clock. Works with the p5.js sketch in this same folder

   created 12 Oct 2021
   by Tom Igoe
*/

#include <Encoder.h>

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
  Serial.begin(9600);
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
      // button changed
      settingMode++;
      settingMode %= 4;
      
      // send settngMode value as a JSON string:
      Serial.print("{\"button\":");
      Serial.print(settingMode);
      Serial.println("}");
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

    // send encoder value as a JSON string:
    Serial.print("{\"encoder\":");
    Serial.print(encoderDirection);
    Serial.println("}");
    // save encoder position for next time through loop:
    lastPosition = newPosition;
  }
}
