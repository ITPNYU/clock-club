/* Clock Tick Demonstration

  An example of how to control an analog clock.
  To control an analog clock, you pulse the two pins of the solenoid,
  for 10 milliseconds, alternating which is pulsed.

  Based on an example by Matt Mets, completed in 2008
  This version refactored by Tom Igoe, 2017
*/

int clockPin1 = 4;           // connected to one side of the clock solenoid
int clockPin2 = 3;           // connected to the other
int pulsingPin = clockPin1;  // the pin you'll pulse next
long lastTick = 0;           // time of the last tick, in milliseconds

void setup() {
  pinMode(clockPin1, OUTPUT);   // make the solenoid pins outputs
  pinMode(clockPin2, OUTPUT);

  digitalWrite(clockPin1, LOW); // set them low (ground) as a default
  digitalWrite(clockPin2, LOW);
}

void loop() {
  if (millis() - lastTick > 1000) { // wait 1 second
    tick();                         // pulse clock motor
    lastTick = millis();            // record time of this tick
  }
}

void tick() {
  // pulse the clock solenoid to move the second hand.
  // 10 milliseconds seems to move it about 1 second on an Uno. Timing
  // may vary a few milliseconds from one clock model to another:
  digitalWrite(pulsingPin, HIGH);
  delay(10);
  digitalWrite(pulsingPin, LOW);

  // Change which solenoid pin is pulsed for next time:
  if (pulsingPin == clockPin1) {
    pulsingPin = clockPin2;
  } else {
    pulsingPin = clockPin1;
  }
}
