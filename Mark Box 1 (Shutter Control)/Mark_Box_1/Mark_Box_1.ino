//Set USB type to 'MIDI' before compile

const int led = 13;
const bool debug = true;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  pinMode(led, OUTPUT);
  digitalWriteFast(led, LOW);
  
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandleProgramChange(OnProgramChange);

  Serial1.begin(19200);
  inputString.reserve(200);
}

void loop() {
  usbMIDI.read();

  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString == "Error Code"){
      digitalWriteFast(led, HIGH);  
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void ShutterOpen(){
  Serial1.println("CF VMUTE OFF");
  //Response is either '000' or 'Error Code'
}


void ShutterClose(){
  Serial1.println("CF VMUTE ON");
  //Response is either '000' or 'Error Code'
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
  if(channel == 0 && note == 0){
    ShutterOpen();
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
  if(channel == 0 && note == 0){
    ShutterClose();
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
}
