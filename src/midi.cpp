#include <Arduino.h>
#include "midi.h"

void setupMidi()
{
  Serial2.begin(31250); // TX default pin 17
}

void sendNote(int cmd, int midinoteNumber, int velocity)
{

  /* Serial.print("Command: ");
  Serial.print(cmd);
  Serial.print(" MidiNote:");
  Serial.print(midinoteNumber);
  Serial.print(" Velocity: ");
  Serial.print(velocity);
  Serial.println(""); */
  sendMIDICommand(cmd, midinoteNumber, velocity);
}

void sustainMessage(int state)
{

  if (state == 0)
  {
    sendMIDICommand(0xB0, 0x40, 127);
  }
  else
  {
    sendMIDICommand(0xB0, 0x40, 0);
  }
}

void damperMessage(int state)
{

  if (state == 0)
  {
    sendMIDICommand(0xB0, 0x43, 127);
  }
  else
  {
    sendMIDICommand(0xB0, 0x43, 0);
  }
}

void programChange(int val)
{
  sendMIDICommand(192, val, 0);
}




void modMessage(int val)
{
  sendMIDICommand(0xB0, 0x01, val);
}

void pitchWheelChange(int value)
{
  unsigned int change = 0x2000 + value;      //  0x2000 == No Change
  unsigned char low = change & 0x7F;         // Low 7 bits
  unsigned char high = (change >> 7) & 0x7F; // High 7 bits

  sendMIDICommand(0xE0, low, high);
}

void sendAllNotesOff()
{
  sendMIDICommand(123,0,0);
}

void sendMIDICommand(uint8_t messageType, uint8_t data1, uint8_t data2)
{
  uint8_t channel = MIDI_CHANNEL;
  channel--;                                  // Decrement the channel, because MIDI channel corresponds to binary channel 0
  messageType &= 0b11110000;                  // Make sure that only the high nibble of the message type is set
  channel &= 0b00001111;                      // Make sure that only the low nibble of the channel is set
  uint8_t statusByte = messageType | channel; // Combine the messageType (high nibble) with the channel (low nibble)

  // Both the message type and the channel should be 4 bits wide
  statusByte |= 0b10000000; // Set the most significant bit of the status byte
  data1 &= 0b01111111;      // Clear the most significant bit of the data bytes
  data2 &= 0b01111111;




  switch (statusByte)
  {
  
  case (128):
    break;
  
  case (144):
    break;
  default:
   
    /* Serial.print(statusByte);
    Serial.print(" ");
    Serial.print(data1);
    Serial.print(" ");
    Serial.println(data2); */
   break;
  }
  
  /*
  Serial1.write(statusByte);
  Serial1.write(data1);
  Serial1.write(data2);
  */

  Serial2.write(statusByte);
  Serial2.write(data1);
  Serial2.write(data2);
}
