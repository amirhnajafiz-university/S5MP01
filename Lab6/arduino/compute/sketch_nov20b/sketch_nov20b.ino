#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(COLS, ROWS);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  begin_cooperation();
}

void begin_cooperation() {
  while(true) {
    if (Serial.available() > 0) {
      String input = Serial.readString();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(input);
      
      if (input == "DONE") {
        break;
      }
  
      int number = input.toInt();
      if (number == 1) {
        Serial.print(1);
      } else if (number == 0) {
        Serial.print(0);
      } else {
        number = number > 0 ? number - 2 : number + 2;
        Serial.print(number);
      }

      lcd.setCursor(0, 1);
      lcd.print(number);
    }
  }
}
