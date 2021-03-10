#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int buttonN = 3;
int sensorPin = A0;
int sensorValue = 0;
int outputValue = 0;
int buttonPin[buttonN] = {2, 3, 4};
int buttonCState[buttonN] = {0};
int buttonPState[buttonN] = {0};

int prog[3] = { -7, 0 , 7};
int chord[5] = {0, 4 , 7, 12, 24};

void setup() {
  MIDI.begin();
  Serial.begin(115200);



  for (int i = 0; i < buttonN; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

}

void loop() {
  sensorValue = analogRead(sensorPin);
  outputValue = map(sensorValue, 0, 1023, 60 , 71);

  for (int i = 0; i < buttonN; i++) {
    buttonCState[i] = digitalRead(buttonPin[i]);
  }

  for (int i = 0; i < buttonN; i++) {

    if (buttonPState[i] != buttonCState[i]) {

      if (buttonCState[i] == LOW) {
        for (int z = 0; z < 5; z++) {
          MIDI.sendNoteOn(outputValue + prog[i] + chord[z], 127, 1);


        }
        //        Serial.print("button on >> ");
        //        Serial.println(i);
        buttonPState[i] = buttonCState[i];


      }
      else {

        for (int z = 0; z < 5; z++) {
          MIDI.sendNoteOn(outputValue + prog[i] + chord[z], 0, 1);

        }


      }

      //        Serial.print("button off >> ");
      //        Serial.println(i);
      buttonPState[i] = buttonCState[i];
    }

  }
}
