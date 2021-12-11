#include "pitches.h"
#include "iran.h"
#include "mario.h"
#include "poc.h"
#include "otj.h"
#include <Keypad.h>

// ############ Keypad setup
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


float scale = 0;
bool onset = false;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();

  int* melody;
  int* noteDurations;
  int length_of_array;
  
  if (key == '1') {
    melody = melody_IR;
    noteDurations = noteDurations_IR;
    length_of_array = sizeof(melody_IR) / sizeof(int);
    onset = true;
  } else if (key == '2') {
    melody = melody_MR;
    noteDurations = noteDurations_MR;
    length_of_array = sizeof(melody_MR) / sizeof(int);
    onset = true;
  } else if (key == '3') {
    melody = melody_PO;
    noteDurations = noteDurations_PO;
    length_of_array = sizeof(melody_PO) / sizeof(int);
    onset = true;
  } else if (key == '4') {
    melody = melody_OT;
    noteDurations = noteDurations_OT;
    length_of_array = sizeof(melody_OT) / sizeof(int);
    onset = true;
  }

  if (onset) {
    for (int thisNote = 0; thisNote < length_of_array; thisNote++) {
      scale = analogRead(A0) / 512.0;
      int noteDuration = 200 / noteDurations[thisNote];
      tone(9, (int)(melody[thisNote] * scale), noteDuration);
      delay((int)(noteDuration * 1.3));
    }

    onset = false;
  }
}
