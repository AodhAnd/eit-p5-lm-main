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

void PI_controller(){

  const float Wantedspeed = 1.4;
  float Actualspeed;
  float Error;
  float Integral = 0;
  float ControllerOutput;
  float DutyPrSpeed;
  float Duty = 0;
  const float Stiction = 0.38;
  const float SysGain = 0.486;
  const float Ki = 4.8759;  
  const float Kp = 1.0288;

  while(1){
    batReading = analogRead(8); //reading battery voltage
    speed0 = getSpeed(0);       //reading speed of first belt
    speed1 = getSpeed(1);       //reading speed of the other belt
    timestamp = millis();       //getting time at which data was recorded


    Actualspeed = (speed0 + speed1)/2; // average speed of the vehicle
    
    if(timestamp > 5000)
    {
      Error = Wantedspeed - Actualspeed;
      Integral = Integral + (Error*0.030); //Delta t = 0.03 s = sample time i.e. 30 ms
      ControllerOutput = (Kp * Error + Ki * Integral + Stiction);
      DutyPrSpeed = 100.0/(((float)batReading/102.4)*SysGain); // Duty cycle pr speed  (% pr m/s)
      Duty = ControllerOutput * DutyPrSpeed;
      if(Duty > 100) Duty = 100;
      if(Duty < 0) Duty = 0;
    }
//    Serial.print("Duty: ");
//    Serial.print(Duty);
//    Serial.print(" Con: ");
//    Serial.print(ControllerOutput);
//    Serial.print(" error: ");
//    Serial.print(Error);
//    Serial.print(" integral: ");
//    Serial.print(Integral);
    Serial.print(timestamp);
    Serial.print(',');
    Serial.println(Actualspeed);

    if(timestamp > 2000 && timestamp < 5000) speed(20);
    if(timestamp > 5000) speed(Duty);
    if(timestamp > 10000) speed(0);
    
    delay(30);
    }
  }

void setup() {
    k_init(2,1,0);

  pinMode(5,OUTPUT);
  initServo();
  initMotor();
  pinMode(dPinMove1, OUTPUT); 
  pinMode(dPinMove2, OUTPUT);
  pinMode(dPinOnOff, OUTPUT);

  enableMotor(1);
  direction(1);

  Serial.begin(115200);
  Serial.println("REBOOT");
  pinMode(35,INPUT);

  initHallTimers();

  delay(1000);
  pTaskInfo=k_crt_task(tSpeed,10,stack,300);
  task2=k_crt_task(PI_controller,11,stack2,300);

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
