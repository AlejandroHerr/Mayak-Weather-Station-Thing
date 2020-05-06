
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BME280I2C.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MayakDisplay.h"
#include "connectToWifi.h"
#include "connectToBME.h"
#include "BME280Reading.h"
#include "BME280Thing.h"
#define SERIAL_BAUD 115200

const char *name = "mayak-xx";
const char *ssid = "ssid";
const char *password = "password";

MayakDisplay display(name);
BME280Reading reading = {.temp = NAN, .hum = NAN, .pres = NAN};

BME280I2C bme;
BME280Thing bme280Thing;

void printErrorAndDie(char *error)
{
  display.printError(error);
  while (1)
  {
    delay(1000);
  }
}
void setup()
{
  Serial.begin(SERIAL_BAUD);

  while (!Serial)
  {
  } // Wait
  display.begin();

  char *error = connectWifi(display, ssid, password);

  if (error)
  {
    printErrorAndDie(error);
  }

  display.printConnectedToWiFi(ssid, WiFi.localIP());

  delay(1000);

  ConnectToBMEResponse connectToBMEResponse = connectoToBME(display);

  if (connectToBMEResponse.error)
  {
    printErrorAndDie(connectToBMEResponse.error);
  }

  bme = connectToBMEResponse.bme;

  GetBMEInfoResponse getBMEInfoResponse = getBMEInfo(connectToBMEResponse.bme);

  if (getBMEInfoResponse.error)
  {
    printErrorAndDie(getBMEInfoResponse.error);
  }

  display.printInfo(getBMEInfoResponse.info);

  delay(1000);

  bme280Thing.setup(name, WiFi.localIP());
  bme280Thing.begin();
}

void updateBME280Data()
{
  bme.read(reading.pres, reading.temp, reading.hum, BME280::TempUnit_Celsius, BME280::PresUnit_hPa);
}

void loop()
{
  updateBME280Data();
  display.printReading(reading);
  bme280Thing.update(reading);
  delay(60000);
}