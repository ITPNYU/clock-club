# Tabletop Clock

_Ben Light & Tom Igoe, Jan. 2020_

This project is a tabletop clock, designed as a production example for our [Tangible Interaction](https://itp.nyu.edu/classes/tangible-interaction) class. We made it to demonstrate how to make a housing for an electronic device with tangible controls from a single block of wood. 

## Display and Controls
The device has an LCD screen that displays an analog clock face, two pushbuttons on the front face, and a recessed rotary encoder with pushbutton on the back face. It's powered by a 5-12V DC power jack in the back. 

The rotary encoder is used to set the time. Push the button once to set hours, twice to set minutes, and three times to set seconds. The appropriate clock hand will change colors when it's the hand to be set. In any of these modes, turn the encoder to move the clock hand. A fourth push puts the clock back into normal operating mode. 

The front pushbuttons control the brightness of the screen and the daylight savings mode. One button switches the hour hand back and forth from normal to daylight savings. The other toggles the display between a bright and a dim mode. The buttons light up when pressed, and fade on release.

## Housing
The housing was made from a clock of 4x4 maple that we bought from the art store across the street from our office. 

## Electronics
The clock runs on an Arduino [Nano 33 IoT](https://store.arduino.cc/usa/nano-33-iot). We chose this because it is a small form factor, has a built-in realtime clock, and a WiFi/Bluetooth radio that could be used to set the time wirelessly (that option is not currently implemented). 

The display is an LCD display from Tinkersphere, the [TS-336 TFT LCD display](https://tinkersphere.com/arduino-compatible-components/336-tft-lcd-display-22-arduino-compatible.html). This was our third choice. We settled on it because it was the best size for our housing, obtainable nearby, reasonably priced, and had an [available library with decent documentation](https://github.com/Nkawu/TFT_22_ILI9225) for graphics and text. 

The first display we looked at before that was the [SSD1306 OLED display](https://www.amazon.com/SSD1306/s?k=SSD1306), an inexpensive display with an I2C interface (and therefore requiring very few pins on the microcontroller). These displays are easy to use, and available from many retailers, but even the larger one was too small for our housing. The other display we considered was the [DFR0529](https://www.dfrobot.com/product-1794.html?search=DFR0529&description=true), a round TFT LCD display from DFRobot. The display was a good size for our housing, and a round display would have been ideal, but the [available library](https://github.com/DFRobot/DFRobot_ST7687S) was too slow to update the screen for our tastes, and we didn't have time to write a new library.

The rotary encoder was a [Bourns PEC11R-4220K-S0024](https://www.digikey.com/products/en?keywords=PEC11R-4220K-S0024-ND), bought through Digikey, which we had in stock. The pushbuttons were [16mm illuminated pushbuttons](https://www.adafruit.com/product/1477), bought through Adafruit, which we had in stock. We used them because we wanted to show how to use built-in LEDs.

## Programming

The [program](TabletopClock001) is written for the Nano 33 IoT, but it could run on any of the MKR boards, or presumably any Arduino-compatible that uses a SAMD processor with the realtime clock on board.