
/*
  Stepper Motor Control - one step at a time

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.

  The motor will step one step at a time, very slowly.  You can use this to
  test that you've got the four wires of your stepper wired to the correct
  pins. If wired correctly, all steps should be in the same direction.

  Use this also to count the number of steps per revolution of your motor,
  if you don't know it.  Then plug that number into the oneRevolution
  example to see if you got it right.

  Created 30 Nov. 2009
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
  delay(50);
}

