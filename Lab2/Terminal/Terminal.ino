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
// ############

// ############ LED Function
uint8_t digitPins[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8};

void reset() {
  for(int i = 0; i < 9; i++) {
    digitalWrite(digitPins[i], LOW);
  }
}

void power(int number) {
  reset();
  for(int i = 0; i < number; i++) {
    digitalWrite(digitPins[i], HIGH);
  }
}
// ############

void setup(){
  Serial.begin(9600);
  for(int i = 0; i < 9; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}
  
void loop(){
  if (Serial.available() > 0) {
    int number = Serial.parseInt();
    if (number >= 0 && number < 10) {
      Serial.println(number);
      power(number);
    } else {
      reset();
      Serial.println("Invalid number");
    }
  }
}
