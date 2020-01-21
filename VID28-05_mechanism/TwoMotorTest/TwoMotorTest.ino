
/*
  VID28-05 Motor Control

  Controls two stepper motors at once, used to test a VID28-05 
  concentric shaft motor

  Created 24 May 2018
  modified 20 Jan 2020
  by Tom Igoe

*/

#include <Stepper.h>

const int stepsPerRevolution = 720;  // VID28-05 is 720 steps per revolution

// initialize the stepper library. 
// Any 8 pins will do. These numbers were used for the MKR Zero form factor:
Stepper hourMotor(stepsPerRevolution,A5, A6, 0, 1);
Stepper minuteMotor(stepsPerRevolution, 2,3,4,5);

int hourSteps = 0;
int minuteSteps = 0;
// motors will move in opposite directions:
int hourDir = -1;     
int minuteDir = 1;

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one step:
  hourMotor.step(hourDir);
  minuteMotor.step(minuteDir);

  hourSteps += hourDir;
  hourSteps %= stepsPerRevolution;
  minuteSteps += minuteDir;
  minuteSteps %= stepsPerRevolution;

  // reverse the hands on each revolution:
  if (hourSteps == 0) {
    hourDir = -hourDir;
    delay(2000);
  }
  if (minuteSteps == 0) {
    minuteDir = -minuteDir;
  }
  // arbitrary delay to test speed. 1.8ms seems to be the lower limit: 
  delayMicroseconds(1800);
}
