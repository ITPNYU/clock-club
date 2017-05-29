/*
  Draws a clock. Draws the sun and moon position
	for your location and time as well.
	Outside radius arcs with seconds.

	Circle goes:
                3*PI/2 at the top
                      |
  PI on the left    - o -       0 on the right
                      |
                PI/2 at the bottom

Program works by rotating the drawing surface proportional to the angle
of each hand, then drawing the line for the hand.

Uses suncalc library by Vladimir Agafonkin: https://github.com/mourner/suncalc

created 29 May 2017
by Tom Igoe
*/

// parameters of the clock:
var clockRadius = 200;
var hourHand = 60;
var minuteHand = 90;
var secondHand = minuteHand;
var handStart = -10;
// var birth = new Date('6/13/1967 00:03:00');
// var times = SunCalc.getTimes(birth, 40.879463, -73.416215);
//
// // get position of the sun (azimuth and altitude) at today's sunrise
// var sunPos = SunCalc.getPosition(birth, 40.879463, -73.416215);
// var moonPos = SunCalc.getMoonPosition(birth, 40.879463, -73.416215);
var sunPos, moonPos, moonIllumination;
var now, latitude, longitude;

function setup() {
  // set the general parameters for drawing:
  createCanvas(windowWidth, windowHeight);
	frameRate(1);
  smooth();
  strokeWeight(2);
  strokeCap(ROUND);
	  getLocation();
}

function draw() {
  background('#000'); // white background
  translate(width / 2, height / 2); // move to the center of the window
  rotate(3 * PI / 2); // rotate drawing 270 degrees to get 0 at the top

  // draw second hand:
  drawHand(second(), '#ccc', secondHand, 60);
  // draw minute hand:
  drawHand(minute(), '#ace', minuteHand, 60);
  // draw hour hand:
  drawHand(minute(), '#ace', hourHand, 12);
  // draw arc from 0 to current second:
  push();
  stroke("#5597cf"); // set arc color
  noFill(); // no fill for the arc
  arc(0, 0, clockRadius, clockRadius, 0, second() * PI / 30);
  pop();
	calcPositions();
	drawSun(sunPos.azimuth);
	drawMoon(moonPos.azimuth);


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

function calcPositions() {
	 now = new Date();
 moonIllumination = SunCalc.getMoonIllumination(now);
	// get position of the sun (azimuth and altitude) at today's sunrise
	 sunPos = SunCalc.getPosition(now, latitude, longitude);
	 moonPos = SunCalc.getMoonPosition(now,  latitude, longitude);
}

function drawSun(pos) {
  push();
  rotate(3*PI / 2); // rotate so that 0 is in the right place
  rotate(pos + PI); // rotate for the tidal height and direction
  noStroke();
  fill('#ffff00'); // dot color
  ellipse(0, clockRadius / 2, 18, 18);	// radius 12px
  pop();
}

function drawMoon(pos) {
	push();
  rotate(3*PI / 2); // rotate so that 0 is in the right place
  rotate(pos + PI); // rotate for the tidal height and direction
  noStroke();
  fill('#999'); // dot color
  ellipse(0, clockRadius / 2, 12, 12); // radius 8px
	fill('#000');
	ellipse(-moonIllumination.fraction*12, (clockRadius / 2), 12, 12);
  pop();
}

function geoSuccess(position) {
   latitude = position.coords.latitude;
   longitude = position.coords.longitude;
}

function geoError(error) {
  print(error);
}

function getLocation() {
  if ("geolocation" in navigator) {
    navigator.geolocation.getCurrentPosition(geoSuccess, geoError);
  }
}
