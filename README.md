# Simple MCP9808

Simple MCP9808 is a lightweight Arduino library for Microchip MCP9808 temperature sensor.

## Basic Usage

The usage of the library is extremely simple with just a few lines of code:
```
Simple_MCP9808 mcp;
if (mcp.begin()) {
  int16_t tempR = mcp.getTemperature();
  Serial.print("Temperature in Celsius: ");
  Serial.println(tempR / 16.0);
}
else {
  Serial.println("Unable to communicate with MCP9808 sensor");
}
```

See [basic.ino](https://github.com/e-tinkers/Simple_MCP9808/blob/master/examples/basic/basic.ino) for complete code.

## Check Alert Conditions
MCP9808 converts temperatures between -20°C and +100°C to a digital word with ±0.25°C/±0.5°C (typical/maximum) accuracy. There is a user-programmable temperature limits for temperature window limit (for upper and lower temperature limits) and critical temperature limit. The [check_alert](https://github.com/e-tinkers/Simple_MCP9808/blob/master/examples/check_alert/check_alert.ino) example demonstrated how to setup the lower-limit and upper-limit temperature as well as critical temperature threshhold, and how to evaluate the triggered alert status when an alert is triggered.

## Power-Saving Mode
MCP9808 offers sensor shutdown capability which disables all power consuming activities (including temperature sampling operations) while leaving the serial interface active, bring the shutdown current down to 0.1uA (typical) from typcial operating current of 200uA. This is a great feature for battery-powered temperature sensing. See [power_saving.ino](https://github.com/e-tinkers/Simple_MCP9808/blob/master/examples/power_saving/power_saving.ino) for the example.

## Reference
[MCP9808 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf).

## License
This library is released under MIT License.
