# 1 "F:\\Desktop\\UniClasses\\Sem5\\Microprocessor\\Lab\\Lab1\\Arduino\\Pulling\\sketch_oct10a\\sketch_oct10a.ino"
void reset() {
  // Resets the LEDs status to 0
  for(int counter = 0; counter < 6; counter++) {
    digitalWrite(counter, 0x0);
  }
}

void set() {
  // Sets the LEDs status to 1
  for(int counter = 0; counter < 6; counter++) {
    digitalWrite(counter, 0x1);
  }
}

void ltr_blink() {
  // Turns on the LED lights from left to write
  for(int counter = 0; counter < 6; counter++) {
    reset();
    digitalWrite(counter, 0x1);
    delay(1000);
  }
  reset();
}

void name_length_blick() {
  // Toggles LED lights 
  for(int counter = 0; counter < strlen("Amirhossein"); counter++) {
    reset();
    delay(1000);
    set();
    delay(1000);
  }
}

void setup() {
  // put your setup code here, to run once:
  // 6 LED output
  pinMode(0, 0x1);
  pinMode(1, 0x1);
  pinMode(2, 0x1);
  pinMode(3, 0x1);
  pinMode(4, 0x1);
  pinMode(5, 0x1);
  // 3 Switch input
  pinMode(10, 0x0);
  pinMode(11, 0x0);
  pinMode(12, 0x0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(10) == 1) {
    reset();
  } else if (digitalRead(11) == 1) {
    ltr_blink();
  } else if (digitalRead(12) == 1) {
    name_length_blick();
  }
}
