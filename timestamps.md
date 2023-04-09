# Tracking Time 

To keep track of time in a connected system, you need coordinated time.  Networked computers all use [Coordinated Universal Time (UTC)](https://www.timeanddate.com/worldclock/timezone/utc) these days, and most operating systems count time using the [Unix Epoch Time](https://www.epochconverter.com/), which counts the number of seconds since January 1, 1970. The international standard for representing time as a string is the [ISO8601](https://en.wikipedia.org/wiki/ISO_8601) standard, in which dates look like this: `2021-06-09T14:51:31Z`. The advantage of using these standards is that when you're transmitting time information from client to server, both sides can translate each others' times, and many programming environments include tools for calculating time differences in UTC. 

[Epoch Converter](https://www.epochconverter.com/) gives you calculators for understanding the relationship between Unix timekeeping and everyday timekeeping. When you're tracking the duration of an event, you often need to calculate hours, days, weeks, months, and years in terms of seconds or milliseconds Epoch Converter offers the following:

* 1 hour = 3600 seconds
* 1 day = 86400 seconds
* 1 week = 604800 seconds
* 1 month (30.44 days) = 2629743 seconds
* 1 year (365.24 days)  = 31556926 seconds

These numbers are key to calculating any time difference, as you'll see below. 

## Time and Date in JavaScript

In JavaScript, the [Date API](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Date), which is based on UTC, lets you get time, calculate differences between time, convert a time to your local timezone, etc. It can be used on the client side or the server side.

You can get the Unix epoch time using the JS Date API in a few ways:

````js
let myDate = new Date();
````

This will return a Date object, which will generally be represented by a string, like so: `Thu Apr 28 2022 09:42:51 GMT-0400 (Eastern Daylight Time)` Because it's a Date object, you can run the Date API functions on it. For example:

* `myDate.getDay()` returns 28
* `myDate.getMonth()` returns 3
* `myDate.getFullYear()` returns 2022
* `myDate.getHours()` returns 9
* `myDate.getUTCHours()` returns 13 (because UTC is measured from Greenwich Mean Time, GMT, and this date is in Eastern Daylight Time, or GMT-4).

There are many other commands in the Date API, allowing you to represent date and time in just about any way you want. You can also create Date objects and set the date using setter commands. Every getter command, such as `.getHours()`, has an equivalent setter (in this case, `.setHours()`).

You can also get the Unix time as a number of milliseconds like so:

````js
let myDate = Date.now();
````

The JS Date API uses milliseconds as its basis, not seconds, so to convert to epoch time, you need to divide by 1000. 

If you have two dates and you want to know the difference between them, apply the calculations above. For example:

````js
var now = new Date('3/12/97 1:23:45');
var then = new Date('3/31/93 13:23:00');
````
How far apart are these two date-times? It depends on your time scale. Start with the number of seconds in each time unit:

````js
const secondsInAnHour = 3600;
const secondsInADay = 86400;
const secondsInAWeek = 604800;
const secondsInAMonth = 2629743;
const secondsInAYear = 31556926;
````
Then calculate the difference using those:
````js
// JS gives you the values in milliseconds, so:
var difference = now - then;
// the total difference between now and then, in seconds (124545645):
var secondsDiff = (now - then) / 1000;
// in minutes (2075760.75):
var minutesDiff = secondsDiff / 60; 
// in hours (34596.0125):
var hoursDiff = secondsDiff / secondsInAnHour; 
// in days (1441.5005208333334):
var daysDiff = secondsDiff / secondsInADay; 
// in weeks (205.92864583333332):
var weeksDiff = secondsDiff / secondsInAWeek; 
// in months (47.36038654727857):
var monthsDiff = secondsDiff / secondsInAMonth; 
// in years (3.9466976282797632):
var yearsDiff = secondsDiff / secondsInAYear; 
````

What if you want to know the number of years, months, days, hours, minutes, and seconds between the two?  (It's  3 years, 11 months, 10 days, 12 hours, 0 minutes, and 45 seconds). For that, you need to break the difference down into parts. To do that for any given time unit, take the remainder (the modulo value) of the value in seconds divided by the number of seconds in that unit.  Then divide by the length in seconds of a unit you want. Finally, round it to get rid of the fraction, using `Math.floor()`.

Here it is, one unit at a time:

````js
var years = Math.floor(secondsDiff / secondsInAYear);
var months = Math.floor((secondsDiff % secondsInAYear) / secondsInAMonth);
var weeks = Math.floor((secondsDiff % secondsInAYear) / secondsInAWeek);
var days = Math.floor((secondsDiff % secondsInAMonth) / secondsInADay);
var hours = Math.floor((secondsDiff % secondsInADay) / secondsInAnHour);
var minutes = Math.floor((secondsDiff % secondsInAnHour) / 60);
var seconds = Math.floor((secondsDiff % 60));
````

When you've got all of that, print it out:
````js
console.log(years + ' years '
+ months + ' months '
+ days + ' days '
+ hours + ' hours ' 
+ minutes + ' minutes '
+ seconds + ' seconds');
````
 You should get `3 years 11 months 10 days 12 hours 0 minutes 45 seconds`.

[Here is a node server](https://github.com/tigoe/NodeExamples/tree/main/TimeServer) that gets the time from its host computer using the JavaScript Date commands.

## Time Logging on the Microcontroller

When you're datalogging, it's often necessary to attach a time stamp to each set of sensor readings, and you need coordinated time for that. The simplest solution if you're logging sensor data to a web server via WiFi is to let the server timestamp each reading. However, there may be reasons to time stamp locally by the microcontroller as well. If that is the case, then you want to attach a real-time clock to the microcontroller, or use a controller with one built-in, like the Nano 33 IoT or the MKR boards. The [RTCZero]((https://www.arduino.cc/reference/en/libraries/rtczero/)) library lets you access that realtime clock, and the WiFi libraries let you set the clock by making a network time server request, using the command `WiFi.getTime()`. 

On the Arduino SAMD boards (Nano 33 IoT, BLE, MKR boards), there is a Real-time Clock that allows you to keep time in hours, minutes and seconds. the RTCZero library allows you to access this feature of the microcontroller. There several examples for setting the time using this library in [this repository](Microcontroller_Time_Setting_Methods). There is an example which uses WiFi to connect to the network and get the time, then sets the RTC using the epoch at [this link]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/WiFiTimeSet/WiFiTimeSet.ino). In this example, you can see some similar time difference calculations as those above in the [`getUptime` function (line 122)](https://github.com/ITPNYU/clock-club/blob/2e73d280f02625948d21c1e7ae69216f9e46cecc/Microcontroller_Time_Setting_Methods/WiFiTimeSet/WiFiTimeSet.ino#L122).  Because you're working in integers, the math can be simpler:

````arduino
unsigned long upTime = rtc.getEpoch() - startTime;
int upSecs = upTime % 60;
int upMins = (upTime % 3600L) / 60;
int upHours = (upTime % 86400L) / 3600;
int upDays = (upTime % 31556926L) / 86400L;
````
The `L` on the end of the constants is a C language formatting element indicating that they should be stored as long integers. 

In a connected system, it's better to let the server keep track of timestamps, since it's the one running all the time. But when you need to keep a client device up and running, the RTC library is very useful. Without it, you're constantly checking with the server or with a time server for the correct time. 
