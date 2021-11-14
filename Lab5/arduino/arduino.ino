#include <string.h>

void setup() {
  pinMode(22,OUTPUT);
  pinMode(21,INPUT);
}

void loop() {
  digitalWrite(22,digitalRead(21));
}
