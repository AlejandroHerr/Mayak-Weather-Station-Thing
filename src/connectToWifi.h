#ifndef CONNECT_TO_WIFI_H
#define CONNECT_TO_WIFI_H
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <ESP32WiFi.h>
#else
#include <Wifi.h>
#endif

#include <MayakDisplay.h>

#define CONNECT_WIFI_TIMEOUT = 60;

char *connectWifi(MayakDisplay mayakDisplay, const char *ssid, const char *password, uint8 timeout = 60);

#endif /* CONNECT_TO_WIFI_H */
