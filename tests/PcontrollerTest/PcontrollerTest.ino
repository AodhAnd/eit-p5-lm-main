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

void P_controller(){

  const float Wantedspeed = 2.0;
  const float Speedtoduty = 1.0/(7.2*0.42);//to get from speed to duty cycle

  float Actualspeed;
  float Error;
  const float PGain = 1.0;
  int duty;
  float test;
  while(1){
    
    batReading = analogRead(8); //reading battery voltage
    speed0 = getSpeed(0);       //reading speed of first belt
    speed1 = getSpeed(1);       //reading speed of the other belt
    timestamp = millis();       //getting time at which data was recorded

  If(timestamp > 4500){
    Actualspeed = (speed0 + speed1)/2; // average speed of the vehicle

    Error = Wantedspeed - Actualspeed;

    test = ((Error*PGain+Wantedspeed)*Speedtoduty)*100; 
    duty = test;
    if(duty > 100) duty = 100;
    if(duty < 0) duty = 0;
  }
    //number between 0 and a 100%

    if(timestamp < 10000) speed(duty);
    else speed(0);
    
    //printing out the data whith commas for easy export as .scv-file:
    Serial.print(test);
    Serial.print(",");
    Serial.print(duty);
    Serial.print(",");
    Serial.print(Error);
    Serial.print(",");
    Serial.print(speed0);
    Serial.print(",");
    Serial.print(speed1);
    Serial.print(",");
    Serial.print(timestamp);
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
  speed(10);
  pTaskInfo=k_crt_task(tSpeed,10,stack,300);
  task2=k_crt_task(P_controller,11,stack2,300);

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
