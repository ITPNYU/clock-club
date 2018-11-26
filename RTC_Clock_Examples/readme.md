# Realtime Clock examples

These examples use the Arduino RTCZero library to keep time and date. The serial example includes the minimum setup for an RTC-based clock that keeps time and date.

These examples set the time and date on the clock using the compile time of the sketch.

## References

* [RTC library](https://www.arduino.cc/en/Reference/RTC)
* [LedDisplay library](https://github.com/PaulStoffregen/LedDisplay) for HCMS29xx displays
    * [Paul Stoffregen's page on the HCMS29xx displays](https://www.pjrc.com/teensy/td_libs_LedDisplay.html)
    * [Tom Igoe's page on the HCMS29xx displays](http://playground.arduino.cc/Main/LedDisplay)
* [Adafruit SSD1306 library](https://github.com/adafruit/Adafruit_SSD1306) for SSD1306 OLED displays

## Parts Used

* Arduino [MKRZero](https://store.arduino.cc/usa/arduino-mkrzero) - any of the [MKR](https://store.arduino.cc/usa/catalogsearch/result/?ie=UTF-8&oe=UTF-8&q=MKR&domains=&sitesearch=) boards will work as well.
* Avago [HCMS29xx LED display](https://sigma.octopart.com/23295/datasheet/Avago-HCMS-2973.pdf)
* [SSD1306 OLED display](https://octopart.com/search?q=hcms-2912&oq=hcms-2912&start=0) - available from multiple sources, such as [Adafruit](https://www.adafruit.com/product/931), [Amazon](https://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Daps&field-keywords=ssd1306&rh=i%3Aaps%2Ck%3Assd1306), [NewEgg](https://www.newegg.com/Product/Product.aspx?Item=9SIAGC17U22386), and others.
