#include "MayakDisplay.h"

MayakDisplay::MayakDisplay(const char *deviceName) : display(OLED_RESET), header(deviceName)
{
}

void MayakDisplay::printHeader()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(header);
  display.println("-");
}

void MayakDisplay::begin()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 64x48)
  display.setRotation(90);
  display.display();
}

void MayakDisplay::printConnectingToWifi()
{
  display.clearDisplay();
  printHeader();
  display.setTextColor(WHITE); // 'inverted' text
  display.println("Connecting to WiFi");
  display.display();
}

void MayakDisplay::printConnectedToWiFi(const char *ssid, IPAddress ipAddress)
{
  display.clearDisplay();
  printHeader();
  display.setTextColor(BLACK, WHITE);
  display.println("WiFI");
  display.setTextColor(WHITE);
  display.println(ssid);
  display.print(ipAddress);
  display.display();
}

void MayakDisplay::printConnectingToBME()
{
  display.clearDisplay();
  printHeader();
  display.setTextColor(WHITE); // 'inverted' text
  display.println("Connecting to sensor");
  display.display();
}

void MayakDisplay::printConnectedToBME(char *message)
{
  display.clearDisplay();
  printHeader();
  display.setTextColor(BLACK, WHITE);
  display.println("SENSOR");
  display.setTextColor(WHITE);
  display.println(message);
  display.display();
}

void MayakDisplay::printProgress()
{
  display.print("#");
  display.display();
}

void MayakDisplay::printReading(BME280Reading BME280Reading)
{
  display.clearDisplay();
  printHeader();
  display.print("T: ");
  display.print(BME280Reading.temp); // display pressure in hPa
  display.println("C");
  display.print("P: ");
  display.print((int)BME280Reading.pres); // display pressure in hPa
  display.println("hPa");
  display.print("H: ");
  display.print(BME280Reading.hum); // display pressure in hPa
  display.println("%");
  display.display();
}

void MayakDisplay::printInfo(char *message)
{

  display.clearDisplay();
  printHeader();
  display.setTextColor(WHITE);
  display.println(message);
  display.display();
}

void MayakDisplay::printError(char *errorMessage)
{

  display.clearDisplay();
  printHeader();
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.print("ERROR");
  display.setTextColor(WHITE);
  display.print(" ");
  display.println(errorMessage);
  display.display();
}