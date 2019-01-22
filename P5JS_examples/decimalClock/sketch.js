/*
  Draws a clock in decimal time.
  Circle goes:  
                3*PI/2 at the top
                      |
  PI on the left    - o -       0 on the right
                      |
                PI/2 at the bottom
  
Program works by rotating the drawing surface proportional to the angle
of each hand, then drawing the line for the hand.

Metric formula from https://bijlmakers.com/metric-time/ 
For history of French decimal time, see http://mentalfloss.com/article/32127/decimal-time-how-french-made-10-hour-day,
https://io9.gizmodo.com/the-short-strange-history-of-decimal-time-5886129,
or https://en.wikipedia.org/wiki/Decimal_time

created 22 Aug 2012
modified to decimal 22 Jan 2019
by Tom Igoe
*/

// parameters of the clock:
var clockRadius = 200;
var hourHand = 60;
var minuteHand = 90;
var secondHand = minuteHand;
var handStart = -10;
var tickLength = 30;
var tickStart = clockRadius - 50;

function setup() {
  frameRate(120);
  // set the general parameters for drawing:
  createCanvas(windowWidth, windowHeight);
  smooth();
  strokeWeight(2);
  strokeCap(ROUND);
}

function draw() {
  let now = new Date();
  // add up seconds in the day so far:
  let secondsIntoDay = (now.getHours() * 3600)
    + (now.getMinutes() * 60)
    + now.getSeconds()
    + now.getMilliseconds() / 1000;
  // 1 decimal sec = 0.864 standard secs:
  let dSecsIntoDay = secondsIntoDay / 0.864;
  // hour = dsecs in day / 10000:
  let dHour = Math.floor(dSecsIntoDay / 10000);
  // subtract hours from total dSecs into day:
  let remaining = dSecsIntoDay - (10000 * dHour);
  // divide by 100 to get remaining in minutes:
  let dMinute = Math.floor(remaining / 100);
  // subtract minutes from remaining to get seconds:
  let dSecond = remaining - (100 * dMinute);

  background(255); // white background
  translate(width / 2, height / 2); // move to the center of the window
  rotate(3 * PI / 2); // rotate drawing 270 degrees to get 0 at the top

  var tickCount = 10;
  for (var t = 0; t < tickCount; t++) {
    drawMark(t, '#444', tickLength, 10);
  }

  // draw second hand:
  drawHand(dSecond, '#ccc', secondHand, 100);
  // draw minute hand:
  drawHand(dMinute, '#ace', minuteHand, 100);
  // draw hour hand:
  drawHand(dHour, '#ace', hourHand, 10);
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

// this function draws a hand, given the unit value, hand color, length,
// and how many divisions in a circle (e.g. minute: 60, hour: 12):
function drawMark(unitValue, tickColor, tickLength, divisions) {
  push();
  rotate(unitValue * 2 * PI / divisions); // rotate to draw hand
  stroke(tickColor); // set line color
  line(tickStart, 0, tickLength + tickStart, 0);
  pop();
}