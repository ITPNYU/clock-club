/* Clock Tick Demonstration

  An example of how to control an analog clock. 
  To control an analog clock, you pulse the two pins of the solenoid,
  for 10 milliseconds, alternating which is pulsed.
  
  Based on an example by Matt Mets, completed in 2008
  This version refactored by Tom Igoe, 2017
  
  
 */

 // Clock's solenoid is connected to these two pins, in any order:
int clockA = 4;
int clockB = 3;
 
int tickPin = clockA;    // This keeps track of which clock pin should be fired next.
 
 
// Initialize the IO ports
void setup()
{
  pinMode(clockA, OUTPUT);
  pinMode(clockB, OUTPUT);
 
  digitalWrite(clockA, LOW);
  digitalWrite(clockB, LOW);
}
 
// Main loop
void loop()
{
     tick();
     delay( random(1000));
}

// moves the clock forward one second:
void tick() {
  // Energize the electromagnet in the correct direction.
  digitalWrite(tickPin, HIGH);
  delay(15);
  digitalWrite(tickPin, LOW);  
 
  // Switch the direction so it will fire in the opposite way next time.
  if (tickPin == clockA)
  {
    tickPin = clockB;
  } else {
    tickPin = clockA;
  }
}
