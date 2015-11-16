#include "motor_driver.h"
#include <arduino.h>

int initMotor(){
  pinMode(9, OUTPUT);
  TCCR2A = 0;
  TCCR2B = 0;                     // Halt counter by setting clock select bits to 0 (No clock source)
  TCNT2 = 0x00;                   // Start counting the timer. 
  
  OCR2A = 100;                   // Reset after counting to 100 (corrosponds to 20KHz)


  OCR2B = 0;                  //To set the center pulsewidth, we want 1400 us and timerperiode is 0.5 us
  TCCR2A |= (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
  TCCR2B |= (1<<CS21)| (1<<WGM22);                       // Sets timer prescaler to F_CPU/8 = 2 MHz - makes the time timer count at 2 MHz (has to be a number which divides into 30ms)
}




int speed (int iSpeed){
  if (iSpeed<0) iSpeed = 0;
  if (iSpeed>99) iSpeed = 99;
  //int iAnalogSpeed = (iSpeed * 255) / 100;  //convert in analog scale
  OCR2B = iSpeed;
  return 0;
}

int direction(int iDir){
//pin 2 and 4 to choose backwardvand forward
int iFlag;

if (iDir == 0)    //break
{
  digitalWrite(dPinMove1, 0);
  digitalWrite(dPinMove2, 0);
  iFlag = 0;

}

if (iDir == 1)    //Forward
{
  digitalWrite(dPinMove1, 1);
  digitalWrite(dPinMove2, 0);
  iFlag = 1;
}

if (iDir == 2)    //backward
{
  digitalWrite(dPinMove1, 0);
  digitalWrite(dPinMove2, 1);
  iFlag = 2;
}

  return iFlag;
}


int motorCurrent(){

  int iCurrentRead = analogRead(dPinCurrent1) + analogRead(dPinCurrent2);
  return iCurrentRead;

}


int enableMotor(int iOnOff){
  digitalWrite(dPinOnOff, iOnOff);
  return 0;
}


int test(int iTest)
{
  if(iTest == 0){
    return 5;
    }

  if(iTest == 1){
    return 4;
    }
}
