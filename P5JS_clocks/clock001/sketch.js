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
var clockRadius = 200;
var hourHand = 60;
var minuteHand = 90;
var secondHand = minuteHand;
var handStart = -10;

function setup() {
// set the general parameters for drawing:
  createCanvas(windowWidth, windowHeight);
  smooth();
  strokeWeight(2);
  strokeCap(ROUND);
}

function draw() {
  background(255);              // white background
  translate(width / 2, height / 2); // move to the center of the window
  rotate(3 * PI / 2);           // rotate drawing 90 degrees
  
  // draw second hand:
  push();
  rotate(second() * (PI / 30)); // rotate to draw second hand
  stroke('#ccc');               // set line color
  line(handStart, 0, secondHand + handStart, 0);  
  pop();

  // draw minute hand:
  push();
  rotate(minute() * PI / 30);   // rotate to draw minute hand
  stroke('#ace');               // set line color
  line(handStart, 0, minuteHand + handStart, 0);
  pop();
  
  // draw hour hand:
  push();                       
  rotate(hour() * (PI / 6));    // rotate to draw hour hand
  line(handStart, 0, hourHand + handStart, 0);
  pop();

  // draw arc from 0 to current second:
  push();
  stroke("#5597cf");            // set arc color
  noFill();                     // no fill for the arc
  arc(0, 0, clockRadius, clockRadius, 0, second() * PI / 30);
  pop();
}