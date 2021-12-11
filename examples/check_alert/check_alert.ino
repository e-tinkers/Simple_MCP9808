#include <Simple_MCP9808.h>

// To test the alert triggering, change the following parameters to suit your
// temperature environment so that an alert can be obversed
#define LOWER_LIMIT_TEMPERATURE -20
#define UPPER_LIMIT_TEMPERATURE 100
#define CRITICAL_TEMPERATURE 100

Simple_MCP9808 mcp;

void setup() {
  Serial.begin(115200);
  Serial.println();

  if (!mcp.begin()) {
    Serial.println("Failed to communicate with MCP9808 sensor");
    while (1) { delay(10); }
  }
  else {
    // Setup temperature threshholds
    mcp.setLowerTemperature(LOWER_LIMIT_TEMPERATURE);
    mcp.setUpperTemperature(UPPER_LIMIT_TEMPERATURE);
    mcp.setCriticalTemperature(CRITICAL_TEMPERATURE);
  }
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

  int16_t alertStatus = mcp.alertTriggered();

  if (alertStatus & LOWER_TEMP_ALERT)
    Serial.println("*** Temperature < Preset Lower Limit");
  if (alertStatus & UPPER_TEMP_ALERT)
    Serial.println("*** Temperature > Preset Upper Limited");
  if (alertStatus & CRITICAL_TEMP_ALERT)
    Serial.println("*** Temperature > Preset Critial Temperature");

  delay(5000);
}
