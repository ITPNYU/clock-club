
/*
  VID28-05 Motor Control

  Controls two stepper motors at once, used to test a VID28-05
  concentric shaft motor. Treats the inner hand as a minute hand,
  and the outer as a second hand.

  The second hand moves in discrete 6-degree (1-tick) steps in this example,
  and the minute hand moves in a continuous sweep.

  Doesn't use delays.

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

RTCZero rtc;
int lastSecond = -1;  // the previous second
int lastMinute = -1;  // the previous minute
long lastMove = 0;    // last time the hands were moved
int speedLimit = 83; // 83.33ms = 1rpm @ 720 steps/rev

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
    Serial.println(String(rtc.getMinutes()) + ":" + String(thisSecond));
    // second hand should move 12 steps per second:
    secondSteps = 12;
    // move the minute hand 1 step every 5 seconds:
    if (thisSecond % 5 == 0) {
      minuteMotor.step(1);
    }
    lastSecond = thisSecond;
  }

   // if 83ms have passed, move the hands:
  if (millis() - lastMove > speedLimit) {
    if (secondSteps > 0) {
      secondMotor.step(1);
      secondSteps--;
    }
  }
}
