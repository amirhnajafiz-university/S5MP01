#include <Arduino.h>
#include <Servo.h>

Servo servo;
int curr_degree = 0;

void setup() {
  // put your setup code here, to run once:
  servo.attach(9, 1000, 2000);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0);

  String enteredText = Serial.readString();

  int number = enteredText.toInt();

  curr_degree =  curr_degree - number;
  if (curr_degree >= -180 && curr_degree <= 180)
  {
    int degreee = map(curr_degree, -180, 180, 0, 180);
    servo.write(degreee);
    Serial.print("Set to ");
    Serial.println(curr_degree * -1);
  }
  else
  {
    curr_degree = 0;
    servo.write(0);
    Serial.println("New degree is not between (-180 to 180)");
  }
}
