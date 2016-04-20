//Set USB type to 'Serial + Keyboard + Mouse + Joystick' before compile
//MIDI RX = Pin 0
//MIDI TX = Pin 1

#include <MIDI.h>

const int led = 13;
const bool debug = true;

void setup() {
  pinMode(led, OUTPUT);
  digitalWriteFast(led, LOW);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);  
  MIDI.setHandleNoteOff(OnNoteOff);
  MIDI.setHandleNoteOn(OnNoteOn);
  MIDI.setHandleControlChange(OnControlChange);
  MIDI.setHandleProgramChange(OnProgramChange);
}

void loop() {
  MIDI.read();
}

void OnNoteOn(byte channel, byte note, byte velocity) {
  if(debug){
    Serial.print("Note On, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(note, DEC);
    Serial.print(", velocity=");
    Serial.print(velocity, DEC);
    Serial.println();
  }
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  if(debug){
    Serial.print("Note Off, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(note, DEC);
    Serial.print(", velocity=");
    Serial.print(velocity, DEC);
    Serial.println();
  }
}

void OnControlChange(byte channel, byte control, byte value) {
  if(debug){
    Serial.print("Control Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", control=");
    Serial.print(control, DEC);
    Serial.print(", value=");
    Serial.print(value, DEC);
    Serial.println();
  }
}

void OnProgramChange(byte channel, byte program) {
  if(debug){
    Serial.print("Program Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", program=");
    Serial.print(program, DEC);
    Serial.println();
  }
  if(channel == 1){
    Keyboard.print(program + 1);
    Keyboard.print(' ');
  }
}
