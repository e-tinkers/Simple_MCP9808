/*
 *  Microchip MCP9808 Temperatuere Sensor Arduino Library
 *
 *  Author: Henry Cheung
 *  License: MIT
 *  Date: 27 Oct, 2020
 *  Datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf
 */

#ifndef SIMPLE_MCP9808_h
#define SIMPLE_MCP9808_h

#include "Arduino.h"
#include "Wire.h"

// MCP9808 I2C base address
#define MCP9808_ADDR 0x18

// MCP9808 registers
#define CONFIG_REG 0x01
#define UPPER_TEMP_REG 0x02
#define LOWER_TEMP_REG 0x03
#define CRITICAL_TEMP_REG 0x04
#define AMBIENT_TEMP_REG 0x05
#define MFR_ID_REG 0x06
#define DEV_ID_REG 0x07
#define RESOLUTION_REG 0x08

#define MFR_ID 0x0054
#define DEV_ID 0x04

// Revolution Mode, defined as Mode    Resolution  SampleTime
#define RES_P50 0x00          //  0    0.5°C       30 ms
#define RES_P25 0x01          //  1    0.25°C      65 ms
#define RES_P125 0x02         //  2    0.125°C     130 ms
#define RES_P0625 0x03        //  3    0.0625°C    250 ms

// Alert trigger bit mask
#define NO_ALERT 0x00
#define LOWER_TEMP_ALERT 0x20
#define UPPER_TEMP_ALERT 0x40
#define CRITICAL_TEMP_ALERT 0x80

#define SHUTDOWN_MODE 0x0100


class Simple_MCP9808
{
  public:
    Simple_MCP9808();
    bool begin(uint8_t address=MCP9808_ADDR);
    void setResolution(uint8_t resolution=RES_P0625);
    void setUpperTemperature(int16_t tUpper);
    void setLowerTemperature(int16_t tLower);
    void setCriticalTemperature(int16_t tCritical);
    int16_t getLowerTemperature();
    int16_t getUpperTemperature();
    int16_t getCriticalTemperature();
    int16_t getTemperature();
    uint8_t getDeviceID();
    uint8_t getRevision();
    uint16_t getManufacturerID();
    uint8_t alertTriggered();
    void shutdown();
    uint16_t status();

  private:
    uint8_t _i2cAddr;
    uint8_t _resolution;
    uint8_t _alert;
    uint8_t _deviceID;
    uint8_t _revision;
    uint16_t _manufacturerID;
    uint16_t _configuration;

    void _i2cWrite(uint8_t reg, uint8_t data);
    void _i2cWrite16(uint8_t reg, int16_t data);
    int16_t _i2cRead16(uint8_t reg);
    int16_t _readTemperatureData(uint8_t reg);
};
#endif
