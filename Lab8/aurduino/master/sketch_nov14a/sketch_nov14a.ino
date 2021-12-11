#include <SPI.h>

#define SS 48
#define SS1 49

byte MESSAGE[12] = {'a','m','i','r','9','8','3','1','0','6','5'};
byte HI[7] = {'H','i', ' ', 'A', 'm', 'i', 'r'};

bool sendName = true;
bool sendHelloHi = false;
bool sendTempLightBool = false;

void setup() {
  pinMode(SS, OUTPUT);
  pinMode(SS1, OUTPUT);
  digitalWrite(SS, HIGH);
  digitalWrite(SS1, HIGH);
  
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);

  Serial.begin(9600);
  Serial.println("This is master");
}

void printName(){
  digitalWrite(SS, LOW); // Enable Slave 0
  delay(50);
  
  for(int i=0; i<12; i++){
    SPI.transfer(MESSAGE[i]);
    Serial.print((char)MESSAGE[i]);
    delay(10); 
  }
  Serial.println("");

  digitalWrite(SS, HIGH); // Disable Slave 0
  delay(500);
  
  delay(1000);
}

void printHiHello(){
  Serial.println("Sending>>Name");
  
  digitalWrite(SS, LOW); // Enable Slave 0
  delay(50);
  
  for(int i=0; i<12; i++){
    SPI.transfer(MESSAGE[i]);
    Serial.print((char)MESSAGE[i]);
    delay(10); 
  }
  delay(50);
  
  digitalWrite(SS, HIGH);// Disable Slave 0
  delay(500);

  Serial.println("Sending>>HI");
  
  digitalWrite(SS1, LOW); // Enable Slave 1
  delay(50);
  
  for(int i=0; i<7; i++){
    SPI.transfer(HI[i]);
    Serial.print((char)HI[i]);
    delay(10); 
  }
  delay(50);
  
  digitalWrite(SS1, HIGH); // Disable Slave 1
  delay(500);
}

void sendTempLight(){
  digitalWrite(SS, LOW); // Enable Slave 0
  delay(50);
  
  float temp = analogRead(A0);
  temp *= 0.48828125;
  Serial.println("Current temperature: [" + String(temp)+"*C");
  byte tempTemperature[2];
  tempTemperature[0] = (int)temp;
  tempTemperature[1] = (int)temp >> 8; 
   
  for(int i=0; i<2; i++){
    SPI.transfer(tempTemperature[i]);
    delay(10); 
  }
  delay(50);
  
  digitalWrite(SS, HIGH); // Disable Slave 0
  delay(500);

  digitalWrite(SS1, LOW); // Enable Slave 1
  delay(50);

  int analogLight = analogRead(A1) ;
  byte tempLight[2];
  tempLight[0] = analogLight;
  tempLight[1] = analogLight >> 8;
  
  Serial.println("Current Light: " + String(analogLight));
  for(int i=0; i<2; i++){
    SPI.transfer(tempLight[i]);
    delay(10); 
  }
  delay(50);
  
  digitalWrite(SS1, HIGH); // Disable Slave 1
  delay(500);
}

void loop() {
  if (sendName) 
    printName();
  else if (sendHelloHi)
    printHiHello();
  else if (sendTempLightBool)
    sendTempLight();  
}
