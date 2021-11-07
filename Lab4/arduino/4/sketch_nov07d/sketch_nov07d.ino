#include <Arduino.h>
#include <Servo.h>

Servo servo;

void setup()
{
  // put your setup code here, to run once:
  servo.attach(9, 1000, 2000);
  Serial.begin(9600);
}

void loop()
{
  int potVal = analogRead(A0);
  potVal = map(potVal, 0, 1023, 0, 180);
  
  Serial.println("Wrote to servo ");
  Serial.println(potVal);

  servo.write(potVal);
  delay(1000);
}
