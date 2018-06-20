
/*
  VID28-05 Motor Control

  Controls two stepper motors at once, used to drive a VID28-05 
  concentric shaft motor

  Created 24 May 2018
  by Tom Igoe

*/

#include <Stepper.h>

const int stepsPerRevolution = 750;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper hourMotor(stepsPerRevolution, 2, 3, 4, 5);
Stepper minuteMotor(stepsPerRevolution, 7, 8, 9, 10);

int hourSteps = 0;
int minuteSteps = 0;
int hourDir = 1;
int minuteDir = -1;

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
//  while (!Serial);

}

void loop() {
  // step one step:
  hourMotor.step(hourDir);
  minuteMotor.step(minuteDir);

  hourSteps += hourDir;
  hourSteps %= stepsPerRevolution;
  minuteSteps += minuteDir;
  minuteSteps %= stepsPerRevolution;
  Serial.print(hourSteps);
  Serial.print(",");
  Serial.println(minuteSteps);
  if (hourSteps == 0) {
    hourDir = -hourDir;
    delay(2000);
  }
  if (minuteSteps == 0) {
    minuteDir = -minuteDir;
  }
  delay(10);
}

