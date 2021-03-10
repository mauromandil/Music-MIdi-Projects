#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int buttonN = 3;
int sensorPin = A0;
int sensorValue = 0;
int outputValue = 0;
int buttonPin[buttonN] = {2, 3, 4};
int buttonCState[buttonN] = {0};
int buttonPState[buttonN] = {0};
const int chordSize = 5; //if you decide to change the numer of notes on your chord
int prog[3] = { -7, 0 , 7}; //set the intervals of your progression. This -7 0 7 works for the 1-4-5 prog
int chord[chordSize] = {0, 4 , 7, 12, 24}; // set the notes on your chord. 0,4,7 is a perfect major, 12 is the octave and 24 a higher octave

void setup() {
  MIDI.begin();
  Serial.begin(115200);



  for (int i = 0; i < buttonN; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

}

void loop() {
  sensorValue = analogRead(sensorPin);
  outputValue = map(sensorValue, 0, 1023, 60 , 71); // range -> starting at 60, 1 is a half tone

  for (int i = 0; i < buttonN; i++) {
    buttonCState[i] = digitalRead(buttonPin[i]);
  }

  for (int i = 0; i < buttonN; i++) {

    if (buttonPState[i] != buttonCState[i]) {

      if (buttonCState[i] == LOW) {
        for (int z = 0; z < chordSize; z++) {
          MIDI.sendNoteOn(outputValue + prog[i] + chord[z], 127, 1);


        }
        //        Serial.print("button on >> ");
        //        Serial.println(i);
        buttonPState[i] = buttonCState[i];


      }
      else {

        for (int z = 0; z < chordSize; z++) {
          MIDI.sendNoteOn(outputValue + prog[i] + chord[z], 0, 1);

        }


      }

      //        Serial.print("button off >> ");
      //        Serial.println(i);
      buttonPState[i] = buttonCState[i];
    }

  }
}
