#include <Arduino.h>
#include <Servo.h>
#include <Keypad.h>

const int DELAY = 300;

const byte rows = 4; 
const byte cols = 4;
char keys[rows][cols] = { 
    {'7', '8', '9', '/'}, 
    {'4', '5', '6', '*'}, 
    {'1', '2', '3', '-'}, 
    {'#', '0', '=', '+'}}; 
byte rowPins[rows] = {31, 33, 35, 37};
byte colPins[cols] = {23, 25, 27, 29};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(9, 1000, 2000);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.write(0);
  
  String input = "";
  
  while (true) {
    char in = keypad.getKey();
    if (in == NO_KEY)
      continue;
    if (in == '#') {
      Serial.println("Entered number");
      int degree = input.toInt();
      servo.write(degree/2);
      input = "";
      continue;
    }
    input += in;
    Serial.println(input);
    if (input.toInt() > 360) {
      input = "";
    }
  }
}
