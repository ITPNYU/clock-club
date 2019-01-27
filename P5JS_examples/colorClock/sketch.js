/*
  Color Clock. Hours, minutes, seconds are all represented
  by the angle of their color on an HSV color wheel. 

  This is still a work in progress, I'm not happy with the look of it.

	created 26 Jan 2019
	by Tom Igoe
*/

function setup() {
	// set the general parameters for drawing:
	createCanvas(windowWidth, windowHeight);
	smooth();
}

function draw() {
	background(0); // white background
	// need the date to get milliseconds:
	let now = new Date();
	// get the seconds and milliseconds as a decimal number:
	let thisSecond = second() + now.getMilliseconds() / 1000;
	// get minutes and seconds as a decimal number:
	let thisMinute = minute() + thisSecond / 60;
	// get hours and minutes as a decimal number:
	let thisHour = hour() + thisMinute / 60;
	// set the sizes of the circles:
	let minuteHand = windowWidth*0.25;
	let hourHand = map(thisHour, 0, 23, 0, minuteHand*0.75);
	let secondHand = minuteHand * 1.05;

	// draw second circle:
	drawHand(thisSecond, secondHand, 60);
	// draw minute circle:
	drawHand(thisMinute, minuteHand, 60);
	// // draw hour circle:
	drawHand(thisHour, hourHand, 24);
}

// this function draws a hand, given the unit value, hand color, length,
// and how many divisions in a circle (e.g. minute: 60, hour: 12):
function drawHand(unitValue, handLength, divisions) {
	let h = map(unitValue, 0, divisions, 0, 360);
	let color = hsv2rgb(h, 1, 1);
	noStroke();
	fill(color); // set line color
	circle(width / 2, height / 2, handLength);
}


// Color conversion by Corey Forsyth: 
// https://medium.com/@bantic/hand-coding-a-color-wheel-with-canvas-78256c9d7d43
// hue in range [0, 360]
// saturation, value in range [0,1]
// return [r,g,b] each in range [0,255]
// See: https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
function hsv2rgb(hue, saturation, value) {
	let chroma = value * saturation;
	let hue1 = hue / 60;
	let x = chroma * (1 - Math.abs((hue1 % 2) - 1));
	let r1, g1, b1;
	if (hue1 >= 0 && hue1 <= 1) {
		([r1, g1, b1] = [chroma, x, 0]);
	} else if (hue1 >= 1 && hue1 <= 2) {
		([r1, g1, b1] = [x, chroma, 0]);
	} else if (hue1 >= 2 && hue1 <= 3) {
		([r1, g1, b1] = [0, chroma, x]);
	} else if (hue1 >= 3 && hue1 <= 4) {
		([r1, g1, b1] = [0, x, chroma]);
	} else if (hue1 >= 4 && hue1 <= 5) {
		([r1, g1, b1] = [x, 0, chroma]);
	} else if (hue1 >= 5 && hue1 <= 6) {
		([r1, g1, b1] = [chroma, 0, x]);
	}

	let m = value - chroma;
	let [r, g, b] = [r1 + m, g1 + m, b1 + m];

	// Change r,g,b values from [0,1] to [0,255]
	// return a p5.js color object:
	return color(255 * r, 255 * g, 255 * b);
}