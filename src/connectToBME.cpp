#include "connectToBME.h"
#include "MayakDisplay.h"

ConnectToBMEResponse makeConnectToBMEResponse(BME280I2C bme, char *error)
{
  ConnectToBMEResponse response = {bme, error};

  return response;
}

BME280I2C::Settings settings(
    BME280::OSR_X1,
    BME280::OSR_X1,
    BME280::OSR_X1,
    BME280::Mode_Forced,
    BME280::StandbyTime_1000ms,
    BME280::Filter_Off,
    BME280::SpiEnable_False,
    BME280I2C::I2CAddr_0x76 // I2C address. I2C specific.
);

ConnectToBMEResponse connectoToBME(MayakDisplay mayakDisplay, uint8 timeout)
{
  mayakDisplay.printConnectingToBME();

  Wire.begin();

  BME280I2C bme = BME280I2C(settings);

  uint8 counter = 0;
  bool timedOut = false;
  while (!bme.begin() && !timedOut)
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
    return makeConnectToBMEResponse(bme, (char *)"Could not find BME280I2C sensor!");
  }

  return makeConnectToBMEResponse(bme, nullptr);
}

GetBMEInfoResponse makeGetBMEInfoResponse(char *info, char *error)
{
  GetBMEInfoResponse response = {info, error};

  return response;
}

GetBMEInfoResponse getBMEInfo(BME280I2C bme)
{
  switch (bme.chipModel())
  {
  case BME280::ChipModel_BME280:
    return makeGetBMEInfoResponse((char *)"Found BME280 sensor! Success.", nullptr);
  case BME280::ChipModel_BMP280:
    return makeGetBMEInfoResponse((char *)"Found BMP280 sensor! No Humidity available.", nullptr);
  case BME280::ChipModel_UNKNOWN:
  default:
    return makeGetBMEInfoResponse(nullptr, (char *)"Found UNKNOWN sensor! Error!");
  }
}