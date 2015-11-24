#include "hall.h"
#include <krnl.h>
#include "motor_driver.h"
#include "myservo.h"
#include <Wire.h>
#include "Magnetometer.h"

// This is the value to change to change the steering angle
// (servo pulse-width)
//#define SERVO_PW 1650

struct k_t *pTaskInfo, *task2;

char stack[300];  // Stack of task1
char stack2[1000]; // Stack of task2
float speed0;     // Speed of belt 1
float speed1;     // Speed of belt 1
long int timestamp;
char byte1;
char byte2;
int batReading;   // Battery voltage reading

void steeringStepResponse(){

  const float Wantedspeed = 2;
  const float SysGain = 0.49;
  float Speedtoduty;
  int servoPulseWidth = SERVO_MIDDLE_PW; // X seconds pulse width makes the vehicle go straight(-ish)
  float Actualspeed;
  int duty;
  float tmp;
  float Error;
  const float PGain = 1.0;
  float feedFwd = Wantedspeed;
  
  
  float compassAverage;
  float sum = 0;
  int i;

  while(1){
    
    batReading = analogRead(8); //reading battery voltage
    speed0 = getSpeed(0);       //reading speed of first belt
    speed1 = getSpeed(1);       //reading speed of the other belt
    timestamp = millis();       //getting time at which data was recorded

    // The servo is set whatever happens
    setServo(servoPulseWidth);
    
    Actualspeed = (speed0 + speed1)/2; // average speed of the vehicle
    
    // Vehicle starts after 2 seconds
    if(timestamp>2000)    //P-Controler with feed forward
    {
      Error = Wantedspeed - Actualspeed;
      Speedtoduty = 1.0/(((float)batReading/102.4)*SysGain);// Battery reading: 1024 = 10V, so 1V = 102.4. multiply that with the system gain to calculate the duty cycle.
      //duty = Speedtoduty*100.0; 
      tmp = (  ((Error)*PGain+feedFwd+0.38)*Speedtoduty)*100.0;//actual P-Controller
      duty=tmp;
      if(duty > 100) duty = 100;
      if(duty < 0) duty = 0;
    }
    
    
    // Steering is triggered 3s later (at t=5s)
    if(timestamp>5000) servoPulseWidth = 1600;  //left
    //if(timestamp>6000) servoPulseWidth = 1150;  //straight
    
    
    if(timestamp>7000) servoPulseWidth = 1070;  //right
    //if(timestamp>8000) servoPulseWidth = 1150;  //straight
    
    
    if(timestamp>9000) servoPulseWidth = 1600;  //left
    //if(timestamp>10000) servoPulseWidth = 1150;  //straight
    
    
    if(timestamp>11000) servoPulseWidth = 1070;  //right
    //if(timestamp>12000) servoPulseWidth = 1150;  //straight

    if(timestamp>13000) servoPulseWidth = 1600;  //left
    //if(timestamp>14000) servoPulseWidth = 1150;  //straight

    //stop at the end
    if(timestamp < 15000) speed(duty);      //set the speed
    else speed(0);                          //stop at the end
    
    
    
    
    
    //filtering of the angle data, rolling average of 5
    sum = 0;
    for(i=0;i<4;i++) sum += CompassGet();
    compassAverage = sum/4;
      
   
    //printing out the data whith commas for easy export as .csv-file:
    Serial.print(compassAverage);
    //Serial.print(CompassGet());
    Serial.print(",");
    Serial.print((float)batReading/102.4);    //voltage
    Serial.print(",");
    Serial.print(Actualspeed);
    Serial.print(",");
    Serial.print(timestamp);
    Serial.print("\n");
    Serial.print("\r");       //carriage return to return the curser for each new line
    delay(30);
    
    }
  }



void setup() {
  k_init(2,1,0);

  pinMode(5,OUTPUT);
  initServo();
  
  pinMode(dPinMove1, OUTPUT); 
  pinMode(dPinMove2, OUTPUT);
  pinMode(dPinOnOff, OUTPUT);

  // Set up the motor
  initMotor();
  enableMotor(1);
  direction(1);    //move forward
  
  // Set up the compass/gyro/accelerometer sensors
  CompassSetup();

  // Init Hall sensors
  pinMode(35,INPUT);
  initHallTimers();

  Serial.begin(9600);
  Serial.println("REBOOT");

  delay(2000);
  pTaskInfo=k_crt_task(tSpeed,10,stack,300);              //hall sensors
  task2=k_crt_task(steeringStepResponse,11,stack2,1000);   //main code for the test

  k_start(1); // krnl runs with 1 msec heartbeat
  /* NOTE: legal time values:
     1-10 : 1-10 milliseconds
     19,20,30,40...10000: 10,20... milliseconds
     if you try negative or 11,54 etc it will not start
  */
}

void loop() {
  // Do not put code here when using JDN's krnl
}
