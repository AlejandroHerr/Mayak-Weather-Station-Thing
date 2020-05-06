#define LARGE_JSON_BUFFERS 1
// #define LARGE_JSON_DOCUMENT_SIZE 4096
// #define SMALL_JSON_DOCUMENT_SIZE 4096

#ifndef BME_280_THING_H
#define BME_280_THING_H
#include "Thing.h"
#include <WebThingAdapter.h>
#include "BME280Reading.h"
// const char *bme280Types[] = {"MultiLevelSensor", "Sensor", "TemperatureSensor", nullptr};

class BME280Thing
{
private:
  ThingDevice thing;
  ThingProperty temperatureProperty;
  ThingProperty pressureProperty;
  ThingProperty humidityProperty;
  WebThingAdapter *adapter;

public:
  BME280Thing();
  void setup(const char *name, IPAddress ipAddress);
  void begin();
  void update(BME280Reading bme280Reading);
};

#endif /* BME_280_THING_H */