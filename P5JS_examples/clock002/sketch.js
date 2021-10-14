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

Arduino code for this example is in the sketch folder.

Uses p5.serialport.js library and the p5.serialcontrol app.

created 22 Aug 2012
re-written for P5.js 1 May 2016
adapted for serialport.js 12 Oct 2021
by Tom Igoe
*/

// variable to hold an instance of the serialport library:
let serial;
// HTML Select option object:
let portSelector;

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

  // new instance of the serialport library:
  serial = new p5.SerialPort();
  // callback function for serialport:
  serial.on('list', printList);
  serial.on('data', serialEvent);
  // list the serial ports:
  serial.list();
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
  arc(0, 0, clockRadius, clockRadius, 0, clockSecond * PI/30);
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

// make a serial port selector object:
function printList(portList) {
  // create a select object:
  portSelector = createSelect();
  portSelector.position(10, 10);
  // portList is an array of serial port names
  for (var i = 0; i < portList.length; i++) {
    // add this port name to the select object:
    portSelector.option(portList[i]);
  }
  // set an event listener for when the port is changed:
  portSelector.changed(mySelectEvent);
}

// populate the serial port selector:
function mySelectEvent() {
  let item = portSelector.value();
  // give it an extra property for hiding later:
  portSelector.visible = true;
  // if there's a port open, close it:
  if (serial.serialport != null) {
    serial.close();
  }
  // open the new port:
  serial.open(item);
}

function keyPressed() {
  // if port selector is visible, hide it, else show it:
  if (portSelector) {
    if (portSelector.visible) {
      portSelector.hide();
      portSelector.visible = false;
    } else {
      portSelector.show();
      portSelector.visible = true;
    }
  }
}

// if new serial data comes in:
function serialEvent() {
  let inData = serial.readLine();
  console.log(inData);
  if (inData) {
// if there's a string, convert it to a JSON object:
    let readings = JSON.parse(inData);

    // if there is a valid button reading:
    if (readings.button) {
      // change time setting mode:
      settingMode = readings.button;
    }
    // if there is a valid encoder reading:
    if (readings.encoder) {
      // add encoder value to current time property 
      // and % 60 or %12 as needed
      switch (settingMode) {
        case 1: // set seconds
          clockSecond += readings.encoder;
          clockSecond %= 60;
          // adjust for negative values:
          if (clockSecond < 0) {
            clockSecond += 60;
          }
          break;
        case 2: // set seconds
          clockMinute += readings.encoder;
          clockMinute %= 60;
          // adjust for negative values:
          if (clockMinute < 0) {
            clockMinute += 60;
          }
          break;
        case 3: // set seconds
          clockHour += readings.encoder;
          clockHour %= 12;
          // adjust for negative values:
          if (clockHour < 0) {
            clockHour += 12;
          }
          break;
      }
    }
  }
}