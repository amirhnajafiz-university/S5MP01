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
    calculate(); 
} 

void calculate() {
  lcd.clear();
  String input = "";
  String numbers[2];
  char operand ;
  int numbersIndex = 0;
  
  while (true)
  {
    char key = keypad.getKey();
    if (key){
      if (key == '='){
        lcd.setCursor(0, 1);
        break;
      }
      if ( key -'0'>=0 && key -'0'<10 ){
        numbers[numbersIndex] += key;
      }
      else {
        operand = key;
        numbersIndex = 1;
      }
      lcd.print(key);
    }
  }
  lcd.print(calc(numbers[0].toInt(),numbers[1].toInt(),operand));
  delay(1500);
}

double calc( double a, double b, char operand) 
{ 
  switch (operand){
      case '+':
          return a + b;
      case '*':
          return a * b;
      case '/':
          return a / b;
      case '-':
          return a - b;
  }
  
} 
 
