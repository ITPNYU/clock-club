/*
  Pushbutton Time Set

  Sets the time using three pushbuttons, one for hours, one for minutes,
  and one for seconds. Changes the hour or minute on button down.
  Resets the seconds to zero when the seconds button is held down.

  circuit:
  Pushbuttons connected to digital pins 2, 3, and 4. Other side
  of pushbuttons is connected to ground. Change pin numbers to suit
  your board.

  created 22 April 2018
  by Tom Igoe
*/

// pin numbers for buttons:
const int hourButton = 2;
const int minuteButton = 3;
const int secondButton = 4;

int prevHButton, prevMButton; // previous states of hour and minute buttons
// time
int hours = 0;
int minutes = 0;
int seconds = 0;
long lastCount = 0; // count of millis since last second

void setup() {
  pinMode(hourButton, INPUT_PULLUP);
  pinMode(minuteButton, INPUT_PULLUP);
  pinMode(secondButton, INPUT_PULLUP);

}

void loop() {
  // read hour and minute buttons:
  int hButtonState = digitalRead(hourButton);
  int mButtonState = digitalRead(minuteButton);

  // check for hour button state change:
  if (hButtonState != prevHButton) {  // if button changes
    delay(8);                         // wait for debounce delay
    if (hButtonState == LOW) {        // if button is pressed,
      hours++;                        // increment the hours
    }
  }
  prevHButton = hButtonState;    // save button state for next comparison

  // check for minute button state change:
  if (mButtonState != prevMButton) {  // if button changes
    delay(8);                         // wait for debounce delay
    if (mButtonState == LOW) {        // if button is pressed,
      minutes++;                      // increment the minutes
    }
  }
  prevMButton = mButtonState;    // save button state for next comparison

  // read seconds reset button. You don't care about
  // state change here, just hold the seconds at zero
  // while the button is pressed:
  if (digitalRead(secondButton) == LOW) {
    seconds = 0;
  }

  // count the milliseconds, update second when 1000ms have passed:
  if (millis() - lastCount > 1000) {
    seconds++;
    lastCount = millis();

    if (seconds > 59) {   // rollover seconds and update minutes
      seconds = 0;
      minutes++;
    }
    if (minutes > 59) {   // rollover minutes and update hours
      minutes = 0;
      hours++;
    }
    if (hours > 12) {     // rollover hours
      hours = 0;
    }
    // print the time:
    if (hours < 10) Serial.print("0");    // leading zero
    Serial.print(hours);
    Serial.print(":");
    if (minutes < 10) Serial.print("0");  // leading zero
    Serial.print(minutes);
    Serial.print(":");
    if (seconds < 10) Serial.print("0");  // leading zero
    Serial.println(seconds);
  }
}


