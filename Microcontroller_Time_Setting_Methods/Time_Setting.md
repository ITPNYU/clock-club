
## Methods For Setting The Time

Setting the time on any microcontroller-driven clock is an important task, one most people avoid when planning the clock.  This repo offers a couple of solutions to the problem of setting the time. Although there are good ways for dealing with time, these examples do not use them so that they can be adapted for any approach you want to take:

 Paul Stoffregen's [Time library](https://www.pjrc.com/teensy/td_libs_Time.html), uses the POSIX epoch string to set the time as a single number. Paul's Time library is the easiest way to deal with time if you're using a microcontroller with no realtime clock. It can also handle external realtime clocks as well. If you're using any of the microcontrollers with the ARM M0+ processor, the [Arduino RTC library](https://www.arduino.cc/en/Reference/RTC) does a good job as well.


1. Setting the time from the [compiler time string](https://github.com/ITPNYU/clock-club/blob/master/Programmable_LED_examples/CompileTimeSet/CompileTimeSet.ino). This uses the time from the computer that compiled your sketch to set the time. There are two special strings, ``__TIME__`` and ``__DATE__`` that you can use to get an initial time and date.
2. Setting the time from a [serial input string](https://github.com/ITPNYU/clock-club/blob/master/Programmable_LED_examples/StringTimeSet/StringTimeSet.ino). This idea, borrowed from Stoffregen's [TimeSerial example](https://github.com/PaulStoffregen/Time/blob/master/examples/TimeSerial/TimeSerial.ino) but using the format of the previous method, gets the time from a serial input string.
3. Setting the time from physical controls. [Pushbuttons](https://github.com/ITPNYU/clock-club/blob/master/Programmable_LED_examples/PushbuttonTimeSet/PushbuttonTimeSet.ino) and rotary encoders are common on inexpensive clocks. You can use these to change the time on your clock too.
