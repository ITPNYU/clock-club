# Setting the time via WiFi

This example uses WiFi to connect to the network and get the time, then sets the RTC using the epoch at [this link]({{site.codeurl}}/Microcontroller_Time_Setting_Methods/WiFiTimeSet/WiFiTimeSet.ino). In this example, you can see some similar time difference calculations as those above in the [`getUptime` function (line 122)](https://github.com/ITPNYU/clock-club/blob/2e73d280f02625948d21c1e7ae69216f9e46cecc/Microcontroller_Time_Setting_Methods/WiFiTimeSet/WiFiTimeSet.ino#L122).  Because you're working in integers, the math can be simpler:

````arduino
unsigned long upTime = rtc.getEpoch() - startTime;
int upSecs = upTime % 60;
int upMins = (upTime % 3600L) / 60;
int upHours = (upTime % 86400L) / 3600;
int upDays = (upTime % 31556926L) / 86400L;
````
The `L` on the end of the constants is a C language formatting element indicating that they should be stored as long integers. 
