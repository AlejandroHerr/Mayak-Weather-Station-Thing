#include "connectToWifi.h"
#include "MayakDisplay.h"

char *connectWifi(MayakDisplay mayakDisplay, const char *ssid, const char *password, uint8 timeout)
{
  mayakDisplay.printConnectingToWifi();

#if defined(ESP8266) || defined(ESP32)
  WiFi.mode(WIFI_STA);
#endif
  WiFi.begin(ssid, password);
  Serial.println("");
  uint8 counter = 0;
  bool timedOut = false;
  while (WiFi.status() != WL_CONNECTED && !timedOut)
  {
    delay(1000);
    mayakDisplay.printProgress();
    counter += 1;
    if (counter >= timeout)
    {
      timedOut = true;
    }
  }

  if (timedOut)
  {
    return (char *)"Cannot connect to wifi";
  }

  return nullptr;
}