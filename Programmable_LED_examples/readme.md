# Programmable LED clocks

This directory contains examples for programming clocks from programmable LED arrays such as the WorldSemi WS2812 (aka NeoPixel, in Adafruit's branding) or APA's APA102 (or DotStar in Adafruit's branding). These LEDs come in a variety of forms, the most common being flexible strips, many of which come in multiples of 60, which are useful for making clocks.

The WS2812 LED protocol is slower than the APA102 protocol, but for small arrays (say, 120 LEDs or less), the speed doesn't affect the timing of a clock substantially.

This directory includes a few different examples:

[NeoPixel001](https://github.com/ITPNYU/clock-club/blob/master/NeoPixelClock/NeoPixelClock001/NeoPixelClock001.ino): a simple example using 60 LEDs, with different colors for hour, minute, second. This clock relies on the [millis()](https://www.arduino.cc/reference/en/language/functions/time/millis/) function in the [Arduino API](https://www.arduino.cc/reference/en/), so it can run on any board that can be programmed with the API.
