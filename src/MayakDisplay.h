#ifndef MAYAK_DISPLAY_H
#define MAYAK_DISPLAY_H

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <ESP32WiFi.h>
#else
#include <Wifi.h>
#endif
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "BME280Reading.h"

#define OLED_RESET 0 // GPIO0

class MayakDisplay
{
private:
  Adafruit_SSD1306 display;
  const char *header;
  void printHeader();

public:
  MayakDisplay(const char *header);
  void begin();
  void printConnectingToWifi();
  void printConnectedToWiFi(const char *ssid, IPAddress ipAddress);
  void printConnectingToBME();
  void printConnectedToBME(char *message);
  void printProgress();
  void printReading(BME280Reading BME280Reading);
  void printInfo(char *message);
  void printError(char *errorMessage);
};

#endif /* MAYAK_DISPLAY_H */