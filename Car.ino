#include <Wire.h>
//Defining car address
#define CAR_ADDR 9
//Defining threshold to start motors
#define threshold 780

//Defining left motors
int in1 = 2;
int in2 = 4;
int enA = 3;

//Defining right motors
int in3 = 5;
int in4 = 7;
int enB = 6;

//Defining received signal variables
volatile byte sig0x1, sig0x2, sig1x1, sig1x2, sig2x1, sig2x2, sig3x1, sig3x2;
volatile int signal0, signal1, signal2, signal3;

void setup() {
  // put your setup code here, to run once:

  //Setting up ouput pins for left motors
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //Setting up ouput pins for right motors
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //Setting up built-in LED output
  pinMode(LED_BUILTIN, OUTPUT);
  
  //Start I2C communications
  Wire.begin(CAR_ADDR);
  //Have Arduino receive signals through I2C
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  
}


void loop() {
  delay(50);
}

void receiveEvent(int numBytes){
  //Reads sent bytes from I2C
  sig0x1 = Wire.read();  //x1 hilds upper byte of received a
  sig0x2 = Wire.read();  //x2 holds lower byte of received a
  sig1x1 = Wire.read();  //x1 hilds upper byte of received a
  sig1x2 = Wire.read();  //x2 holds lower byte of received a
  sig2x1 = Wire.read();  //x1 hilds upper byte of received a
  sig2x2 = Wire.read();  //x2 holds lower byte of received a
  sig3x1 = Wire.read();  //x1 hilds upper byte of received a
  sig3x2 = Wire.read();  //x2 holds lower byte of received a

  //Converts bytes back into integer value
  signal0 = (int)sig0x1 << 8 | (int)sig0x2;
  signal1 = (int)sig1x1 << 8 | (int)sig1x2;
  signal2 = (int)sig2x1 << 8 | (int)sig2x2;
  signal3 = (int)sig3x1 << 8 | (int)sig3x2;

  if(signal0 >= threshold){
    //digitalWrite(LED_BUILTIN, HIGH);
    moveForward();
  }
  else if(signal1 >= threshold){
    moveBackward();
  }
  else if(signal3 >= threshold){
    rotateRight();
  }
  else if(signal2 >= threshold){
    rotateLeft();
  }
  else{
    //digitalWrite(LED_BUILTIN, LOW);
    stop();
  }
  
  
}

void moveForward(){
  //Left motors rotate forwards
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(enA,100);

  //Right motors rotate forwards
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  digitalWrite(enB,100);
}

void moveBackward(){
  //Left motors rotate backwards
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(enA,100);

  //Right motors rotate backwards
  digitalWrite(in3,LOW);  
  digitalWrite(in4,HIGH);
  digitalWrite(enB,100);
}

void rotateLeft(){
  //Left motors rotate backwards
  digitalWrite(in1,LOW); 
  digitalWrite(in2,HIGH);
  digitalWrite(enA,100);

  //Right motors rotate forwards
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,LOW);
  digitalWrite(enB,100);
}

void rotateRight(){
  //Left motors rotate forwards
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(enA,100);

  //Right motors rotate backwards
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  digitalWrite(enB,100);
}

void stop(){
  //Stops left motors
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(enA,100);

  //Stops right motors
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(enB,100);
}