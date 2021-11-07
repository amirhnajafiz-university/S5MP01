#include <Arduino.h>
#include <Servo.h>

const int DELAY = 300;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(9, 1000, 2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (true) {
    servo.write(90);
    delay(4*DELAY);
    servo.write(180);
    delay(4*DELAY);
  } 
}
