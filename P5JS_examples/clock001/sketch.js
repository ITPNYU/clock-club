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

created 22 Aug 2012
re-written for P5.js 1 May 2016
by Tom Igoe
*/

// parameters of the clock:
var clockRadius = 150;
var hourHand = 50;
var minuteHand = 80;
var secondHand = minuteHand;
var handStart = -8;

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

  // draw second hand:
  drawHand(second(), '#ccc', secondHand, 60);
  // draw minute hand:
  drawHand(minute(), '#ace', minuteHand, 60);
  // draw hour hand:
  drawHand(hour(), '#ace', hourHand, 12);

  // draw arc from 0 to current second:
  push();
  stroke("#5597cf"); // set arc color
  noFill(); // no fill for the arc
  arc(0, 0, clockRadius, clockRadius, 0, second() * PI / 30);
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