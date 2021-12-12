/*
 *  Microchip MCP9808 Temperatuere Sensor Arduino Library
 *
 *  Author: Henry Cheung
 *  License: MIT
 *  Date: 27 Oct, 2020
 *  Datasheet: https://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf
 */

#include "Simple_MCP9808.h"

Simple_MCP9808::Simple_MCP9808() {
  _i2cAddr = MCP9808_ADDR;
  _resolution = RES_P0625;
  _alert = NO_ALERT;
}

void Simple_MCP9808::_i2cWrite(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(_i2cAddr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

void Simple_MCP9808::_i2cWrite16(uint8_t reg, int16_t data) {
    Wire.beginTransmission(_i2cAddr);
    Wire.write(reg);
    Wire.write( (uint8_t) (data >> 8) );
    Wire.write( (uint8_t) (data & 0xff) );
    Wire.endTransmission();
}

int16_t Simple_MCP9808::_i2cRead16(uint8_t reg) {
  Wire.beginTransmission(_i2cAddr);
  Wire.write(reg);
  Wire.endTransmission();

  // conversion time depend on resolution
  int ms[4]={30, 65, 130, 250};
  delay(ms[_resolution]);

  int16_t data = 0;
  Wire.requestFrom(_i2cAddr, (uint8_t) 0x02);
  if(Wire.available() == 2) {
    data = (Wire.read() << 8);
    data |= Wire.read();
  }

  return data;
}

int16_t Simple_MCP9808::_readTemperatureData(uint8_t reg) {

  int16_t data = _i2cRead16(reg);

  // bit 15 - 13 represent temp boundaries set by tCritical ,tUpper and tLower
  if (reg == AMBIENT_TEMP_REG) {
    _alert = (uint8_t) (data >> 8) & (CRITICAL_TEMP_ALERT | UPPER_TEMP_ALERT | LOWER_TEMP_ALERT);
  }

  data &= 0x1FFF;
  //if sign bit is set, convert the two's complement value to a negative number
  if (data & 0x1000) {
    data = -( (~data & 0xfff) + 1 );
  }

  return data;
}

/*
 Initialize MCP9808 to Continuous conversion mode, Alert disabled, Power-up default
 Also read the manufacturer ID (0x0054) to see if device can be read correctly
 */
bool Simple_MCP9808::begin(uint8_t address) {
  if (address != MCP9808_ADDR)
    _i2cAddr |= (address & 0x1F);

  Wire.begin();
  Wire.setClock(400000L);

  setConfiguration(0x0000);

  _manufacturerID = _i2cRead16(MFR_ID_REG);

  int16_t dev = _i2cRead16(DEV_ID_REG);
  _deviceID = (uint8_t) (dev >> 8);
  _revision = (uint8_t) (dev & 0xff);

  return (_manufacturerID == MFR_ID && _deviceID == DEV_ID);
}

/* Set Resolution Register - default on power-up is 0.0625°C */
void Simple_MCP9808::setResolution(uint8_t resolution) {
  if ( (resolution >= RES_P50) && (resolution <= RES_P0625) ) {
    _i2cWrite(RESOLUTION_REG, resolution);
  }
}

void Simple_MCP9808::setConfiguration(uint16_t config) {
  _i2cWrite16(CONFIG_REG, config);
}

/* uppder temperature limit is 11-bit with 0.250°C precision */
void Simple_MCP9808::setUpperTemperature(int16_t tUpper) {
  _i2cWrite16(UPPER_TEMP_REG, tUpper << 4);
}

void Simple_MCP9808::setLowerTemperature(int16_t tLower) {
  _i2cWrite16(LOWER_TEMP_REG, tLower << 4);
}

void Simple_MCP9808::setCriticalTemperature(int16_t tCritical) {
  _i2cWrite16(CRITICAL_TEMP_REG, tCritical << 4);
}

/*
Get Raw Temperature Reading
the raw temperature value returned is in integer with 4-decimal point precision
To get actual temperature value in Celsius, divide it by 16
*/
int16_t Simple_MCP9808::getTemperature() {
  return _readTemperatureData(AMBIENT_TEMP_REG);
}

int16_t Simple_MCP9808::getLowerTemperature() {
  return _readTemperatureData(LOWER_TEMP_REG);
}

int16_t Simple_MCP9808::getUpperTemperature() {
  return _readTemperatureData(UPPER_TEMP_REG);
}

int16_t Simple_MCP9808::getCriticalTemperature() {
  return _readTemperatureData(CRITICAL_TEMP_REG);
}

uint8_t Simple_MCP9808::getDeviceID() {
  return _deviceID;
}

uint8_t Simple_MCP9808::getRevision() {
  return _revision;
}

uint16_t Simple_MCP9808::getManufacturerID() {
  return _manufacturerID;
}

uint8_t Simple_MCP9808::alertStates() {
  return _alert;
}

/* Set SHDN bit of Config Register */
void Simple_MCP9808::shutdown() {
  _i2cWrite16(CONFIG_REG, SHUTDOWN_MODE);
}

uint16_t Simple_MCP9808::getConfiguration() {
  return _i2cRead16(CONFIG_REG);
}
