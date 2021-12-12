/*
 *                     3.3V or 5V
 *                          |
 *     2k(5V) or 1k(3.3v)  |-|
 *      resistor           | |
 *                         |-|
 *                          |
 *                         _|_
 *      LED (Optional)     \ /
 *                         -|-
 *                          |
 *      MCP9808 Pin 3 >-----|-----> MCU GPIO Pin (e.g. Pin 5)
 *
 * This example requires to connect MCP9808 alert pin (pin 3) to a MCU GPIO pin
 * (pin 5 is used in this example), a Pull-up resistor is also required, the LED
 * is optional but it help to observer when the interrupt happened.
 */
#include <Simple_MCP9808.h>

#define ALERT_PIN 5 // Use any GPIO pin you prefer
#define LOWER_LIMIT_TEMPERATURE -20
#define UPPER_LIMIT_TEMPERATURE 100

volatile bool isrFlag = false;
unsigned long startT = 0;

Simple_MCP9808 mcp;

void alertISR() {
  isrFlag = true;
}

void readTemperature() {
  Serial.print("Temperature in Celsius = ");
  Serial.println(mcp.getTemperature()/16.0);
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  if (mcp.begin()) {
    // Setup temperature threshholds
    mcp.setLowerTemperature(LOWER_LIMIT_TEMPERATURE);
    mcp.setUpperTemperature(UPPER_LIMIT_TEMPERATURE);
    mcp.setCriticalTemperature(32);  // set Critial Temperature for triggering interrupt

    // See page 19 of MCP9808 on more details about Alert configuration options
    // Enable Interrupt with Tl < T, T > Tu, or T > Tc, ALERT_PIN=active-low (bit 1)
    // mcp.setConfiguration(mcp.getConfiguration() | 0x0009);

    // Enable Interrupt with T > Tc only, ALERT_PIN=active-low (bit 1)
    mcp.setConfiguration(mcp.getConfiguration() | 0x000d);
    
    attachInterrupt(digitalPinToInterrupt(ALERT_PIN), alertISR, FALLING);

    readTemperature();
  }
  else {
    Serial.println("Failed to communicate with MCP9808 sensor");
    while(1) { delay(10); }
  }
}

void loop() {
  if (millis() - startT > 2000) {
    readTemperature();

    // if interrupt isrFlag is set and T < Ta (i.e. no more alert)
    // then clear the interrupt flag and reset the isrFlag
    if (isrFlag && !mcp.alertStates()) {
      isrFlag = false;
      mcp.setConfiguration(mcp.getConfiguration() | INTERRUPT_CLEAR_BIT);
    }

    startT = millis();
  }

  if (isrFlag) {
    Serial.println("*** Interrupt Alert ");
  }

}
