# p5.js Analog Clock Examples

A collection of analog clock designs done in JavaScript using  [p5.js](https://p5js.org)

## Theory of Operation

The analog clocks in this directory use p5.js' rotate() command to rotate  each hand before drawing them. The radial coordinates work like so:
```
              3*PI/2 at the top
                    |
PI on the left    - o -       0 on the right
                    |
              PI/2 at the bottom
```
To get 0 at the top, the program rotates the whole drawing 3*PI/2 radians. This gives the following map:

```
                    0 at the top
                        |
3*PI/2 on the left    - o -       PI/2 on the right
                        |
                   PI at the bottom
```
Then the program rotates the drawing surface proportional to the angle of each hand, then drawing the line for the hand. The formula for rotating a given hand is dependent on the number of divisions of the circle needed (e.g. 12 for minutes and hours, 60 for seconds) and the actual value of the time unit in question. The formula is

unitValue * 2 * PI / number of divisions

For example, if it's 15 minutes past the hour, then:

15*2*PI / 60 = PI/2 = the hand is pointing to the right.

Te circle around the edge of [clock001](https://rawgit.com/ITPNYU/clock-club/master/P5JS_examples/clock001/index.html) is simply an arc starting at 0 and going to the position of the seconds.

## See the Clocks in Action

[clock001](https://rawgit.com/ITPNYU/clock-club/master/P5JS_examples/clock001/index.html) A basic analog clock with the hands offset from the center, and the seconds represented by an arc around the edge of the circle.

[SunMoonClock](https://rawgit.com/ITPNYU/clock-club/master/P5JS_examples/SunMoonClock/index.html) Some clocks depend on the position of the sun and the moon. The [suncalc](https://github.com/mourner/suncalc) library calculates these for you, using your [geolocation](https://developer.mozilla.org/en-US/docs/Web/API/Geolocation/Using_geolocation) and the time. This example draws a clock like the previous example, but also adds the moon and sun. It uses the [suncalc](https://github.com/mourner/suncalc) library and your geolocation to calculate the sun and moon's position (azimuth) relative to you. It then draws them in their proper positions for the current date and time, and your location. North is shown at the top of the clock.

[Decimal Clock](https://rawgit.com/ITPNYU/clock-club/master/P5JS_examples/decimalClock/index.html) - a clock based on the French revolution-era [decimal time scheme](https://en.wikipedia.org/wiki/Decimal_time).

[Color Clock](https://rawgit.com/ITPNYU/clock-club/master/P5JS_examples/colorClock/index.html) - a clock that tells time using the [HSV color wheel](https://www.researchgate.net/figure/HSV-color-wheel_fig6_228701246). Red is twelve o'clock, green is 4 o'clock, blue is seven o'clock. The inner circle is the hours, and grows over 24 hours. The middle circle is the minutes. The outer ring is the seconds.

See also Christer Nilsson's [Bezier Clock](https://christernilsson.github.io/Lab/2017/081-BezierClock/), which uses p5.js to make a clock of Bezier curves
