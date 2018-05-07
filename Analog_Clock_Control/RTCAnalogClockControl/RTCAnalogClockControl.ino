/* Clock Tick Demonstration

  An example of how to control an analog clock.
  To control an analog clock, you pulse the two pins of the solenoid,
  for 10 milliseconds, alternating which is pulsed.

  This version uses a realtime clock of an M0-based board
  to time the seconds.

  Based on an example by Matt Mets, completed in 2008, see
  http://www.cibomahto.com/2008/03/controlling-a-clock-with-an-arduino/

  This version adapted by Tom Igoe, 2018
*/
#include <RTCZero.h>
RTCZero rtc;

const int clockPin1 = 1;    // connected to one side of the clock solenoid
const int clockPin2 = 2;    // connected to the other
int pulsingPin = clockPin1; // the pin you'll pulse next
int lastSecond = 0;

void setup() {
  pinMode(clockPin1, OUTPUT);   // make the solenoid pins outputs
  pinMode(clockPin2, OUTPUT);
  digitalWrite(clockPin1, LOW); // set them low (ground) as a default
  digitalWrite(clockPin2, LOW);

  rtc.begin();              // start the realtime clock
  rtc.setTime(00, 00, 00);  // you don't care about the actual time
}


void loop() {
  // if the seconds have changed, pulse the solenoid:
  int thisSecond = rtc.getSeconds();
  if (thisSecond != lastSecond) {
    tick();
    Serial.println(thisSecond);
  }
  lastSecond = thisSecond;  // save current second for next comparison
}

void tick() {
  // pulse the clock solenoid to move the second hand.
  // 27 milliseconds seems to move it about 1 second on an M0. Timing
  // may vary a few milliseconds from one clock model to another:
  digitalWrite(pulsingPin, HIGH);
  delay(27);
  digitalWrite(pulsingPin, LOW);

  // Change which solenoid pin is pulsed for next time:
  if (pulsingPin == clockPin1)
  {
    pulsingPin = clockPin2;
  } else {
    pulsingPin = clockPin1;
  }
}
