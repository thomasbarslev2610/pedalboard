#include <Arduino.h>
void setupMidi();
void sendNote(int cmd, int pitch, int velocity);
void sendAllNotesOff();
void sendMIDICommand(uint8_t messageType, uint8_t data1, uint8_t data2) ;
void sustainMessage(int state);
void damperMessage(int state);
void programChange (int val);
void modMessage (int val);

const u_int32_t MIDI_CHANNEL = 1;

