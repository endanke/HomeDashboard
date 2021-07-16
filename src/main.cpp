#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJSON.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"
#include "display/Composer.h"
// Screen includes
#define LILYGO_T5_V213
#include "boards.h"
#include <GxEPD.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

GxIO_Class io(SPI,  EPD_CS, EPD_DC,  EPD_RSET);
GxEPD_Class display(io, EPD_RSET, EPD_BUSY);

int wifiClientConnectionTimeoutSeconds = 3;

WiFiUDP ntpUDP;
Composer composer;
String displayText;

void clearAndPrint(const String& text) {
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(0, 20);
  display.println(text);
  display.update();
}

void setup() {
  SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
  display.init();
  display.eraseDisplay();
  display.setTextSize(1);
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  clearAndPrint("Connecting to WiFi");

  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  int retryIntervalMs = 500;
  int timeoutCounter = wifiClientConnectionTimeoutSeconds * (1000 / retryIntervalMs);
  while (WiFi.status() != WL_CONNECTED && timeoutCounter > 0)
  {
    delay(retryIntervalMs);
    if (timeoutCounter == (wifiClientConnectionTimeoutSeconds * 2 - 3)) {
      WiFi.reconnect();
    }
    timeoutCounter--;
    Serial.print(".");
  }

  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  clearAndPrint("Waiting for data");
  composer.setup();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
      WiFi.reconnect();
  }

  composer.loop();

  if (displayText != composer.displayText && composer.displayText != "") {
    displayText = composer.displayText;
    clearAndPrint(displayText);
  }

  delay(300);
}