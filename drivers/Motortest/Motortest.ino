#include "motor_driver.h"



void setup()
{
pinMode(dPinMove1, OUTPUT);
pinMode(dPinMove2, OUTPUT);
pinMode(dPinOnOff, OUTPUT);
pinMode(dPinSpeed, OUTPUT);
enableMotor(1);
Serial.begin(9600);
}

void loop(){
  direction(1);
  for(int i=0;i<=50;i++){
    speed(i);
    delay(10);
  }
  
  speed(50);
  delay(2000);
  for(int i=50;i>=0;i--){
    speed(i);
    delay(10);
  }
  speed(0);
  delay(100);
  direction(2);
  for(int i=0;i<=50;i++){
    speed(i);
    delay(10);
  }
  
  speed(50);
  delay(2000);
  for(int i=50;i>=0;i--){
    speed(i);
    delay(10);
  }
  delay(100);  
  
  
  }
