#include <Simple_MCP9808.h>

Simple_MCP9808 mcp; // Datasheet: https://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf

void setup() {
  Serial.begin(115200);
  Serial.println();

  // By default, MCP0808 I2C address is 0x18, if other address is used, instantiated
  // the sensor object with MCP9808 mcp(i2cAddr); See 3.0 PIN DESCRIPTION of datasheet
  if (!mcp.begin()) {
    Serial.println("Failed to communicate with MCP9808 sensor");
    while (1) { delay(10); }
  }

  // Be default MCP9808 resolutinon is set at 0.0625°C (i.e. 1/16 degree Celsius)
  // other lower resolutions can be set at RES_P50 (0.5°C), RES_P25(0.25°C) and
  // RES_P125(0.125°C)
  // mcp.setResolutionRegister(RES_P0625);

}

void loop() {

  int16_t tempR = mcp.getTemperature();
  Serial.print("Temperaure raw reading = ");
  Serial.println(tempR);

  float tempC = tempR/16.0;
  Serial.print("Temperature in Celsius = ");
  Serial.println(tempC);

  float tempF = tempR/16.0 * 9.0 / 5.0 + 32;
  Serial.print("Temperature in Fahrenheit = ");
  Serial.println(tempF);

  delay(5000);
}
