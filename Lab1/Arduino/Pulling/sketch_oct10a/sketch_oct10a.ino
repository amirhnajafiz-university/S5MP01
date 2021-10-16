void reset() {
  // Resets the LEDs status to 0
  for(int counter = 0; counter < 6; counter++) {
    digitalWrite(counter, LOW);
  }
}

void set() {
  // Sets the LEDs status to 1
  for(int counter = 0; counter < 6; counter++) {
    digitalWrite(counter, HIGH);
  }
}

void ltr_blink() {
  // Turns on the LED lights from left to write
  for(int counter = 0; counter < 6; counter++) {
    reset();
    digitalWrite(counter, HIGH);
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
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  // 3 Switch input
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
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
