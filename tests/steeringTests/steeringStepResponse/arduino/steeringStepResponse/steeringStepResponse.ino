#include "hall.h"
#include <krnl.h>
#include "motor_driver.h"
#include "myservo.h"
#include <Wire.h>
#include "Magnetometer.h"

// This is the value to change to change the steering angle
// (servo pulse-width)
#define SERVO_PW 1590

struct k_t *pTaskInfo, *task2;

char stack[300];
char stack2[300];
float speed0;
float speed1;
long int timestamp;
char byte1;
char byte2;
int batReading;

void steeringStepResponse(){

  const float Wantedspeed = 2;
  const float SysGain = 0.49;
  float Speedtoduty;
  int servoPulseWidth = SERVO_MIDDLE_PW; // 1578s pulse width makes the vehicle go straight(-ish)
  float Actualspeed;
  float duty;


  while(1){
    
    batReading = analogRead(8); //reading battery voltage
    speed0 = getSpeed(0);       //reading speed of first belt
    speed1 = getSpeed(1);       //reading speed of the other belt
    timestamp = millis();       //getting time at which data was recorded

    Actualspeed = (speed0 + speed1)/2; // average speed of the vehicle

    // The servo is set whatever happens
    setServo(servoPulseWidth);

    // Vehicle starts after 2 seconds
    if(timestamp>2000){
    // Battery reading: 1024 = 10V, so 1V = 102.4. multiply that with the system gain to calculate the speed-to-duty-cycle ratio.
    Speedtoduty = 1.0/(((float)batReading/102.4)*SysGain) * 100.0;
    duty = Wantedspeed*Speedtoduty + 0.38;
    // The motor duty cycle should stay in the range of 0-100%
    if(duty > 100) duty = 100;
    if(duty < 0) duty = 0;
    }
    // Steering is triggered 3s later (at t=5s)
    if(timestamp>5000) servoPulseWidth = SERVO_PW;

    if(timestamp < 10000) speed(duty);
    else speed(0);
    
    //printing out the data whith commas for easy export as .csv-file:
    Serial.print(CompassGet());
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
  task2=k_crt_task(steeringStepResponse,11,stack2,300);   //main code for the test

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
