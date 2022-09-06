# OwieWatcher
[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/lolwheel/Owie)

todo
- use the u8g2 library better display support

A simple ESP8266 based sketch to connect to an [owie](https://github.com/tonyt321/OWIE-OLED) device and pull the battery info from the status webpage for output to an OLED display. The current code configuration outputs the Voltage, BMS SOC & OVERRIDEN SOC.

## Demo
<br>OwieWatcher bootup</p>
<p><img src="https://github.com/TurdSnack/owiewatcher/blob/main/Boot.gif" alt="BootDemo" width="200px">
<br>OwieWatcher refresh(every 10 seconds)</p>
<p><img src="https://github.com/TurdSnack/owiewatcher/blob/main/Refresh.gif" alt="RefreshDemo" width="200px">


## Setup
Download the `owie-watcher.ino` file and update the `ssid` & `password` variables. Then flash to your ESP8266, making sure you have the appropriate libraries downloaded.

## Required Libraries
* [ESP8266WiFi](https://github.com/esp8266/Arduino)
* [ESP8266WiFiMulti](https://github.com/esp8266/Arduino)
* [ESP8266HTTPClient](https://github.com/esp8266/Arduino)
* [Adafruit_SSD1306_Wemos_OLED](https://github.com/stblassitude/Adafruit_SSD1306_Wemos_OLED.git)
* [Adafruit-GFX](https://github.com/adafruit/Adafruit-GFX-Library)

## Parts
- [WeMos D1 Mini Clone](https://www.amazon.com/dp/B081PX9YFV/)
- [64x48 OLED Shield](https://www.amazon.com/gp/product/B01MZYYHHD/)
