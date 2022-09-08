#include <Arduino.h>
#include <U8g2lib.h>  //    https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>


ESP8266WiFiMulti WiFiMulti;

// REPLACE WITH YOUR NETWORK CREDENTIALS
char* ssid = "Owie-8282";
char* password = "";

String ssid1 = "null";
String ssid2 = "null";
String ssid3 = "null";
String ssid4 = "null";

// uncomment the one that works for your OLED if none check the U8G2 example codes
//                                              R is the rotation change to pick direction   R0,R1,R2,R3 
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);                        //1.3 inch  128x64 generic
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ D4);                                    //2.42 inch 128x64 generic


// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found



////////////////////////////////////////////////////////////////////////////////////////////
void wifiscan() 
{  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
              u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_lubI12_te);    // 15 high font
   u8g2.setCursor(0,24);
    u8g2.print ("no networks found");
  } while ( u8g2.nextPage() );
  
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" strength: ");
      Serial.print(WiFi.RSSI(i));
      Serial.print("   encrypt = ");
      Serial.println(WiFi.encryptionType(i));
        
      


if (WiFi.encryptionType(i) == 7) {

    u8g2.firstPage();do {
    u8g2.setFont(u8g2_font_lubI12_te);    // 15 high font
        //u8g2.setFont(u8g2_font_maniac_tf);dual outline font      //u8g2_font_inr33_t_cyrillic);//u8g2_font_maniac_tf//u8g2_font_maniac_tf//u8g2_font_freedoomr25_tn//u8g2_font_7Segments_26x42_mn
    u8g2.setCursor(0,24);
    u8g2.print (WiFi.SSID(i));
  } while ( u8g2.nextPage() );

  
  if (ssid1 == "null"){ssid1 = WiFi.SSID(i);
        Serial.print(" ssid1: "); Serial.println(WiFi.SSID(i)); goto wifilist;
}
  if (ssid2 == "null"){ssid2 = WiFi.SSID(i);
        Serial.print(" ssid2: "); Serial.println(WiFi.SSID(i)); goto wifilist;
}
  if (ssid3 == "null"){ssid3 = WiFi.SSID(i);
        Serial.print(" ssid3: "); Serial.println(WiFi.SSID(i)); goto wifilist;
}
  if (ssid4 == "null"){ssid4 = WiFi.SSID(i);
        Serial.print(" ssid4: "); Serial.println(WiFi.SSID(i)); goto wifilist;
}

 delay(2000);    
 
} // end of wifi list that has no password
   wifilist: {}
    
  }
}
}//end of wifi scan
  



//////////////////////////////
void displayip() 
{
  u8g2.firstPage();
  do {

    u8g2.setFont(u8g2_font_lubI12_te);    // 15 high font
        //u8g2.setFont(u8g2_font_maniac_tf);dual outline font      //u8g2_font_inr33_t_cyrillic);//u8g2_font_maniac_tf//u8g2_font_maniac_tf//u8g2_font_freedoomr25_tn//u8g2_font_7Segments_26x42_mn
    u8g2.setCursor(0,24);
    String IPaddress =  WiFi.localIP().toString();
    u8g2.print (IPaddress);
  } while ( u8g2.nextPage() );
}
///////////////////////////////////////////////////




void setup() {
Serial.begin(115200);
u8g2.begin();
u8g2.setFontMode(0);    // enable transparent mode, which is faster
  
displayip();
wifiscan();
  

  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // display.clearDisplay();
  //display.drawBitmap(0, 0,  logo16_glcd_bmp, 64, 48, 1);
  //display.display();
  delay(2000);
  //display.clearDisplay();

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid1,password);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    
  //  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //  display.setTextSize(1);
  //  display.setTextColor(WHITE,BLACK);
    
  //  display.setCursor(0, 0);
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
//          display.setCursor(0, 0);
          stream->find("Voltage");
          while(stream->find("TOTAL_VOLTAGE\">")){
            stream->readBytesUntil('<',vbuff,5);
            Serial.print(vbuff);
        //    display.print("VOL:");
       //     display.print(vbuff);
        //    display.print("v");
        //    display.println();
        //    display.display();
            stream->find("BMS_SOC\">");
            stream->readBytesUntil('<',socbuff,4);
         //   display.println();
         //   display.print("BMS:");
            Serial.println();
            Serial.print(socbuff);
         //   display.print(socbuff);
         //   display.println();
         //   display.display();
            stream->find("OVERRIDDEN_SOC\">");
            stream->readBytesUntil('<',ovrbuff,4);
            Serial.println();
            Serial.print(ovrbuff);
        //    display.println();
         //   display.print("OVR:");
         //   display.print(ovrbuff);
         //   display.println();
        //    display.display();
        //    display.print("          ");
         //   display.display();
        //    display.setCursor(0, 41);
            delay(5 * 1000);
        //    display.print("REFRESH");
        //    display.display();
            Serial.print("REFRESH");
            delay(1 * 1000);
        //    display.print(".");
            Serial.print(".");
       //     display.display();
            delay(1 * 1000);
        //    display.print(".");
            Serial.print(".");
        //    display.display();
            delay(1 * 1000);
        //    display.print(".");
            Serial.print(".");
       //     display.display();
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
 // display.setCursor(0, 41);
 // display.print("RETRYING  ");
 // display.display();
  delay(30 * 1000);
}