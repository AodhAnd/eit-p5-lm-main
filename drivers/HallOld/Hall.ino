#include "hall.h"
#include <krnl.h>
#include "motor_driver.h"

struct k_t *pTaskInfo, *task2;

char stack[100];
char stack2[200];

void printSpeed(){
  char buff[10];
  String valueString = "";
  while(1){
    Serial.print("Speed 0: ");
    Serial.print(getSpeed(0),5);
    Serial.print(" Speed 1: ");
    Serial.print(getSpeed(1),5);
    Serial.write("\n");
  }
}

void setup() {
    k_init(2,1,0);
  
  pinMode(dPinMove1, OUTPUT); 
  pinMode(dPinMove2, OUTPUT);
  pinMode(dPinOnOff, OUTPUT);
  pinMode(dPinSpeed, OUTPUT);
  enableMotor(1);
  direction(1);

  Serial.begin(9600);
  Serial.println("REBOOT");
  pinMode(35,INPUT);

  initHallTimers();
    speed(10);


  pTaskInfo=k_crt_task(tSpeed,10,stack,100);
  task2=k_crt_task(printSpeed,11,stack2,200);

  k_start(1); // krnl runs with 1 msec heartbeat
  /* NOTE: legal time values:
     1-10 : 1-10 milliseconds
     19,20,30,40...10000: 10,20... milliseconds
     if you try negative or 11,54 etc it will not start
  */
}

void loop() {
  // put your main code here, to run repeatedly:

}
