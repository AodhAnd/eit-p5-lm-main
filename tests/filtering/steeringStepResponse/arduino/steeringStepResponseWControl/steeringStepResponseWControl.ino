sudo putt
#include "hall.h"
#include <krnl.h>
#include "motor_driver.h"
#include "myservo.h"
#include <Wire.h>
#include <HMC5883L.h>


HMC5883L compass; //Copy the folder "HMC5883L" in the folder "C:\Program Files\Arduino\libraries" and restart the arduino IDE.

float xv, yv, zv;

//calibrated_values[3] is the global array where the calibrated data will be placed
//calibrated_values[3]: [0]=Xc, [1]=Yc, [2]=Zc
float calibrated_values[3];   
//transformation(float uncalibrated_values[3]) is the function of the magnetometer data correction 
//uncalibrated_values[3] is the array of the non calibrated magnetometer data
//uncalibrated_values[3]: [0]=Xnc, [1]=Ync, [2]=Znc
void transformation(float uncalibrated_values[3])    
{
  //calibration_matrix[3][3] is the transformation matrix
  //replace M11, M12,..,M33 with your transformation matrix data
  double calibration_matrix[3][3] = 
  {
    {1.206, -0.002, 0.039},
    {0.013, 1.193, -0.004},
    {-0.004, -0.025, 1.414}  
  };
  //bias[3] is the bias
  //replace Bx, By, Bz with your bias data
  double bias[3] = 
  {
    -52.455,
    -164.666,
    -143.707
  };  
  //calculation
  for (int i=0; i<3; ++i) uncalibrated_values[i] = uncalibrated_values[i] - bias[i];
  float result[3] = {0, 0, 0};
  for (int i=0; i<3; ++i)
    for (int j=0; j<3; ++j)
      result[i] += calibration_matrix[i][j] * uncalibrated_values[j];
  for (int i=0; i<3; ++i) calibrated_values[i] = result[i];
}

void setupHMC5883L()
{  
  compass.SetScale(0.88);
  compass.SetMeasurementMode(Measurement_Continuous);
}
 
void getHeading()
{ 
  MagnetometerRaw raw = compass.ReadRawAxis();
  xv = (float)raw.XAxis;
  yv = (float)raw.YAxis;
  zv = (float)raw.ZAxis;
 
}

// This is the value to change to change the steering angle
// (servo pulse-width)
//#define SERVO_PW 1650

struct k_t *task1, *task2, *task3;

struct k_t *sem2; //semaphore for Steering controller

char stack[300];  // Stack of Hall sensor
char stack2[300]; // Stack of Speed Control
char stack3[1000]; // Stack of Steering control
float speed0;     // Speed of belt 1
float speed1;     // Speed of belt 1
long int timestamp;
long int timestampMagneto;
char byte1;
char byte2;
int batReading;   // Battery voltage reading

float values_from_magnetometer[3];

float angles[8];

void SteeringControl(){
   
   int servoPulseWidth = SERVO_MIDDLE_PW; // X seconds pulse width makes the vehicle go straight(-ish)
   float MAG_Heading_Old;                 // Heading to compare with from last run
   float MAG_Heading_New;                 // Current heading
   float Omega_current;                   // Current angular velocity
   float Omega_error;                     // Error angular velocity
   float Omega_wanted = 0;                // Wanted angular velocity
   float P_out;                           // Output from P controller

   float P_gain = 0.2;

   const int rightOffset = -250; 
   const int leftOffset = 250;
   
   k_set_sem_timer(sem2,50); // krnl will signal sem every 50th tick
   
/* Get initial heading */   
  getHeading();
  values_from_magnetometer[0] = xv;
  values_from_magnetometer[1] = yv;
  values_from_magnetometer[2] = zv;
  transformation(values_from_magnetometer);
  MAG_Heading_Old = atan2(-calibrated_values[1], calibrated_values[0])*(180.0/3.14);
  int i;
  for (i=0;i<8;i++){angles[i]= MAG_Heading_Old;} //start with current direction in every slot; 

  int sampleNumber = 0;
  while(1){
  
/* Get current heading */  
  getHeading();
  values_from_magnetometer[0] = xv;
  values_from_magnetometer[1] = yv;
  values_from_magnetometer[2] = zv;
  transformation(values_from_magnetometer);
  angles[sampleNumber] = atan2(-calibrated_values[1], calibrated_values[0])*(180.0/3.14);
  for(i=0; i<8; i++){MAG_Heading_New += angles[i];}
  MAG_Heading_New = MAG_Heading_New /8; // Rolling average
  sampleNumber++;

  if (sampleNumber > 8){sampleNumber = 0;}
  
/* Calculate current angular velocity  */
  Omega_current = (MAG_Heading_New - MAG_Heading_Old);
  if (Omega_current < 180){Omega_current +=360;}
  if (Omega_current > 180){Omega_current -=360;}
  Omega_current = Omega_current * 20;  // (Old heading - New heading)/50ms = degrees per second
  MAG_Heading_Old = MAG_Heading_New;

  Omega_error = Omega_wanted - Omega_current;

  P_out = Omega_error * P_gain;

  if(P_out>0){setServo(SERVO_MIDDLE_PW+leftOffset+P_out);}
  if(P_out<0){setServo(SERVO_MIDDLE_PW+rightOffset+P_out);}
  if(P_out==0){setServo(SERVO_MIDDLE_PW);}
    
  //Serial.flush(); 

  
  

  Serial.print(MAG_Heading_New);
  Serial.print(',');
  Serial.print(P_out);
  Serial.println(',');
  Serial.print(timestampMagneto);
  Serial.println(',');
    
    if(timestamp>3000) Omega_wanted = -10;  //right
    if(timestamp>5000) Omega_wanted = 0;  //straight
    
    
    if(timestamp>6000) Omega_wanted = 10;  //left
    if(timestamp>8000) Omega_wanted = 0;  //straight
    
    
    if(timestamp>9000) Omega_wanted = -10;  //right
    if(timestamp>11000) Omega_wanted = 0;  //straight

    if(timestamp>12000) Omega_wanted = 10;  //left
    if(timestamp>14000) Omega_wanted = 0;  //straight
      
     k_wait(sem2,0);     //wait for semaphore
     timestampMagneto = millis();

  }
}

void SpeedControl(){

  const float Wantedspeed = 1.2;
  const float SysGain = 0.49;
  float Speedtoduty;
  float Actualspeed;
  int duty;
  float tmp;
  float Error;
  const float PGain = 1.0;
  float feedFwd = Wantedspeed;
 
  while(1){
    batReading = analogRead(8); //reading battery voltage
    speed0 = getSpeed(0);       //reading speed of first belt
    speed1 = getSpeed(1);       //reading speed of the other belt
    timestamp = millis();       //getting time at which data was recorded

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
    //stop at the end
    if(timestamp<15000)speed(duty);
  
    else speed(0);    
    
  Serial.print(Actualspeed),
  Serial.print(',');
  Serial.print(batReading);
  Serial.print(' ');
  //Serial.print(timestamp);

  //Serial.println(' ');

    delay(50);
    
    }
  }

void setup() {
  k_init(3,2,0);

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
  //CompassSetup();
  Wire.begin();  
  compass = HMC5883L();  
  setupHMC5883L(); 
  // Init Hall sensors
  pinMode(35,INPUT);
  initHallTimers();

  sem2 = k_crt_sem(1,2);


  Serial.begin(9600);
  Serial.println("REBOOT");

  delay(2000);
  task1=k_crt_task(tSpeed,10,stack,300);              //hall sensors
  task2=k_crt_task(SpeedControl,12,stack2,300);   // Velocity controller
  task3=k_crt_task(SteeringControl,11,stack3,1000); // Steering controller

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
