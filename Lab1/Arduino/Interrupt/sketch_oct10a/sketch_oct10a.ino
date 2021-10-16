// Global state
int state;

void hard_reset() {
  state = 0;
}

void blink_1() {
  state = 1;
}

void blink_2() {
  state = 2;
}

void reset() {
  // Sets the LEDs status to 0
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
  hard_reset();
}

void name_length_blink() {
  // Toggles LED lights 
  for(int counter = 0; counter < strlen("Amirhossein"); counter++) {
    reset();
    delay(1000);
    set();
    delay(1000);
  }
  hard_reset();
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
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  // Interrupts 
  state = 0;
  attachInterrupt(digitalPinToInterrupt(18), hard_reset, HIGH);
  attachInterrupt(digitalPinToInterrupt(19), blink_1, HIGH);
  attachInterrupt(digitalPinToInterrupt(20), blink_2, HIGH);
}

void loop() {
  if (state == 0) {
    reset();
  } else if (state == 1) {
    ltr_blink();
  } else if (state == 2) {
    name_length_blink();
  }
}
