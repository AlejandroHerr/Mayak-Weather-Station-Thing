#include "BME280Thing.h"

const char *bme280Types[] = {"MultiLevelSensor", nullptr};

BME280Thing::BME280Thing() : thing((const char *)"bme280", (const char *)"BME280 Weather Sensor", bme280Types),
                             temperatureProperty("temperature", "Temperature Reading", NUMBER, "LevelProperty"),
                             pressureProperty("pressure", "Pressure Reading", NUMBER, "LevelProperty"),
                             humidityProperty("humidity", "Humidity Reading", NUMBER, "LevelProperty")
{
  temperatureProperty.unit = "C";
  temperatureProperty.readOnly = true;
  temperatureProperty.title = "Temperature";

  pressureProperty.unit = "hPa";
  pressureProperty.readOnly = true;
  pressureProperty.title = "Pressure";

  humidityProperty.unit = "%";
  humidityProperty.readOnly = true;
  humidityProperty.maximum = 100;
  humidityProperty.minimum = 0;
  humidityProperty.title = "Humidity";

  thing.addProperty(&pressureProperty);
  thing.addProperty(&humidityProperty);
  thing.addProperty(&temperatureProperty);
}

void BME280Thing::setup(const char *name, IPAddress ipAddress)
{
  adapter = new WebThingAdapter(name, ipAddress);
  adapter->addDevice(&thing);
}

void BME280Thing::begin()
{
  adapter->begin();
}

void BME280Thing::update(BME280Reading bme280Reading)
{
  ThingPropertyValue value;

  value.number = bme280Reading.temp;
  temperatureProperty.setValue(value);
  value.number = bme280Reading.pres;
  pressureProperty.setValue(value);
  value.number = bme280Reading.hum;
  humidityProperty.setValue(value);

  adapter->update();
}
