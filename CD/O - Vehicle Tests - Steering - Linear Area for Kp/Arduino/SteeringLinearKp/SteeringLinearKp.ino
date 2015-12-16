#include "hall.h"
#include <krnl.h>
#include "motor_driver.h"
#include "myservo.h"
#include <Wire.h>
#include <HMC5883L.h>
#include <math.h>


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

// This is the value to change the steering angle
// (servo pulse-width)
//#define SERVO_PW 1650

struct k_t *task1, *task2, *task3;

struct k_t *sem2; //semaphore for Steering controller

char stack[300];  // Stack of Hall sensor
char stack2[300]; // Stack of Speed Control
char stack3[1000]; // Stack of Steering control
float speed0;     // Speed of belt 1
float speed1;     // Speed of belt 2
long int timestamp;
char byte1;
char byte2;
int batReading;   // Battery voltage reading

float values_from_magnetometer[3];

float angles[8];

void SteeringControl(){
   
   int servoPulseWidth = SERVO_MIDDLE_PW; // X seconds pulse width makes the vehicle go straight(-ish)
   float MAG_Heading_Old;                 // Heading to compare with from last run
   float MAG_Heading_New;                 // Current heading
   float MAG_Heading_Ref;                 // Reference heading
   float Theta_error;                     // Error between new and old heading
   float P_out;                           // Error in time(ms) after multiplied by the P_gain (Kp)

   float P_gain = 1.5;                  // to convert angle error into distance error

   const int rightOffset = -220;          // to begin turning direclty
   const int leftOffset = 250;
      
   k_set_sem_timer(sem2,15); // krnl will signal sem every 50th tick
   
/* Get initial heading */   
  getHeading();                          //get the values from magnetometer
  values_from_magnetometer[0] = xv;
  values_from_magnetometer[1] = yv;
  values_from_magnetometer[2] = zv;
  transformation(values_from_magnetometer);      //shift the values to fit the model, centered in the center of the coordinate system
  MAG_Heading_Old = atan2(-calibrated_values[1], calibrated_values[0])*(180.0/3.14);      //convert the values into an angle
  
  MAG_Heading_Ref = 0; //MAG_Heading_Old;        //initialize reference of the angle to follow at beginning

  setServo(servoPulseWidth); // Initialized to the start value (SERVO_MIDDLE_PW)
    
  while(1){
  
    /* Get current heading */  
    getHeading();                  //get the values from magnetometer
    values_from_magnetometer[0] = xv;
    values_from_magnetometer[1] = yv;
    values_from_magnetometer[2] = zv;
    transformation(values_from_magnetometer);          //shift the values to fit the model, centered in the center of the coordinate system
    
    MAG_Heading_New = atan2(-calibrated_values[1], calibrated_values[0])*(180.0/3.14);      //convert the values into an angle
    
    
    /* calculate new duty to send to the servo */
    Theta_error = MAG_Heading_New - MAG_Heading_Ref;              //difference between what's happening and what we want
    if (Theta_error < 180){Theta_error +=360;}                    //if heading around +-180°, to have values from -
    if (Theta_error > 180){Theta_error -=360;}
  
    P_out = Theta_error * P_gain;                                 //multiply by the gain to get a distance of error
    
    if(P_out<0) servoPulseWidth = SERVO_MIDDLE_PW + leftOffset;   //set middle PWM, plus offset to begin turning (loose in the middle)
    if(P_out>0) servoPulseWidth = SERVO_MIDDLE_PW + rightOffset;
    if(P_out==0)setServo(SERVO_MIDDLE_PW);
    
    servoPulseWidth += P_out;       // add the error converted into time in ms
    setServo(servoPulseWidth);                                   // send the PWMto the servo
  
  
    /* Main code for the steering */
    //stepresponse after 3 sec
    if(millis()>=5000) MAG_Heading_Ref = 45;


    /* Printing for the steering */    
    Serial.print(millis());
    Serial.print(',');
    Serial.print(MAG_Heading_New);
    Serial.println(',');    
      
    k_wait(sem2,0);     //wait for semaphore
  }
}

void SpeedControl(){

  const float Wantedspeed = 1.4;
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
      tmp = (  ((Error)*PGain+feedFwd+0.38)*Speedtoduty)*100.0;//actual P-Controller
      duty=tmp;
      if(duty > 100) duty = 100;
      if(duty < 0) duty = 0;
    }
    //stop at the end
    if(timestamp<10000)speed(duty);
  
    else speed(0);    

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
  I2C_Init();
  initMotor();
  enableMotor(1);
  direction(1);    //move forward
  
  // Set up the compass/gyro/accelerometer sensors
  //CompassSetup();
  Magn_Init();
  Wire.begin();  
  compass = HMC5883L();  
  setupHMC5883L(); 
  // Init Hall sensors
  pinMode(35,INPUT);
  initHallTimers();

  sem2 = k_crt_sem(1,2);


  Serial.begin(115200);
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
