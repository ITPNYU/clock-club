/*
Draws a clock. Draws the sun and moon position
for your location and time as well.

Draws the sun and moon at their azimuth to you, with north at the top.

Uses suncalc library by Vladimir Agafonkin: https://github.com/mourner/suncalc

created 29 May 2017
updated 22 April 2018
by Tom Igoe
*/

// parameters of the clock:
var clockRadius = 100;
var hourHand = 60;
var minuteHand = 90;
var secondHand = minuteHand;
var handStart = -10;          // hands are slightly off-center
var moonRadius = 18;
var sunRadius = 30;
var now = new Date();
// position of the moon, sun, moon illumination, times of sunrise, sunset, etc.
// from suncalc library:
var sunPos, moonPos, moonIllumination, times;

// your position in the world. This determined all the suncalc data:
var latitude = 0;
var longitude = 0;

function setup() {
  // set the general parameters for drawing:
  createCanvas(windowWidth, windowHeight);
  frameRate(1);       // 1 second per frame.
  smooth();
  strokeWeight(2);
  strokeCap(ROUND);
  textAlign(CENTER);
  textFont('Helvetica');
  textStyle(NORMAL);

  // Turn on location watcher:
  if ("geolocation" in navigator) {
    var watcher = navigator.geolocation.watchPosition(geoSuccess, geoError);
  }
}

function draw() {
  background('#333'); //black background

  // mark north on the map:
  fill('#aaa');
  stroke('#aaa');
  let x = height / 2 - clockRadius * 2;
  triangle(width / 2, x, (width / 2) + 5, x + 20, (width / 2) - 5, x + 20);
  line(width / 2, x + 20, width / 2, x + 40);
  text('N', width / 2, x + 60);

  translate(width / 2, height / 2); // move to the center of the window
  rotate(3 * PI / 2); // rotate drawing 270 degrees to get 0 at the top

  // draw second hand:
  drawHand(second(), '#ccc', secondHand, 60);
  // draw minute hand:
  drawHand(minute(), '#ace', minuteHand, 60);
  // draw hour hand:
  drawHand(hour(), '#ace', hourHand, 12);

  // calculate sun and moon positions:
  calcPositions();
  // draw the sun and moon:
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

// calculate the sun and moon positions based on
// your position and the date and time:
function calcPositions() {
  // get current date and time:
  now = new Date();
  times = SunCalc.getTimes(now, latitude, longitude);
  moonIllumination = SunCalc.getMoonIllumination(now);
  // get position of the sun (azimuth and altitude) at today's sunrise:
  sunPos = SunCalc.getPosition(now, latitude, longitude);
  moonPos = SunCalc.getMoonPosition(now, latitude, longitude);
}

// draw the sun at its azimuth:
function drawSun(pos) {
  var angle = pos;
  var x = -clockRadius * 2 * cos(angle);
  var y = -clockRadius * 2 * sin(angle);
  noStroke();
  // dim the sun after sunset:
  if (now > times.sunrise && now < times.sunset) {
    fill('#ffff00'); // during the day, sun is brighter
  } else {
    fill('#555500'); // at night, sun is dimmed
  }
  // draw the sun:
  ellipse(x, y, sunRadius, sunRadius);
}

// draw the moon at its azimuth:
function drawMoon(pos) {
  var angle = pos;
  var x = -clockRadius * cos(angle);
  var y = -clockRadius * sin(angle);
  noStroke();
  // brighten the moon after moonrise:
  if (now > times.night && now < times.sunriseEnd) {
    fill('#444'); // during the day, moon is dimmed 
  } else {
    fill('#bbb'); // at night, moon is brighter
  }
  // rotate so zero is at the top:
  rotate(3 * PI / 2);
  push();
  // draw the bright part of the moon:
  ellipse(x, y, moonRadius, moonRadius);
  fill('#222');
  // fullness is a percentage, and its sign indicates waning (+) or waxing(-):
  var fullness = map(moonIllumination.fraction, 0, 1, -moonRadius, moonRadius);
  // if fullness is negative (waxing moon), you need to adjust the shadow:
  var adjustment = 1;
  if (fullness < 0) {
    adjustment = -adjustment;
  }
  // draw the leading edge of the shadow:
  // arc: x, y, width, height, start, stop, mode
  arc(x, y, fullness, moonRadius, PI / 2, 3 * PI / 2, PIE);
  // draw the back half of the shadow:
  arc(x, y, adjustment * moonRadius + adjustment, moonRadius + 1, 3 * PI / 2, PI / 2, PIE);
  pop();
}

// get your lat and long from the geolocation watcher:
function geoSuccess(position) {
  latitude = position.coords.latitude;
  longitude = position.coords.longitude;
}

function geoError(error) {
  console.log(error);
}
