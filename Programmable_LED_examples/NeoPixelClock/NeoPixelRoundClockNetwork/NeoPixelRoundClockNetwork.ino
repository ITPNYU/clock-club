/*
  Creates a clock using a string of 60 neoPixels. Uses RTCZero lib for time,
  So it needs a MKR1000, Zero, or other M0 based board.

  Uses Adafruit's NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel

  created 28 May 2016
  modified 14 Aug 2016
  by Tom Igoe
*/
#include <Adafruit_NeoPixel.h>
#include <RTCZero.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
WiFiUDP Udp;
char ssid[] = "tigoenet";  //  your network SSID (name)
char pass[] = "m30w-m30w";       // your network password

const int port = 8888;      // port on which this client receives


const int neoPixelPin = 5;  // control pin
const int numPixels = 60;    // number of pixels

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, neoPixelPin, NEO_GRB + NEO_KHZ800);

RTCZero rtc;
// colors

long hourColor = 0xAA77FF;
long minuteColor = 0x2222FF;
long secondColor = 0xFFFFFF;

long lastTick = 0; // Last second when the LEDs changed
String message = "";

void setup() {
  Serial.begin(9600);
  // get the time from the compiler. __TIME__ returns
  // a string of the time the sketch was compiled, as hh:mm:ss
  String compileTime = __TIME__;

  // while you're not connected to a WiFi AP:
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass); //   try to connect
    delay(2000);       // wait 2 seconds before trying again
  }
  printWifiStatus();

  Udp.begin(port);

  rtc.begin(); // initialize RTC
  setClock(compileTime);
  printTime();


  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // Initialize all pixels to 'off'
}

void loop() {
  // count the milliseconds, update second when 1000ms have passed:
  if (rtc.getSeconds() != lastTick) {
    lastTick = rtc.getSeconds();

    strip.clear();

    // calculate the beginning of the hour segment:
    int hourPosition = (rtc.getHours() % 12) * 5;      // every fifth pixel
    strip.setPixelColor(hourPosition, hourColor);
    strip.setPixelColor(rtc.getMinutes(), minuteColor);   // set minute pixel
    strip.setPixelColor(rtc.getSeconds(), secondColor);   // set second pixel
    strip.show();                             // refresh the strip
  }

  if (Udp.parsePacket() > 0) {    // check incoming message length
    // you have to call parsePacket() before available():
    while (Udp.available() > 0) {
      message = Udp.readStringUntil('\n'); // read a char
    }
    Serial.println(message);
    setClock(message);
    message = "";
  }
}

void printTime() {
  Serial.print(rtc.getHours());
  Serial.print(":");
  Serial.print(rtc.getMinutes());
  Serial.print(":");
  Serial.println(rtc.getSeconds());
}

void setClock(String currentTime) {
  int hours = -1;
  int minutes = -1;
  int seconds = -1;

  if (isDigit(currentTime.charAt(0)) &&
      isDigit(currentTime.charAt(1))) {
    hours =  currentTime.substring(0, 2).toInt();
  }

  if (isDigit(currentTime.charAt(3)) &&
      isDigit(currentTime.charAt(4))) {
    minutes =  currentTime.substring(3, 5).toInt();
  }

  if (isDigit(currentTime.charAt(6)) &&
      isDigit(currentTime.charAt(7))) {
    seconds =  currentTime.substring(6, 8).toInt();
  }

  if (hours < 0 || minutes < 0 || seconds < 0) {
    //Serial.println("invalid time");
    sendReply("invalid time");
  } else {
    rtc.setTime(hours, minutes, seconds);
    //Serial.println("set time OK");
    sendReply("set time to " + currentTime);
  }
}

void sendReply(String msg) {
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); // start a new packet
  Udp.print(msg);// add payload to it
  Udp.endPacket();                  // finish and send packet
}
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


