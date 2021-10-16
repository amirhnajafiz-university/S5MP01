# 1 "F:\\Desktop\\UniClasses\\Sem5\\Microprocessor\\Lab\\Lab1\\Arduino\\Interrupt\\sketch_oct10a\\sketch_oct10a.ino"
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
  pinMode(0, 0x1);
  pinMode(1, 0x1);
  pinMode(2, 0x1);
  pinMode(3, 0x1);
  pinMode(4, 0x1);
  pinMode(5, 0x1);
  // 3 Switch input
  pinMode(18, 0x0);
  pinMode(19, 0x0);
  pinMode(20, 0x0);
  // Interrupts 
  state = 0;
  attachInterrupt(((18) == 2 ? 0 : ((18) == 3 ? 1 : ((18) >= 18 && (18) <= 21 ? 23 - (18) : -1))), hard_reset, 0x1);
  attachInterrupt(((19) == 2 ? 0 : ((19) == 3 ? 1 : ((19) >= 18 && (19) <= 21 ? 23 - (19) : -1))), blink_1, 0x1);
  attachInterrupt(((20) == 2 ? 0 : ((20) == 3 ? 1 : ((20) >= 18 && (20) <= 21 ? 23 - (20) : -1))), blink_2, 0x1);
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
