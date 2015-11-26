
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

  const float Wantedspeed = 1.6;
  const float SysGain = 0.49;
  float Speedtoduty;
  int servoPulseWidth = SERVO_MIDDLE_PW; // X seconds pulse width makes the vehicle go straight(-ish)
  float Actualspeed;
  int duty;
  float tmp;
  float Error;
  const float PGain = 1.0;
  float feedFwd = Wantedspeed;
  float CompassReading[4];
  
  float compassAverage;
  int compasscnt = 0;
  int i;
  int bou = 1;
  int count = 0;
  
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
    if(timestamp>8000) servoPulseWidth = 1600;  //left
    //if(timestamp>6500) servoPulseWidth = 1150;  //straight
    
    /*
    if(timestamp>8000) servoPulseWidth = 1070;  //right
    if(timestamp>9500) servoPulseWidth = 1150;  //straight
    
    
    if(timestamp>11000) servoPulseWidth = 1600;  //left
    if(timestamp>12500) servoPulseWidth = 1150;  //straight
    
    
    if(timestamp>14000) servoPulseWidth = 1070;  //right
    if(timestamp>15500) servoPulseWidth = 1150;  //straight

    if(timestamp>17000) servoPulseWidth = 1600;  //left
    if(timestamp>18500) servoPulseWidth = 1150;  //straight
    */
    //stop at the end
    if(timestamp<10000)speed(duty);
  
    else speed(0);    
    
    /*count++;
   if(count == 25)
   {
     if(bou == 1) 
     {
       speed(50);      //set the speed
       bou = 0;
     }
     else
     {
       speed(0);
       bou = 1;
     }
     count= 0;
   }
*/
//speed(50);
    
    float values_from_magnetometer[3];
  
  getHeading();
  values_from_magnetometer[0] = xv;
  values_from_magnetometer[1] = yv;
  values_from_magnetometer[2] = zv;
  transformation(values_from_magnetometer);

  //Serial.flush(); 
  
  float MAG_Heading = atan2(-calibrated_values[1], calibrated_values[0])*(180.0/3.14);
  Serial.print(MAG_Heading);
  Serial.print(',');
  
  Serial.print(calibrated_values[0]);
  Serial.print(',');

  Serial.print(calibrated_values[1]);
  Serial.print(',');

  Serial.print(calibrated_values[2]);
  Serial.print(',');
  
  Serial.print(timestamp);

  Serial.println(' ');

  
  
    
    
    //filtering of the angle data, rolling average of 5
    /*CompassReading[compasscnt] = CompassGet();
    compasscnt++;
    if (compasscnt == 4) compasscnt = 0;
    compassAverage = 0;
    for (i=0;i<4;i++){compassAverage += CompassReading[i];}
    compassAverage = compassAverage/4;*/
      
   
    //printing out the data whith commas for easy export as .csv-file:
    //Serial.print(compassAverage);
    //Serial.print(CompassGet());
    //Serial.print(",");
    /*Serial.print((float)batReading/102.4);    //voltage
    Serial.print(",");
    Serial.print(Actualspeed);
    Serial.print(",");
    Serial.print(timestamp);
    Serial.print("\n");
    Serial.print("\r");      */ //carriage return to return the curser for each new line
    delay(100);
    
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
  //CompassSetup();
  Wire.begin();  
  compass = HMC5883L();  
  setupHMC5883L(); 
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
