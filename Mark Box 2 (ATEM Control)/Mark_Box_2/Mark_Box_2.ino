//Set USB type to 'Serial + Keyboard + Mouse + Joystick' before compile
//MIDI RX = Pin 0
//MIDI TX = Pin 1

#include <MIDI.h>

const int led = 13;
const bool debug = false;

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
  if(channel == 1){     //V-800HD
    switch(control){
      case 12:    //PGM select
        break;
      case 13:    //PST/EFFECT select
        break;
      case 18:
        if(value < 7)
          Keyboard.print(value + 1);
        break;
      case 66:    //AUTO button
        break;
      case 67:    //DSK button
        //Keyboard.print(' ');
        Keyboard.println();
        break;
      case 68:    //CUT button
        break;
      case 98:    //Bar (16 bit)
        break;
    }
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
  //if(channel == 1){
    //if(program < 8)
      //Keyboard.print(program + 1);
  //}
}
