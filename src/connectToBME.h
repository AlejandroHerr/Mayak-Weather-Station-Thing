#ifndef CONNECT_TO_BME_H
#define CONNECT_TO_BME_H

#include <tuple>
#include <Wire.h>
#include <BME280I2C.h>

#include <MayakDisplay.h>

#define CONNECT_BME_TIMEOUT = 60;

struct ConnectToBMEResponse
{
  BME280I2C bme;
  char *error;
};

ConnectToBMEResponse makeConnectToBMEResponse(BME280I2C bme, char *error);

ConnectToBMEResponse connectoToBME(MayakDisplay mayakDisplay, uint8 timeout = 60);

struct GetBMEInfoResponse
{
  char *info;
  char *error;
};

GetBMEInfoResponse makeGetBMEInfoResponse(char *info, char *error);

GetBMEInfoResponse getBMEInfo(BME280I2C bme);

#endif /* CONNECT_TO_BME_H */
