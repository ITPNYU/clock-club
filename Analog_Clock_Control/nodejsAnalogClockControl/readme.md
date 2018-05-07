# Node.js Control of an Analog Clock

This program uses the [onoff](https://www.npmjs.com/package/onoff) package on a Raspberry Pi or BeagleBone to control an analog clock. To install, download this directory, cd into the downloaded directory, then:

``$ npm install``

Note that it won't install on any hardware that can't run the onoff package (like your laptop). You'll need to install on your Pi or BeagleBone itself.  To run:

``$ node gpioControl.js``

If your clock doesn't move well, try some of [these tips](../readme.md) to adjust your program.
