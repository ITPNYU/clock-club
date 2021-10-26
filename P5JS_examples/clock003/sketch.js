/*
  Draws a clock. Outside radius arcs with seconds
  Circle goes:  
                3*PI/2 at the top
                      |
  PI on the left    - o -       0 on the right
                      |
                PI/2 at the bottom
  
Program works by rotating the drawing surface proportional to the angle
of each hand, then drawing the line for the hand.

This version does not use the computer time. It takes input
from a serial port to set the time. It expects one of two JSON objects:
{"button": 0}  (can be 0-3)
{"encoder": 1}  (can also be -1)

If the button object is received, the sketch changes the setting mode:
mode 0: no setting
mode 1: set seconds from encoder
mode 2: set minutes from encoder
mode 3: set hours from encoder

If the encoder object is received, the sketch changes the current time
parameter using the value of the encoder.

Arduino code for this example is in the sketch folder. Only works on USB-native Arduinos

Uses input from the keyboard (WASD without the W): 
* d moves clock forward
* a moves it back
* s changes the mode

created 22 Aug 2012
re-written for P5.js 1 May 2016
adapted for serialport.js 25 Oct 2021
by Tom Igoe
*/


// parameters of the clock:
let clockRadius = 200;
let hourHand = 60;
let minuteHand = 90;
let secondHand = minuteHand;
let handStart = -10;

// time setting variables:
let settingMode = 0;
let clockSecond = 0;
let clockMinute = 0;
let clockHour = 0;
let lastSecond = 0;

function setup() {
  // set the general parameters for drawing:
  createCanvas(windowWidth, windowHeight);
  smooth();
  strokeWeight(2);
  strokeCap(ROUND);
}

function draw() {
  background(255); // white background
  translate(width / 2, height / 2); // move to the center of the window
  rotate(3 * PI / 2); // rotate drawing 270 degrees to get 0 at the top

  if (second() != lastSecond) {
    clockSecond++;
    if (clockSecond > 59) {
      clockMinute++;
      clockSecond %= 60;
    }
    if (clockMinute > 59) {
      clockHour++;
      clockHour %= 12;
      clockMinute %= 60;
    }
    // update the computer time:
    lastSecond = second();
  }
  // draw second hand:
  drawHand(clockSecond, '#ccc', secondHand, 60);
  // draw minute hand:
  drawHand(clockMinute, '#ace', minuteHand, 60);
  // draw hour hand:
  drawHand(clockHour, '#ace', hourHand, 12);

  // // draw arc from 0 to current second:
  push();
  stroke("#5597cf"); // set arc color
  noFill(); // no fill for the arc
  arc(0, 0, clockRadius, clockRadius, 0, clockSecond * PI / 30);
  pop();

}

// this function draws a hand, given the unit value, hand color, length,
// and how many divisions in a circle (e.g. minute: 60, hour: 12):
function drawHand(unitValue, handColor, handLength, divisions) {
  push();
  rotate(unitValue * 2 * PI / divisions); // rotate to draw hand
  stroke(handColor); // set line color
  line(handStart, 0, handLength + handStart, 0);
  pop();
}


function keyPressed() {
  // varible for changing the given hand:
  let changeValue = 0;

  switch (keyCode) {
    case 65: //a
      changeValue = -1;
      break;
    case 68: //s
      changeValue = 1;
      break;
    case 83: //d
      settingMode++;
      settingMode %= 4;
      break;
  }

  // add encoder value to current time property 
  // and % 60 or %12 as needed
  switch (settingMode) {
    case 1: // set seconds
      clockSecond += changeValue;
      clockSecond %= 60;
      // adjust for negative values:
      if (clockSecond < 0) {
        clockSecond += 60;
      }
      break;
    case 2: // set seconds
      clockMinute += changeValue;
      clockMinute %= 60;
      // adjust for negative values:
      if (clockMinute < 0) {
        clockMinute += 60;
      }
      break;
    case 3: // set seconds
      clockHour += changeValue;
      clockHour %= 12;
      // adjust for negative values:
      if (clockHour < 0) {
        clockHour += 12;
      }
      break;
  }
}