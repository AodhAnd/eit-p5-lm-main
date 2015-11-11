#include "hall.h"
#include <krnl.h>
#include "motor_driver.h"
#include "myservo.h"

struct k_t *pTaskInfo, *task2;

char stack[300];
char stack2[300];
float speed0;
float speed1;
long int timestamp;
char byte1;
char byte2;
int batReading;

void int DutyCycle(int dutyCycle)
{
  int pulseWidth = dutyCycle * 300;
}

void printSpeed()
{
  int pulsewidth = 880;
  int count = 0;
  while(1)
  {
    count++;
    
    if (count > 100){
      pulsewidth+=10;
      count = 0;
    }
    
    if( pulsewidth >= 1500)
    {
      setServo(1450);
      speed(0);
    }
    else setServo(pulsewidth);
    
    batReading = analogRead(8); //reading battery voltage
    speed0 = getSpeed(0);       //reading speed of first belt
    speed1 = getSpeed(1);       //reading speed of the other belt
    timestamp = millis();       //getting time at which data was recorded

    //printing out the data whith commas for easy export as .scv-file:
    Serial.print(batReading);
    Serial.print(",");
    Serial.print(speed0);
    Serial.print(",");
    Serial.print(speed1);
    Serial.print(",");
    Serial.print(timestamp);
    Serial.print(",");
    Serial.print(pulsewidth);
    Serial.print("\n");
    
    Serial.print("\r");       //carrige return to return the curser for each new line
    
    delay(20);
    }
  }

void setup() {
    k_init(2,1,0);
  pinMode(5,OUTPUT);
  initServo();
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
  delay(2000);
  speed(20);
  delay(1000);

  pTaskInfo=k_crt_task(tSpeed,10,stack,300);
  task2=k_crt_task(printSpeed,11,stack2,300);

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
