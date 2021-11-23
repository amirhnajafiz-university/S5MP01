#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

int curr_row = 0;
int curr_col = 0;

#define E 33
#define RS 32
#define D4 34
#define D5 35
#define D6 36
#define D7 37
#define ROWS 2
#define COLS 16

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'c', '0', '=', '+'}
};
byte rowPins[rows] = {39, 40, 41, 42}; //connect to the row pinouts of the keypad
byte colPins[cols] = {43, 44, 45, 46}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(COLS, ROWS);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  int input = 0;

  while (true)
  {
    char key = keypad.getKey();
    if (key == '=') {
      // Start compute by the other aurdoino
      begin_cooperation(input);
      delay(1000);
      break;
    } else {
      if ( key - '0' >= 0 && key - '0' < 10 ) {
        input = input * 10 + (key - '0');
        lcd.clear();
        lcd.print(input);
      }
    }
  }
}

void begin_cooperation(int input) {
  lcd.setCursor(0, 1);

  Serial.print(input);

  while (true)
  {
    if (Serial.available() > 0) {
      int number = Serial.parseInt();
  
      if (number == 1) {
        lcd.print("ODD");
        Serial.print("DONE");
        break;
      } else if (number == 0) {
        lcd.print("EVEN");
        Serial.print("DONE");
        break;
      } else {
        number = number > 0 ? number - 2 : number + 2;
        Serial.print(number);
      }
    }
  }
}
