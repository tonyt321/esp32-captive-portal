# OwieWatcher
A simple ESP8266 based setup to connect to an owie device and pull the battery info from the status webpage for output to an OLED display.

## Demo
<p><img src="https://i.imgur.com/LoV5n43.mp4" alt="BootDemo" width="282px"><p><img src="https://i.imgur.com/D6lNwEH.mp4" alt="RefreshDemo" width="282px">

## Setup
Download the `owie-watcher.ino` file and flash to your ESP8266, make sure you have the appropriate libraries downloaded.

## Required Libraries
* ESP8266WiFi
* ESP8266WiFiMulti
* ESP8266HTTPClient
* [Adafruit_SSD1306_Wemos_OLED](https://github.com/stblassitude/Adafruit_SSD1306_Wemos_OLED.git)
* [Adafruit-GFX](https://github.com/adafruit/Adafruit-GFX-Library)

## Parts
- [WeMos D1 Mini Clone](https://www.amazon.com/dp/B081PX9YFV/)
- [64x48 OLED Shield](https://www.amazon.com/gp/product/B01MZYYHHD/)
