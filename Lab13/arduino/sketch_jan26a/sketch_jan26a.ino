#include <Keypad.h>
#include <LiquidCrystal.h>

// =============== Tools setup ===============
// LED
int RED = 5;
int GREEN = 4;
int BLUE = 3;

// LCD
int curr_row = 0;
int curr_col = 0;

#define E 33
#define RS 32
#define D4 34
#define D5 35
#define D6 36
#define D7 37
#define CROWS 4
#define CCOLS 16

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

// Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', 'x'},
  {'1', '2', '3', '-'},
  {'*', '0', '#', '+'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
// =============== End Tools setup ===============
// =============== Variables setup ===============
bool printed = false;
bool finish = false;
int turn = 0;

char board[3][3] = {
  {'-', '-', '-'},
  {'-', '-', '-'},
  {'-', '-', '-'},
};

void putIn(char target, int i, int j) {
  board[i][j] = target;
}

bool check(int i, int j) {
  return board[i][j] == '-';
}

bool lock() {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (check(i, j))
        return false;
  return true;
}

bool whowon(char target) {
  bool cond = (board[0][0] == board[0][1]) && (board[0][1] == board[0][2]) && (board[0][0] == target);
  cond = cond || ( (board[1][0] == board[1][1]) && (board[1][1] == board[1][2]) && (board[1][0] == target) );
  cond = cond || ( (board[2][0] == board[2][1]) && (board[2][1] == board[2][2]) && (board[2][0] == target) );
  cond = cond || ( (board[0][0] == board[1][0]) && (board[1][0] == board[2][0]) && (board[0][0] == target) );
  cond = cond || ( (board[0][1] == board[1][1]) && (board[1][1] == board[2][1]) && (board[0][1] == target) );
  cond = cond || ( (board[0][2] == board[1][2]) && (board[1][2] == board[2][2]) && (board[0][2] == target) );
  cond = cond || ( (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] == target) );
  cond = cond || ( (board[2][1] == board[1][1]) && (board[1][1] == board[0][2]) && (board[2][1] == target) );
  return cond;
}

int play(char target, char input) {
  int index = input - '0';
  int i, j;

  if (index == 7) {
    i = 0;
    j = 0;
  } else if (index == 8) {
    i = 0;
    j = 1;
  } else if (index == 9) {
    i = 0;
    j = 2;
  } else if (index == 4) {
    i = 1;
    j = 0;
  } else if (index == 5) {
    i = 1;
    j = 1;
  } else if (index == 6) {
    i = 1;
    j = 2;
  } else if (index == 1) {
    i = 2;
    j = 0;
  } else if (index == 2) {
    i = 2;
    j = 1;
  } else if (index == 3) {
    i = 2;
    j = 2;
  } else {
    return -1; // Not valid house
  }

  if (!check(i, j)) {
    return -2; // Not empty house
  }

  putIn(target, i, j);
  return 0;
}
// =============== End Vars setup  ===============
// =============== I/O      setup  ===============
void printBoard() {
  lcd.clear();
  curr_row = 0;
  curr_col = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      lcd.setCursor(j, i);
      lcd.print(board[i][j]);
      if (i == 0 && j == 2 && !finish) {
        if (turn % 2 == 0) {
          lcd.print(" |Turn: O");
        } else {
          lcd.print(" |Turn: X");
        }
      }
      if (i == 1 && j == 2) {
        lcd.print(" |You are O");
      }
      if (i == 2 && j == 2) {
        lcd.print(" |");
      }
    }
  }
  lcd.setCursor(0, 3);
  if (finish) {
    lcd.print("Game over!");
  }
}

void on(int code) {
  digitalWrite(code, HIGH);
}

void off(int code) {
  digitalWrite(code, LOW);
}

void printMessage(String message) {
  lcd.setCursor(2,4);
  for (int i = 4; i < COLS; i++)
    lcd.print(" ");
  lcd.setCursor(2,4);
  lcd.print(message);
}
// =============== End I/O  setup  ===============


void setup()
{
  // put your setup code here, to run once:
  // LCD
  lcd.begin(CCOLS, CROWS);
  lcd.clear();
  // LED
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  // XBee
  Serial.begin(9600);
}

void loop()
{
  if (!finish) {
    if (turn % 2 == 0) {
      on(BLUE);
      char key = keypad.getKey();
      if (key)
      {
        int temp = play('O', key);
        if (temp == 0) {
          Serial.write(key);
          turn++;
          printed = false;
          off(BLUE);
          on(GREEN);
          delay(500);
          off(GREEN);
        } else if (temp == -1) {
          printMessage("Not valid");
          on(RED);
          delay(200);
          off(RED);
        } else if (temp == -2) {
          printMessage("Not empty");
          on(RED);
          delay(200);
          off(RED);
        }
      }
    } else {
      if (Serial.available() > 0) {
        int received = Serial.read();
        play('X', received);
        turn++;
        printed = false;
      }
    }
    
    finish = (whowon('X') || whowon('O')) || lock();
    if (!printed) {
      printBoard();
      printed = true;
    }
  }
}
