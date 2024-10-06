#include <Arduino.h>
#include "webserver.h"
#include "spiffshandler.h"
#include "settingshandler.h"
#include <ArduinoJson.h>
#include "midi.h"
#include "switches.h"
#include "configurationhandler.h"
#include "settings.h"
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


 
  char* CONFIGURATION_JSON_FILE = ""; 
  JsonDocument configuration;
  int SWITCH1CC_VALUE = 0;
  int SWITCH2CC_VALUE = 0;
  int SWITCH3CC_VALUE = 0;
  int SWITCH4CC_VALUE = 0;
  int SWITCH5CC_VALUE = 0;


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



// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}


void setup() {
  Serial.begin(115200);
  setupSpiffs();
  CONFIGURATION_JSON_FILE = "/configuration.json"; 
  configuration = getConfigurationJSON(CONFIGURATION_JSON_FILE); 
  SWITCH1CC_VALUE = configuration["switches"][0]["switch1cc"];
  SWITCH2CC_VALUE = configuration["switches"][1]["switch2cc"];
  SWITCH3CC_VALUE = configuration["switches"][2]["switch3cc"];
  SWITCH4CC_VALUE = configuration["switches"][3]["switch4cc"];
  SWITCH5CC_VALUE = configuration["switches"][4]["switch5cc"];  



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
  
  setupMidi();
  setupSwitches();
  Serial.println("Setup done");
  
}




void loop() {
  // put your main code here, to run repeatedly:
  readSwitches();

}



