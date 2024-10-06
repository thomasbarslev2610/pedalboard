#include <Arduino.h>
#include <ArduinoJson.h>
JsonDocument getConfigurationJSON(const char* configurationFile);
void saveConfigurationJSON(JsonDocument configurationJSON, const char* configurationFile);