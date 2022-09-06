#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <HttpClient.h>
#include <SPI.h>
#include <Wire.h>

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "LilMello";
const char* password = "MwS6Kv3zPw";
//Owie host IP
const char owieip[] = "192.168.4.1";
const char path[] = "/";
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);
// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

WiFiClient c;
HttpClient http(c);

//Boot Logo, change if you dont like it
static const unsigned char PROGMEM logo16_glcd_bmp[] = 
{  B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B01000000, B00000000, B00000000, B10000001, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B10000001, B00000000, B00000001,
  B10000110, B01001001, B01001100, B00010010, B01011101, B11011001, B01000110, B01010001,
  B10001001, B01010101, B01010010, B00010101, B01000010, B10100101, B10101001, B01100001,
  B10001001, B01010101, B01011110, B00010101, B01001110, B10100001, B00101111, B01000001,
  B10001001, B01010101, B01010000, B00010101, B01010010, B10100001, B00101000, B01000001,
  B10001001, B01010101, B01010010, B00010101, B01010010, B10100101, B00101001, B01000001,
  B10000110, B00100010, B01001100, B00001000, B10001110, B11011001, B00100110, B01000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10001111, B11111111, B11111111, B11100000, B00111111, B11111111, B11111111, B10000001,
  B10010000, B01000001, B00000100, B00010000, B01000001, B00000100, B00010000, B01000001,
  B10010000, B01000001, B00000100, B00010000, B01000001, B00000100, B00010000, B01000001,
  B10010000, B01000001, B00000100, B00010000, B01000001, B00000100, B00010000, B01000001,
  B10010000, B01000001, B00000100, B00011100, B01000001, B00000100, B00010000, B01110001,
  B10010000, B01000001, B00000100, B00011100, B01000001, B00000100, B00010000, B01110001,
  B10010000, B01000001, B00000100, B00011100, B01000001, B00000100, B00010000, B01110001,
  B10010000, B01000001, B00000100, B00011100, B01000001, B00000100, B00010000, B01110001,
  B10010000, B01000001, B00000100, B00011100, B01000001, B00000100, B00010000, B01110001,
  B10010000, B01000001, B00000100, B00011100, B01000001, B00000100, B00010000, B01110001,
  B10010000, B01000001, B00000100, B00010000, B01000001, B00000100, B00010000, B01000001,
  B10010000, B01000001, B00000100, B00010000, B01000001, B00000100, B00010000, B01000001,
  B10010000, B01000001, B00000100, B00010000, B01000001, B00000100, B00010000, B01000001,
  B10001111, B11111111, B11111111, B11100000, B00111111, B11111111, B11111111, B10000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
  B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111  };

//Basic setup to make sure you are aware of connection status before moving on
void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  Serial.println();
  display.display();
  display.clearDisplay();
  display.drawBitmap(0, 0,  logo16_glcd_bmp, 64, 48, 1);
  display.display();
  delay(2000);
  display.clearDisplay();

  WiFi.begin(ssid,password);

  Serial.print("Connecting");
  display.setTextSize(1);

  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Connecting");
  display.display();
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display();
  }
  Serial.println();
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Connected!IPAddress:");
  display.print(WiFi.localIP());
  display.display();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

//Loop for once everythings connected, scrape the Owie for battery info
void loop() {  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Querying");
  display.display();
  
  Serial.print("connecting to ");
  Serial.println(owieip);

  char owiehtml;
  owiehtml = checkOwie();

  
  Serial.print("Here's the webpage var");
  Serial.println(owiehtml);
  delay(30*1000); //run every 30s (in milliseconds)

}

int checkOwie(){  
  int err =0;
  char voltage;
  char bmssoc;
  char ovrsoc;
  char used;
  char regen;
  char webpage;

  err = http.get(owieip, path);
  if (err == 0)
  {
    Serial.println("startedRequest ok");

    err = http.responseStatusCode();
    if (err == 200)
    {
      Serial.print("Got status code: ");
      Serial.println(err);

      err = http.skipResponseHeaders();
      if (err >= 0)
      {
        int bodyLen = http.contentLength();
        Serial.print("Content length is: ");

        Serial.println(bodyLen);
        Serial.println();
        Serial.println("Body returned follows:");
      
        // Now we've got to the body, so we can print it out
        unsigned long timeoutStart = millis();
        // Whilst we haven't timed out & haven't reached the end of the body
        while ((http.connected() || http.available()) && ((millis() - timeoutStart) < kNetworkTimeout)){
            if (http.available())
            {
                webpage = http.read();
                // Print out this char
                bodyLen--;
                // We read something, reset the timeout counter  
                Serial.print("Heres the webpage content:");       
                Serial.print(webpage);
                timeoutStart = millis();
            }
            else
            {
                delay(kNetworkDelay);
            }
            Serial.print(webpage);
            return webpage;
        }
      }
      else{
        Serial.print("Failed to skip response headers: ");
        Serial.println(err);
      }
    }
    else{    
      Serial.print("Getting response failed: ");
      Serial.println(err);
    }
  }
  else{
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();
}
