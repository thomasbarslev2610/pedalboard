#include "settingshandler.h"
#include <Arduino.h>
#include "spiffshandler.h"



void initializeSettings()
{
    //initialize files if not present/corrupt
}

void setSetting (const char*  settingName, const char* settingValue)
{
    Serial.print("Setting setting for: ");
    Serial.println(settingName);
    Serial.print("Value: ");
    Serial.println(settingValue);
    writeFile(SPIFFS, settingName, settingValue );
}

String getSetting (const char* settingName)
{
    Serial.print("Getting setting for: ");
    Serial.println(settingName);
    String setting = returnFileString(SPIFFS, settingName);
    Serial.println(setting);
    return setting;
}
