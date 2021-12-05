#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const byte rows = 4; // four rows
const byte cols = 4; // three columns
char keys[rows][cols] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', 'x'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}};
byte rowPins[rows] = {7, 6, 5, 4}; // connect to the row pinouts of the keypad
byte colPins[cols] = {3, 2, 1, 0}; // connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

LiquidCrystal lcd(50, 51, 45, 46, 47, 48);

int led_pins[4] = {16, 17, 18, 19};

uint8_t modes_time[4] = {3, 6, 6, 6};

int current_mode = 0;
bool is_washing = false;
int start_time;
int remaining_time = 5;
int elapsedMemorySaved = 0;
bool hold = false;

const uint8_t device_address = 80;
// #define device_address 0b1010000
const uint8_t memory_address = 0;

void restore_modes(void);
void write_to_mem(uint8_t data_size, uint8_t mem_addr, char *data);
void read_from_mem(uint8_t data_size, uint8_t mem_addr, char *data);
void update_lcd(int mode);
void update_lcd_timer(int passed_time);
void update_LEDs(int mode);

void setup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(led_pins[i], OUTPUT);
  }

  Serial3.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);

  restore_modes();
}

char pressed_key;
int last_mode = -1;

void loop()
{
  while (true)
  {
    char key = keypad.getKey();

    if (key != NO_KEY)
    {

      if (key == '/' && current_mode == 4) // restart
      {
        is_washing = false;
        last_mode = -1;
        current_mode = 0;
        update_LEDs(current_mode);
        update_lcd(current_mode);
      }
      else if (key >= '0' && key <= '9')
      {
        Serial3.print("press X to save in current mode or C to start this mode");
        Serial3.println(current_mode + 1);
        pressed_key = key;
      }
      else if (key == '#' && !is_washing)
      {
        if (pressed_key >= '0' && pressed_key <= '4')
        {
          current_mode = (int)pressed_key - 48;
          char data_to_store[1] = {pressed_key};
          write_to_mem(1, memory_address, data_to_store);
          update_LEDs(current_mode);
          update_lcd(current_mode);
        }
      }
      else if (key == 'x')
      {
        Serial3.println("try to save presed key: ");
        modes_time[current_mode] = (int)pressed_key - 48;
        char data_to_save[1] = {pressed_key};
        uint8_t mem_addr = memory_address + current_mode + 1;
        write_to_mem(1, mem_addr, data_to_save);
      }

      if (key == '+')
      {
        is_washing = true;
      }
      else if (key == '-')
      {
        is_washing = false;
        modes_time[current_mode] = remaining_time / 1000 - (millis() - start_time) / 1000;
        last_mode = -1;
      }
    }
    if (is_washing && current_mode != 4)
    {
      if (last_mode != current_mode)
      {
        last_mode = current_mode;
        start_time = millis();
        Serial3.println("start new mod");
        remaining_time = modes_time[current_mode] * 1000;
        Serial3.println(remaining_time);
      }
      else
      {
        int elapsed_time_mills = (millis() - start_time) % 1000;
        if (!(elapsed_time_mills >= 20 && elapsed_time_mills <= 980)) // update remaining time in the edges
        {
          int elapsed_time = (millis() - start_time) / 1000;

          update_lcd_timer(elapsed_time);
        }
        if (remaining_time / 1000 - (millis() - start_time) / 1000 <= 0)
        {
          current_mode = (current_mode + 1) % 5;
          if (current_mode == 4)
            is_washing = false;
          char mode_char = current_mode + 48;
          char data_to_store[1] = {mode_char};
          write_to_mem(1, memory_address, data_to_store);
          update_lcd(current_mode);
          update_LEDs(current_mode);
        }
      }
    }
  }
}

void restore_modes(void)
{
  char restored_modes[5];
  Serial3.println("restoring");
  read_from_mem(5, memory_address, restored_modes);
  Serial3.println(restored_modes[0]);

  if (restored_modes[0] >= '0' && restored_modes[0] <= '4')
  {
    current_mode = restored_modes[0] - 48;
  }

  for (int i = 0; i <= 3; i++)
  {
    if (restored_modes[i + 1] > '0' && restored_modes[i + 1] <= '9')
    {
      modes_time[i] = (uint8_t)restored_modes[i + 1] - 48;
    }
  }
  update_lcd(current_mode);
  update_LEDs(current_mode);
}

void write_to_mem(uint8_t data_size, uint8_t mem_addr, char *data)
{
  Wire.beginTransmission(device_address);
  Wire.write((uint8_t)((mem_addr & 0xFF00) >> 8));
  Wire.write((uint8_t)((mem_addr & 0x00FF) >> 0));

  Serial3.println("writing to memory: ");
  for (int i = 0; i < data_size; i++)
  {
    uint8_t d = (uint8_t)data[i] - 48;
    Serial3.print(i);
    Serial3.print("-Data = ");
    Serial3.print(data[i]);
    Serial3.print("  |  ");
    Wire.write(d);
    delay(50);
  }

  Wire.endTransmission();
  delay(50);
}
void read_from_mem(uint8_t data_size, uint8_t mem_addr, char *data)
{
  Wire.beginTransmission(device_address);
  Wire.write((uint8_t)((mem_addr & 0xFF00) >> 8));
  Wire.write((uint8_t)((mem_addr & 0x00FF) >> 0));
  Wire.endTransmission();

  Wire.requestFrom(device_address, data_size);
  Serial3.println("reading form memory: ");
  for (int i = 0; i < data_size; i++)
  {
    data[i] = Wire.read() + 48;
    Serial3.print(i);
    Serial3.print("-Data = ");
    Serial3.print(data[i]);
    Serial3.print("  |  ");
  }
  Serial3.println();
}

void update_LEDs(int mode)
{
  if (mode == 4)
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(led_pins[i], HIGH);
    }
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(led_pins[i], LOW);
    }
    digitalWrite(led_pins[mode], HIGH);
  }
}

void update_lcd(int mode)
{

  lcd.clear();
  switch (mode)
  {
  case 0:
    lcd.print("pre_wash");
    break;
  case 1:
    lcd.print("detergent wash");
    break;
  case 2:
    lcd.print("wash with water");
    break;
  case 3:
    lcd.print("drying");
    break;
  case 4:
    lcd.print("finished");
    break;
  }
}

void update_lcd_timer(int passed_time)
{
  update_lcd(current_mode);
  lcd.setCursor(0, 1);
  String time_to_show = String(remaining_time / 1000 - passed_time);
  lcd.print(time_to_show);
}
