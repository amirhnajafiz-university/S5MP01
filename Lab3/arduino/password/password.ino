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
    {'c', '0', '=', '+'}}; 
 byte rowPins[rows] = {39, 40, 41, 42}; //connect to the row pinouts of the keypad 
byte colPins[cols] = {43, 44, 45, 46}; //connect to the column pinouts of the keypad 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);  
 
void setup() 
{ 
  // put your setup code here, to run once: 
  lcd.begin(COLS, ROWS);
  lcd.clear(); 
} 
 
void loop() 
{ 
    checkPassword("9831065");
} 

void checkPassword(String pass) {
    lcd.clear();
    String input = "";
    while (true) {
        char key = keypad.getKey();
        if (key){
           if (key == 'c'){
              lcd.setCursor(0, 1);
              if (pass.equals(input))
                  lcd.print("correct password");
              else
                  lcd.print(" wrong password ");
              break;
           }
           input += key;
           lcd.print(key);
        }
    }
    delay(2000);
}
