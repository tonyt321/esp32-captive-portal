#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

// REPLACE WITH YOUR NETWORK CREDENTIALS
char* ssid = "owie-ssid";
char* password = "owie-wifi-password";
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

//Boot Logo, change if you dont like it
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b11000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b10000001, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000001, 0b00000000, 0b00000001,
  0b10000110, 0b01001001, 0b01001100, 0b00010010, 0b01011101, 0b11011001, 0b01000110, 0b01010001,
  0b10001001, 0b01010101, 0b01010010, 0b00010101, 0b01000010, 0b10100101, 0b10101001, 0b01100001,
  0b10001001, 0b01010101, 0b01011110, 0b00010101, 0b01001110, 0b10100001, 0b00101111, 0b01000001,
  0b10001001, 0b01010101, 0b01010000, 0b00010101, 0b01010010, 0b10100001, 0b00101000, 0b01000001,
  0b10001001, 0b01010101, 0b01010010, 0b00010101, 0b01010010, 0b10100101, 0b00101001, 0b01000001,
  0b10000110, 0b00100010, 0b01001100, 0b00001000, 0b10001110, 0b11011001, 0b00100110, 0b01000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000011, 0b11000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00001111, 0b11110000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00011100, 0b00111000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00111000, 0b00011100, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00110000, 0b00001100, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00011111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111000, 0b00000001,
  0b10000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00010000, 0b00000001,
  0b10000000, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00000001,
  0b10000000, 0b00000011, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00110000, 0b00001100, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00111000, 0b00011100, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00011100, 0b00111000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00001111, 0b11110000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000011, 0b11000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
  0b11000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011,
  0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111 };

void setup() {

  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.drawBitmap(0, 0,  logo16_glcd_bmp, 64, 48, 1);
  display.display();
  delay(2000);
  display.clearDisplay();

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid,password);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(1);
    display.setTextColor(WHITE,BLACK);
    
    display.setCursor(0, 0);
    Serial.print("[HTTP] begin...\n");

    http.begin(client, "http://192.168.4.1");

    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        int len = http.getSize();

#if 0
        // with API
        Serial.println(http.getString());
#else
        WiFiClient* stream = &client;
        
        while (http.connected() && (len > 0 || len == -1)) {
          char vbuff[5] = {0};
          char socbuff[4] = {0};
          char ovrbuff[4] = {0};
          display.setCursor(0, 0);
          stream->find("Voltage");
          while(stream->find("TOTAL_VOLTAGE\">")){
            stream->readBytesUntil('<',vbuff,5);
            Serial.print(vbuff);
            display.print("VOL:");
            display.print(vbuff);
            display.print("v");
            display.println();
            display.display();
            stream->find("BMS_SOC\">");
            stream->readBytesUntil('<',socbuff,4);
            display.println();
            display.print("BMS:");
            Serial.println();
            Serial.print(socbuff);
            display.print(socbuff);
            display.println();
            display.display();
            stream->find("OVERRIDDEN_SOC\">");
            stream->readBytesUntil('<',ovrbuff,4);
            Serial.println();
            Serial.print(ovrbuff);
            display.println();
            display.print("OVR:");
            display.print(ovrbuff);
            display.println();
            display.display();
            display.print("          ");
            display.display();
            display.setCursor(0, 41);
            delay(5 * 1000);
            display.print("REFRESH");
            display.display();
            Serial.print("REFRESH");
            delay(1 * 1000);
            display.print(".");
            Serial.print(".");
            display.display();
            delay(1 * 1000);
            display.print(".");
            Serial.print(".");
            display.display();
            delay(1 * 1000);
            display.print(".");
            Serial.print(".");
            display.display();
            delay(1 * 1000);
            return;
            }
        }
#endif
        Serial.println();
        Serial.print("[HTTP] connection closed or file end.\n");
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  Serial.print("RETRYING...");
  display.setCursor(0, 41);
  display.print("RETRYING  ");
  display.display();
  delay(30 * 1000);
}
