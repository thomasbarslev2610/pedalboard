#include <Arduino.h>
#include <MIDI.h>
#include "webserver.h"
#include "spiffshandler.h"
#include "settingshandler.h"
#include <ArduinoJson.h>

/*
Bank Down   CC22
Bank Up     CC23
Patch Down  CC24
Patch Up    CC25

Tap Tempo   CC75
Expression

Rotary
- Menu
- Item select
- Preset
  - Save
  - Load
Display




*/


//MIDI_CREATE_DEFAULT_INSTANCE();

TaskHandle_t Task0;
void Task0code( void * parameter) {
  Serial.println("Task 0");
  
  setupwebServer();
  
  while (true) {
    //delay(500);
    //Code for task 1 - infinite loop
    //Serial.print("Task1 running on core ");
    //Serial.println(xPortGetCoreID());
    //scanKeyboard();

    
  }
}



void getConfigurationJSON()
{
    
    String configuration = getSetting(CONFIGURATION_JSON_FILE);
    DynamicJsonDocument  doc(256);
     // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, configuration.c_str());

    // Test if parsing succeeds.
    if (error) {
        Serial.print(F("deserializeJson() failed in getConfigurationJSON(): "));
        Serial.println(error.f_str());
        return;
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
      int switchValueInt = switchValueString.toInt();
      //int value = setting["switch1"];
      Serial.println(switchValueInt);
      
      }
    Serial.println("Done, GetConfigurationJSON");
       
}
// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

void setup() {
  
  Serial.begin(115200);
  setupSpiffs();
  getConfigurationJSON();
    xTaskCreatePinnedToCore(
      Task0code, /* Function to implement the task */
      "Task0", /* Name of the task */
      20000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task0,  /* Task handle. */
      0); /* Core where the task should run */

  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  //MIDI.begin();
  //MIDI.sendControlChange(21,127,1);
  
 
  Serial.println("Setup done");
  
}




void loop() {
  // put your main code here, to run repeatedly:
}



