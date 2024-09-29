#include <Arduino.h>

const char* const CONFIGURATION_JSON_FILE = "/configuration.json"; 
const char* const CONFIGURATION_TEST_FILE = "/test.txt"; 

void initializeSettings();
String getSetting (const char* settingName);
void setSetting (const char* settingName, const char* settingValue);

