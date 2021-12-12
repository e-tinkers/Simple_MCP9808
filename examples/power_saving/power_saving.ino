#include <MCP9808.h>

Simple_MCP9808 mcp;

void setup() {
  Serial.begin(115200);
  Serial.println();
}

void loop() {

  if (mcp.begin()) {
    Serial.print("Temperature in Celsius = ");
    Serial.println(mcp.getTemperature()/16.0);

    Serial.println("Put MCP9808 in power-saving mode");
    mcp.shundown();
  }
  else {
    Serial.println("Unable to communicate with MCP9808 sensor");
  }

  // loop forever or replace this with MCU deep sleep code
  while(true) { delay(10); }

}
