/*
Clock Animation Test
Circle goes:
3*PI/2 at the top
|
PI on the left    - o -       0 on the right
|
PI/2 at the bottom

Program works by rotating the drawing surface proportional to the angle
of each hand, then drawing the line for the hand.

created 22 Aug 2012
modified for image layers 7 May 2018
by Tom Igoe
*/

var hourImg;    // images to be displayed on each layer
var minuteImg;
var secondImg;

var hAlpha = 255; // transparency of the layers, from 0 (invisible) to 255 (opaque)
var mAlpha = 127;
var sAlpha = 100;

var h = 0;    // hour, minute, second
var m = 0;
var s = 0;
var speed = 30;     // frames per second
function preload() {
  // load the images:
  hourImg = loadImage('assets/hourLayer.png');
  minuteImg = loadImage('assets/minuteLayer.png');
  secondImg = loadImage('assets/secondLayer.png');
}

function setup() {
  // set the general parameters for drawing:
  createCanvas(windowWidth, windowHeight);
  frameRate(speed);
  smooth();
  imageMode(CENTER);
}

function draw() {
  background(255);                  // white background
  translate(width / 2, height / 2); // move to the center of the window
  rotate(3 * PI / 2);               // rotate drawing 270 degrees to get 0 at the top

  // draw hour layer:
  drawHand(h, hourImg, hAlpha, 12);
  // draw minute layer:
  drawHand(m, minuteImg, mAlpha, 60);
  // draw second layer:
  drawHand(s, secondImg, sAlpha, 60);

  s++;            // advance seconds
  if (s > 59) {   // on the top of the minute,
    m++;          // advance minutes
    s=0;          // reset secoonds
  }
  if (m > 59) {   // on the top of the hour
    h++;          // advance hours
    m=0;          // reset minutes
  }
  if (h > 11) {   // on the top of the clock
    h=0;          // reset hours
  }

}

// this function draws a hand, given the unit value, hand image, alpha
// and how many divisions in a circle (e.g. minute: 60, hour: 12):
function drawHand(unitValue, thisImage, alpha, divisions) {
  push();
  rotate(unitValue * 2 * PI / divisions); // rotate to draw hand
  //tint(255,255,255,alpha);
  image(thisImage, 0, 0);
  pop();
}
