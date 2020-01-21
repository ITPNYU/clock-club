
/*
  VID28-05 Motor Control

  Controls two stepper motors at once, used to test a VID28-05
  concentric shaft motor. Treats the inner hand as a minute hand,
  and the outer as a second hand.

  The hands move in an almost continous sweep in this example.

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
// motors will move in opposite directions:
int secondDir = 1;
int minuteDir = 1;

RTCZero rtc;
int lastSecond = -1;  // the previous second
int lastMinute = -1;  // the previous minute
long lastMove = 0;    // last time the hands were moved
int speedMillis = 81; // 0.08333s per step, approx.

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  // initialize the RTC:
  rtc.begin();
  rtc.setTime(0, 0, 0);
}

void loop() {
  int thisSecond = rtc.getSeconds();
  if (thisSecond != lastSecond) {
    // second hand should move 12 steps per second:
    secondSteps = 12;
    // move the minute hand 1 step every 5 seconds:
    if (thisSecond % 5 == 0) {
      minuteMotor.step(1);
    }
    lastSecond = thisSecond;
  }

  if (rtc.getMinutes() !=  lastMinute) {
    // move forward one minute
    lastMinute = rtc.getMinutes();
  }

  // move the second hand once evey 83.33ms (approx):
  if (millis() - lastMove > speedMillis) {
    if (secondSteps > 0) {
      secondMotor.step(1);
      secondSteps--;
    }
    lastMove = millis();
  }
}
