//Set USB type to 'MIDI' before compile

const int led = 13;
const bool debug = false;

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
  delay(5000);
  if(debug){
    Serial.println("Ready");
  }
}

void loop() {
  usbMIDI.read();

  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    if(debug){
      Serial.print(inChar);
    }
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag
//    // so the main loop can do something about it:
//    if (inChar == '\n') {
//      stringComplete = true;
//    }
  }
  
//  if (stringComplete) {
//    if(debug){
//      Serial.println(inputString);
//    }
//    if(inputString == "Error Code"){
//      digitalWriteFast(led, HIGH);  
//    }
//    // clear the string:
//    inputString = "";
//    stringComplete = false;
//  }
}

void ShutterOpen(){
  if(debug){
    Serial.println("Opening shutter");
  }
  Serial1.print("CF VMUTE OFF"); Serial1.write('\r');     //Other option is 0x0A
  //Response is either '000' or 'Error Code'
}


void ShutterClose(){
  if(debug){
    Serial.println("Closing shutter");
  }
  Serial1.print("CF VMUTE ON"); Serial1.write('\r');      //Other option is 0x0A
  //Response is either '000' or 'Error Code'
}

void OnNoteOn(byte channel, byte note, byte velocity) {
  if(debug){
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    Serial.print("Note On, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(note, DEC);
    Serial.print(", velocity=");
    Serial.print(velocity, DEC);
    Serial.println();
  }
  //if(channel == 1 && note == 49){
    ShutterOpen();
  //}
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  if(debug){
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    delay(50);
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    Serial.print("Note Off, ch=");
    Serial.print(channel, DEC);
    Serial.print(", note=");
    Serial.print(note, DEC);
    Serial.print(", velocity=");
    Serial.print(velocity, DEC);
    Serial.println();
  }
  //if(channel == 1 && note == 49){
    ShutterClose();
  //}
}

void OnControlChange(byte channel, byte control, byte value) {
  if(debug){
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    delay(50);
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    delay(50);
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
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
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    delay(50);
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    delay(50);
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    delay(50);
    digitalWriteFast(led, HIGH);
    delay(50);
    digitalWriteFast(led, LOW);
    Serial.print("Program Change, ch=");
    Serial.print(channel, DEC);
    Serial.print(", program=");
    Serial.print(program, DEC);
    Serial.println();
  }
}
