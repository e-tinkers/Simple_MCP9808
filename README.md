# Simple MCP9808

Simple MCP9808 is a simple and lightweight Arduino library for Microchip MCP9808 temperature sensor.

## I2C address
By default, MCP9808 has an I2C address of 0x18, User-selectable address can be configurated through the A0-A2 pins of the chip, which alters the 3 least significant bits of the I2C address, giving the choise of I2C address betwen 0x18-0x1F. To use the alternative I2C address, call `MCP9808::begin(I2CAddr)` by passing in the I2CAddr instead of `MCP9808::begin()`.

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

## Alert with Pulling
MCP9808 converts temperatures between -20°C and +100°C to a digital word with ±0.25°C/±0.5°C (typical/maximum) accuracy. There is a user-programmable temperature limits for temperature window limit (for upper and lower temperature limits) and critical temperature limit. The [check_alert](https://github.com/e-tinkers/Simple_MCP9808/blob/master/examples/check_alert/check_alert.ino) example demonstrated how to setup the lower-limit and upper-limit temperature as well as critical temperature threshhold, the alert states is returned when reading a temperature, it can be used to evaluate whether the temperature has exceed the preset temperature window.

## Alert with Interrupt
MCP9808 offers an alert pin which can be used to trigger an interrupt when temperature drifts above or below TUPPER and TLOWER limits, or uses as a critical temperature-only output. In Interrupt mode, the alert pin can be set as active-low(default) or active-high. The microcontroller receiving the interrupt will have to acknowledge the interrupt by clearing the interrupt clear bit. The [alert_interrupt](https://github.com/e-tinkers/Simple_MCP9808/blob/master/examples/aleart_interrupt/alert_interrupt.ino) example demostrates the usage of interupt.

## Power-Saving Mode
MCP9808 offers sensor shutdown capability which disables all power consuming activities (including temperature sampling operations) while leaving the serial interface active, bring the shutdown current down to 0.1uA (typical) from typcial operating current of 200uA. This is a great feature for battery-powered temperature sensing. See [power_saving.ino](https://github.com/e-tinkers/Simple_MCP9808/blob/master/examples/power_saving/power_saving.ino) for the usage of `MCP9808::shutdown()`.

## Reference
[MCP9808 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/25095A.pdf).

## License
This library is released under MIT License.
