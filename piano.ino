#include "MIDIUSB.h"

const int inputPins[] = {A3, A2, A1, A0, 15, 8, 9, 16, 10};
const int outputPins[] = {2, 3, 4, 5, 6, 7};
int previousState[49];
int currentState[49];
int startingNote = 49;

void setup() {

  // Serial.begin(9600);

  for(int a = 0; a < 9; a++){
    pinMode(inputPins[a], INPUT_PULLUP); 
  };

  for(int a = 0; a < 6; a++){
    pinMode(outputPins[a], OUTPUT); 
  };

  for(int a = 0; a < 49; a++){
    previousState[a] = 1;
  };

  for(int a = 0; a < 49; a++){
    currentState[a] = 1;
  };
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void readButtons() {

  for(int a = 0; a < 49; a++){
    previousState[a] = currentState[a];
  };

  int counter = 0;

  for (int a = 0; a < 9; a++){
    if (a<8){
      for (int b = 0; b < 6; b++){
        digitalWrite(outputPins[b], LOW);
        if (digitalRead(inputPins[a]) == 0){
          currentState[counter] = 0;
        } else {
          currentState[counter] = 1;
        };
        digitalWrite(outputPins[b], HIGH);
        counter++;
      };
    } else {
      digitalWrite(outputPins[0], LOW);
      if (digitalRead(inputPins[a]) == 0){
          currentState[counter] = 0;
        } else {
          currentState[counter] = 1;
        };
      digitalWrite(outputPins[0], HIGH);
      counter++;
    };
  };
}

void playNotes() {
  for (int a = 0; a < 49; a++) {
    if (previousState[a] != currentState[a]) {
      if (currentState[a] == 0) {
        noteOn(0, a+startingNote, 64);
      } else {
        noteOff(0, a+startingNote, 64);
      };
    };
  };
  MidiUSB.flush();
}

void loop() {

  readButtons();
  playNotes();
  delay(50);

}