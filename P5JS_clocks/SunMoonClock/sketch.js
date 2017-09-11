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
var clockRadius = 100;
var hourHand = 60;
var minuteHand = 90;
var secondHand = minuteHand;
var handStart = -10;
var moonRadius = 60;
var sunRadius = 18;
 var now = new Date('6/13/1967 00:03:00');
// var times = SunCalc.getTimes(birth, 40.879463, -73.416215);
//
// // get position of the sun (azimuth and altitude) at today's sunrise
// var sunPos = SunCalc.getPosition(birth, 40.879463, -73.416215);
// var moonPos = SunCalc.getMoonPosition(birth, 40.879463, -73.416215);
var sunPos, moonPos, moonIllumination, times;
var latitude = 40.879463;
var longitude = -73.416215;
var then = new Date('01/30/1967 19:17:00');

function setup() {
  // set the general parameters for drawing:
  createCanvas(320, 240);
  frameRate(1);
  smooth();
  strokeWeight(2);
  strokeCap(ROUND);
  //getLocation();
}

function draw() {
  background('#000'); //black background
  translate(width / 2, height / 2); // move to the center of the window
  rotate(3 * PI / 2); // rotate drawing 270 degrees to get 0 at the top

  // draw second hand:
  drawHand(second(), '#ccc', secondHand, 60);
  // draw minute hand:
  drawHand(minute(), '#ace', minuteHand, 60);
  // draw hour hand:
  drawHand(minute(), '#ace', hourHand, 12);

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
  times = SunCalc.getTimes(now, latitude, longitude);
  moonIllumination = SunCalc.getMoonIllumination(now);
  // get position of the sun (azimuth and altitude) at today's sunrise
  sunPos = SunCalc.getPosition(now, latitude, longitude);
  console.log(sunPos);
  moonPos = SunCalc.getMoonPosition(now,  latitude, longitude);
  console.log(moonPos);
}

function drawSun(pos) {
  var angle =  pos;
  var x = -clockRadius * cos(angle);
  var y = -clockRadius * sin(angle);
  noStroke();
  // dim the sun after sunset:
  if (now > times.sunrise && now < times.sunset) {
    fill('#ffff00'); // during the day, sun is brighter
  } else {
    fill('#555500'); // at night, sun is dimmed
  }
  ellipse(x,y, sunRadius, sunRadius);
}

function drawMoon(pos) {
  var angle =  pos;
  var x = -clockRadius * cos(angle);
  var y = -clockRadius * sin(angle);
  noStroke();
  if (now > times.night && now < times.sunriseEnd) {
    fill('#444'); // during the day, moon is dimmed
  } else {
    fill('#bbb'); // at night, moon is brighter
  }
  rotate(-3*PI/2);
  var moonAngle = moonIllumination.angle = moonPos.parallacticAngle;
  //rotate(moonAngle);
  console.log(moonAngle);
  ellipse(x,y, moonRadius, moonRadius);
  fill('#000');
  var fullness = map(moonIllumination.fraction, 0, 1, -moonRadius, moonRadius);
  // if fullness  is negative (waxing moon), you need to adjust the shadow:
  var adjustment = 1;
  if (fullness < 0) {
    adjustment = -adjustment;
  }
  // draw the leading edge of the shadow:
  arc(x,y, fullness, moonRadius, PI/2, 3*PI/2, PIE);
  // draw the back half of the shadow:
  arc(x,y, adjustment*moonRadius+adjustment, moonRadius+1, 3*PI/2, PI/2, PIE);
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
