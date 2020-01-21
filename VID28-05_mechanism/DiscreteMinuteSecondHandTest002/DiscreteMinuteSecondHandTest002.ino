
/*
  VID28-05 Motor Control

  Controls two stepper motors at once, used to test a VID28-05
  concentric shaft motor. Treats the inner hand as a minute hand,
  and the outer as a second hand.

  The hands move in discrete 6-degree (1-tick) steps in this example.
  Uses delays.

  Created 20 Jan 2020
  by Tom Igoe
*/
#include <RTCZero.h>
#include <Stepper.h>
const int stepsPerRevolution = 720;  // VID28-05 is 720 steps per revolution

// initialize the stepper library.
// Any 8 pins will do. These numbers were used for the MKR Zero form factor:
Stepper secondMotor(stepsPerRevolution, A5, A6, 0, 1);
Stepper minuteMotor(stepsPerRevolution, 2, 3, 4, 5);

int secondSteps = 0;
int minuteSteps = 0;

RTCZero rtc;
int lastSecond = -1;  // the previous second
int lastMinute = -1;  // the previous minute
long lastMove = 0;    // last time the hands were moved

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  // initialize the RTC:
  rtc.begin();
  rtc.setTime(0, 0, 0);
}

void loop() {
  if (rtc.getSeconds() != lastSecond) {
    // second hand should move 12 steps per second:
    for (int s = 0; s < 12; s++) {
      secondMotor.step(1);
      delay(2);
    }
    lastSecond = rtc.getSeconds();
  }

  if (rtc.getMinutes() !=  lastMinute) {
    // minute hand should move 12 steps per minute:
    for (int s = 0; s < 12; s++) {
      minuteMotor.step(1);
      delay(2);
    }
    lastMinute = rtc.getMinutes();
  }
}
