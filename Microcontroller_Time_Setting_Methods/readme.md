
# Methods For Setting The Time On A Microcontroller

Setting the time on any microcontroller-driven clock is an important task, one most people avoid when planning the clock.  This repo offers a couple of solutions to the problem of setting the time. 

 Paul Stoffregen's [Time library](https://www.pjrc.com/teensy/td_libs_Time.html) contains an example which uses the POSIX epoch string to set the time as a single number. Paul's Time library is the easiest way to deal with time if you're using a microcontroller with no realtime clock. It can also handle external realtime clocks as well. 
 
 If you're using the Nano 33 IoT, the MKR series Arduinos, or any of the microcontrollers with the ARM M0+ processor, the [Arduino RTC library](https://www.arduino.cc/en/Reference/RTC) does a good job as well.

There are a few ways of setting a realtime clock once you have one:

### Use the Compile Time

When your program compiles, the compiler records the time and date of compile in two special strings, ``__TIME__`` and ``__DATE__`` that you can use to get an initial time and date. You can see the value of these strings if you print them out. They look like this:

````
11:05:24
Apr  9 2023
````

Once you have them as String objects, you can search for the the substrings to get the time and date. That's what the [compiler time string]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/CompileTimeSet/CompileTimeSet.ino) example does. 

### Use a Serial Input String

You can send a serial input string into your microcontroller to set the time. This idea is borrowed from Stoffregen's [TimeSerial example](https://github.com/PaulStoffregen/Time/blob/master/examples/TimeSerial/TimeSerial.ino) but using the format of the previous method, gets the time from a serial input string. The POSIX `date` command gives you the time and date in any format you want. So, for example, on the command line of a Mac or Linux machine or WSL on Windows, you can type

````
date
````

and you'll get `Sun Apr  9 11:13:23 EDT 2023`

You can also format your date with the following modifiers:

* %C - century
* %Y - 4-digit year
* %y - 2-digit year (no century)
* %m - month
* %d - day
* %H - hour
* %M - minute
* %S - second

So for example, changing the command like so:
````
date "+%Y-%m-%d %H:%M:%S"  
````
gives you `2023-04-09 11:13:23`

That's an easy string to parse using the Arduino [Stream](https://reference.arduino.cc/reference/en/language/functions/communication/stream/) [parseInt](https://reference.arduino.cc/reference/en/language/functions/communication/stream/streamparseint/) function, and that is what the [StringTimeSet]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/StringTimeSet/) and [StringDateSet]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/StringDateSet/) examples do. 

The example [StringTimeSetNoRTC]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/StringTimeSetNoRTC/) shows you how to set the time with no real-time clock, and to track the time using only millis(). It's less accurate than an RTC-based clock. It's also subject to delays and other interruptions in your code, so it's not as good at keeping time long-term as a realtime clock. 

### Use a Physical Control

You can set the time with what most desktop clocks use: pushbuttons or rotary encoders. The examples 
[PushbuttonTimeSet]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/PushbuttonTimeSet/) and [EncoderTimeSet]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/EncoderTimeSet/) show you how to do just that. 

### Setting the Time via WiFi

If you're using the Arduino [WiFi101](https://www.arduino.cc/reference/en/libraries/wifi101/) or [WiFiNINA](https://docs.arduino.cc/tutorials/communication/wifi-nina-examples) libraries, you can get the time from the internet. The command `WiFi.getTime()` makes a call to a network time server to get the current epoch time. Then you can then set the RTC using the epoch.  It works like this:

````arduino
// check that you are connected:
if ( WiFi.status() == WL_CONNECTED) {
  // set the time from the network:
  unsigned long epoch;
  do {
    Serial.println("Attempting to get network time");
    epoch = WiFi.getTime();
    delay(2000);
  } while (epoch == 0);
// you got the time
Serial.println(epoch);
````

Once you've got it, you can set your realtime clock, assuming your clock library has a command to set the time from the UNIX epoch. For the RTCZero library, the command is setEpoch:
````arduino
  rtc.setEpoch(epoch);
````
For Stoffregen's time library, it's setTime:
````arduino
  rtc.setTime(epoch);
````
The example [WiFiTimeSet]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/WiFiTimeSet/) shows you how to set the RTCZero time using `WiFi.getTime()`.

### Timezones and Daylight Savings

If you set your time using `WiFi.getTime()`, you've got the time in Greenwich Mean time, GMT. You need to offset for your timezone. Depending on where you are in the world, you may need to adjust for daylight savings time too. The [Timezones_DaylightSavings]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/Timezones_DaylightSavings) example does this. It gives you a variable for your timezone relative to GMT, and it adjusts for daylight savings in the US, where daylight savings starts on the second Sunday in March and standard time starts on the first Sunday in November.
