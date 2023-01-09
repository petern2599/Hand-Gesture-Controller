#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  //Setting up flex sensor input pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  //Setting up Arduino built-in LED output
  pinMode(LED_BUILTIN, OUTPUT);

  //Starting I2C communication
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Start initial delay
  delay(50);

  //Read flex sensor input
  int signal0 = analogRead(A0);
  int signal1 = analogRead(A1);
  int signal2 = analogRead(A2);
  int signal3 = analogRead(A3);
  //Added to signal because flex sensor is on pinky
  signal3 = signal3+30;

  //Print signal
  Serial.println(signal3);

  //Transmit signal through I2C
  Wire.beginTransmission(9);
  Wire.write(highByte(signal0));
  Wire.write(lowByte(signal0));
  Wire.write(highByte(signal1));
  Wire.write(lowByte(signal1));
  Wire.write(highByte(signal2));
  Wire.write(lowByte(signal2));
  Wire.write(highByte(signal3));
  Wire.write(lowByte(signal3));
  Wire.endTransmission();
  
  //Serial.println(signal0);
}
