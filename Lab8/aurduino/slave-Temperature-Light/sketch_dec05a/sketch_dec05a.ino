#include <SPI.h>

#define SS 53
#define MOSI 51
#define MISO 50
#define SCK 52

volatile int i = 0;
byte myArray[2];

void setup() {
  Serial.begin(9600);
  Serial.println("This is slave");
  
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, INPUT);
  
  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE); // interrupts
  SPI.attachInterrupt();  // allows SPI interrupt
  
  Serial.println("This is slave");
}

void loop() {
 if (i == 2){
    Serial.print("Received: ");
    int x = myArray[0] + ( myArray[1] << 8);
    Serial.print(x); 
    Serial.println("");
    i=0;
  }
}

ISR (SPI_STC_vect)   // Inerrrput routine function
{
  Serial.print("|");
  Serial.print(SPDR);
  Serial.print(" ");
  Serial.print(i);
  Serial.println("|");
  myArray[i] = SPDR;
  i++;
}
