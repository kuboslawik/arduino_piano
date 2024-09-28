# Arduino piano keyboard

Revive your broken piano keyboard using Arduino Micro. Connect it to computer by USB and use keyboard for online or dekstop music software.

## Requirements

Arduino with USB HID capabilites such as Micro or Leonardo.

## Wiring

Pins from keyboard are directly connected to Arduino, no resistors required. Code is multiplexing inputs by reading keys sequnetially. Depending on model (mine was Casio CA-110) you might need to change readButtons() function to reflect your keyborad wiring. In this case it consists of 6x8 array of keys plus one extra at the end.

## Notes

Leftmost key starts with C3 note which coresponds with number 49 in MIDI notation. If you want to change starting note edit startingNote varaible.

## Used libraries

MIDIUSB.h is used to emulate USB MIDI device.
