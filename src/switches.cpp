#include "switches.h"
#include <Arduino.h>
#include "midi.h"
#include "hardwarepins.h"
#include "settings.h"


uint8_t switch1State;
uint8_t switch2State;
uint8_t switch3State;
uint8_t switch4State;
uint8_t switch5State;

uint8_t lastSwitch1State;
uint8_t lastSwitch2State;
uint8_t lastSwitch3State;
uint8_t lastSwitch4State;
uint8_t lastSwitch5State;

long lastSwitch1Time;
long lastSwitch2Time;
long lastSwitch3Time;
long lastSwitch4Time;
long lastSwitch5Time;

int debounceTime = 50;


int switchPins [] = {SWITCH1_PIN, SWITCH2_PIN, SWITCH3_PIN, SWITCH4_PIN, SWITCH5_PIN};
int switchStates [] = {switch1State, switch2State, switch3State, switch4State, switch5State};
int lastSwitchStates [] = {lastSwitch1State, lastSwitch2State, lastSwitch3State, lastSwitch4State, lastSwitch5State};
long lastSwitchTimes [] = {lastSwitch1Time, lastSwitch2Time, lastSwitch3Time, lastSwitch4Time, lastSwitch5Time};
int switchValues [5]; 

void setupSwitches()
{

    pinMode(SWITCH1_PIN, INPUT_PULLUP);
    pinMode(SWITCH2_PIN, INPUT_PULLUP);
    pinMode(SWITCH3_PIN, INPUT_PULLUP);
    pinMode(SWITCH4_PIN, INPUT_PULLUP);
    pinMode(SWITCH5_PIN, INPUT_PULLUP);
    
    switch1State = 0;
    switch2State = 0;
    switch3State = 0;
    switch4State = 0;
    switch5State = 0;

   
    
    lastSwitch1State = 0;
    lastSwitch2State = 0;
    lastSwitch3State = 0;
    lastSwitch4State = 0;
    lastSwitch5State = 0;

    lastSwitch1Time = 0;
    lastSwitch2Time = 0;
    lastSwitch3Time = 0;
    lastSwitch4Time = 0;
    lastSwitch5Time = 0;

    switchValues[0] = SWITCH1CC_VALUE;
    switchValues[1] = SWITCH2CC_VALUE;
    switchValues[2] = SWITCH3CC_VALUE;
    switchValues[3] = SWITCH4CC_VALUE;
    switchValues[4] = SWITCH5CC_VALUE;

    

    //int switchPins [] = {SWITCH1_PIN, SWITCH2_PIN, SWITCH3_PIN, SWITCH4_PIN, SWITCH5_PIN};
    //int switchStates [] = {switch1State, switch2State, switch3State, switch4State, switch5State};
    //int lastSwitchStates [] = {lastSwitch1State, lastSwitch2State, lastSwitch3State, lastSwitch4State, lastSwitch5State};

}   

void readSwitches()
{
    for(int i = 0; i < 5; i++)
    {
        long readTime = millis();
        switchStates[i] = digitalRead(switchPins[i]);
        if (switchStates[i] != lastSwitchStates[i])
        {
            if( readTime  > (lastSwitchTimes[i] + debounceTime) )
            {
                //sustainMessage(switchStates[i]);
                Serial.print("Switch: " );
                Serial.print(i);
                Serial.print(" SwitchState: ");
                Serial.print(switchStates[i]);
                Serial.println();
                lastSwitchStates[i] = switchStates[i];
                lastSwitchTimes[i] = readTime;

                Serial.print("Switch cc: ");
                Serial.println(switchValues[i]);
               
            }  
        }
        //delay(1000);
    }

  
    
}