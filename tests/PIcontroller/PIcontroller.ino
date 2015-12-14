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

  const float Wantedspeed = 2;
  float Actualspeed;
  float Error;
  float Integral = 0;
  float ControllerOutput;
  float DutyPrSpeed;
  float Duty = 0;
  const float Stiction = 1.1; // 0.38/0.486   [V]  .. that is:  stiction [m*s^-1] / SysGain [s*m^-1 *V]
  const float SysGain = 0.486;
  const float Kp = 2.0576; //.8;     // Tuned parameters: Kp = .8 and Ki = 6
  const float Ki = 9.7517; //6;      // For time constant equal to that of the plant Kp = 2.0576 and Ki = 9.7517
                                     // however, the rise is too fast for the battery, which drops voltage fast at big currnets,
                                     // so Kp and Ki are recalculated for half the time-constant of the plant
                                     // to allow for a longer rise-time and thus less drop in the battery voltage
                   
  while(1)
  {
    batReading = analogRead(8); //reading battery voltage
    speed0 = getSpeed(0);       //reading speed of first belt
    speed1 = getSpeed(1);       //reading speed of the other belt
    timestamp = millis();       //getting time at which data was recorded


    Actualspeed = (speed0 + speed1)/2; // average speed of the vehicle
    
    if(timestamp > 5000)
    {
      Error = Wantedspeed - Actualspeed;
      
      //if( ControllerOutput < ((float)batReading/102.4) ) //Only increase integral error if the battery is not in saturation
      //{
        Integral = Integral + (Error*0.030); //Delta t = 0.03 s = sample time i.e. 30 ms
      //}
                                                                                                                   //-------------IN THE CODE--------------------------------------------------------------
      ControllerOutput = ((Kp * Error) + (Ki * Integral) + Stiction);                                              // dutyNeeded = controllOut * 100 /( batVolt * SysGain )
      DutyPrSpeed = 100.0/((float)batReading/102.4); // Duty cycle pr volt (% pr V) (divided by 102.4 = volts)     // 
      Duty = ControllerOutput * DutyPrSpeed; // ------------------------------------------------------------------LINK TO MODEL------------------------------------------------------------------
      if(Duty > 100) Duty = 100;             // controllerOut = VoltNeeded --> plant --> m/s
      if(Duty < 0) Duty = 0;                 // batVolt/100 = [volt/duty] => ( batVolt/100 ) *dutyNeeded = VoltNeeded <=> dutyNeeded =   VoltNeeded        / ( batVolt/100 )
    }                                        //                                                                       <=> dutyNeeded =   controllOut       / ( batVolt/100 )
                                             //                                                                       <=> dutyNeeded =   (controllOut*100) /  batVolt
    Serial.print(timestamp);
    Serial.print(',');
    Serial.print(Actualspeed);
    Serial.print(',');
    Serial.print((float)batReading/102.4);
    Serial.print(',');
    Serial.print(ControllerOutput);
    Serial.print(',');
    Serial.print(Ki * Integral);
    Serial.print(',');
    Serial.println(Kp * Error);
    //Serial.print(',');
    //Serial.println(Error);

    //DutyPrSpeed = 100.0/((float)batReading/102.4);  //<
    //Duty =  Stiction * DutyPrSpeed;                 //<< For testing stiction
    //speed(Duty);                                    //<
    
    if(timestamp > 2000 && timestamp <= 5000) speed(20);
    if(timestamp > 5000 && timestamp <= 15000) speed(Duty);
    if(timestamp > 15000) speed(0);
    
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
