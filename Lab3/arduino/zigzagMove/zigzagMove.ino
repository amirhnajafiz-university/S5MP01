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
 
void setup() 
{ 
  // put your setup code here, to run once: 
  lcd.begin(COLS, ROWS);
  lcd.clear(); 
} 
 
void loop() 
{ 
    zigzagPrint('z');
} 

void zigzagPrint(char c) { 
    int turn = 0;
    while (true)
    {
        lcd.clear(); 
        lcd.setCursor(turn % COLS, turn % ROWS); 
        lcd.print(c); 
        turn ++;
        delay(500);
    }
} 
