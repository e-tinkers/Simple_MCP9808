#include <MCP9808.h>

Simple_MCP9808 mcp;

void setup() {
  Serial.begin(115200);
  Serial.println();
}

void loop() {

  if (mcp.begin()) {
    int16_t tempR = mcp.getTemperature();
    mcp.shundown();  //put MCP9808 in power-saving mode
    Serial.print("Temperature in Celsius = ");
    Serial.println(tempR/16.0);
  }
  else {
    Serial.println("Unable to communicate with MCP9808 sensor");
  }

  delay(5000);

}
