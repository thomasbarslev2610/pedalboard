#include "settingshandler.h"
#include <ArduinoJson.h>
#include <Arduino.h>




void saveConfigurationJSON(JsonDocument configurationJSON, const char* configurationFile)
{
  
  char output[256];
  serializeJson(configurationJSON, output);
  setSetting(configurationFile, output);
}

JsonDocument getConfigurationJSON(const char* configurationFile)
{
    
    String configuration = getSetting(configurationFile);
    JsonDocument  doc;
     // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, configuration.c_str());

    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed in getConfigurationJSON(): "));
        Serial.println(error.f_str());
        return doc;
    }

    

    for (int i=0; i<5; i++)
    {
    
      String switchsetting = doc[String("switches")][i];
      Serial.println(switchsetting);
      
      String switchName = "switch";
      switchName.concat(i+1);
      switchName.concat("cc");
      Serial.println(switchName);
      String switchValueString = doc[String("switches")][i][switchName];
     //int switchValueInt = switchValueString.toInt();
      int switchValueInt = (doc["switches"][i][switchName]);

      //int value = setting["switch1"];
      Serial.println(switchValueInt);
      
      }
    Serial.println("Done, GetConfigurationJSON");
    return doc;       
}
