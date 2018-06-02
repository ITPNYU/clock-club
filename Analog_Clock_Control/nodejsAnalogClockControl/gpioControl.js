/*
  node.js control of an analog clock using the GPIO pins of an
  embedded Linux processor. A Raspberry Pi or BeagleBone will work with this
  example.

  Uses the onoff.js package with node.js: https://www.npmjs.com/package/onoff#writevalue-callback

  created 28 April 2018
  by Tom Igoe
*/

var Gpio = require('onoff').Gpio; // include onoff library
var pin1 = new Gpio(23, 'out');   // set solenoid I/O pin as output
var pin2 = new Gpio(24, 'out');   // set solenoid I/O pin as output
var direction = 1;                // direction of the tick
var currentPin = pin1;            // current pin to be pulsed
var pulsewidth = 10;              // pin pulsewidth

// this function pulses each of two solenoid pins alternately.
// The pause between pulses causes the clock to move.
//  You may need to vary the pulsewidth depending on clock model.
function tick() {
  // this local function turns the current pin off and changes pins:
  function flipPin() {
    currentPin.writeSync(0);    // turn the current pin off
    if (currentPin === pin1) {  // change pins for next pulse
       currentPin = pin2;
    } else {
      currentPin = pin1;
    }
  }

  currentPin.writeSync(1);    // turn the current pin on
  setTimeout(flipPin, 10);    // wait  pulsewidth ms, then turn it off
}

// start the clock ticking once per second:
setInterval(tick, 1000);
