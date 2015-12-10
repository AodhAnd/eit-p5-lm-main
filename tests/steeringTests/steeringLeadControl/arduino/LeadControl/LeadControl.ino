#include "hall.h"
#include <krnl.h>
#include "motor_driver.h"
#include "myservo.h"
#include <Wire.h>
#include <HMC5883L.h>
#include "ProtocolRec.h"
#include "Route.h"


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
    {1.05, -0.064, 0.044},
    {0.065, 1.064, 0.023},
    {0.009, -0.009, 1.248}
  };
  //bias[3] is the bias
  //replace Bx, By, Bz with your bias data
  double bias[3] =
  {
    -16.375,
    -163.607,
    -150.167
  };
  //calculation
  for (int i = 0; i < 3; ++i) uncalibrated_values[i] = uncalibrated_values[i] - bias[i];
  float result[3] = {0, 0, 0};
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      result[i] += calibration_matrix[i][j] * uncalibrated_values[j];
  for (int i = 0; i < 3; ++i) calibrated_values[i] = result[i];
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

struct k_t *task1, *task2, *task3, *task4, *task5;

struct k_t *sem3; //semaphore for speed controller
struct k_t *sem2; //semaphore for Steering controller

struct k_msg_t *pMsgGoTLead,*pMsgLeadAngle; // create two message queues

char mar[10*4];
char mar2[10*4];

char stack[300];  // Stack of Hall sensor
char stack2[300]; // Stack of Speed Control
char stack3[1000]; // Stack of Steering control
char stack4[300]; // Stack of Lead Compensator
char stack5[1000]; // Stack of GoT stuff

float speed0;     // Speed of belt 1
float speed1;     // Speed of belt 2
long int timestamp;
char byte1;
char byte2;
int batReading;   // Battery voltage reading

float values_from_magnetometer[3];




void GoT()
{
    int Output[5];
    int Done;
    float Dist;
  
  while(1){
  Done = GetProtocol(Output); // wait for coordinate
  if (Done == 0)
  {
    int sX = 0;
    int sY = 0;
    int eX = 0;
    int eY = 0;
    GetStart(&sX, &sY);
    GetEnd(&eX, &eY);
    Dist = DistanceCal(sX, sY, eX, eY, Output[2], Output[3]);
    k_send(pMsgGoTLead,&Dist); 
   } 
  
  }
}




void LeadCompensator() {
  /* --------------------------  Lead compensator -------------------------- */

  // Laplace domain parameters:
  const float a = 3;              // Zero position            (a*s + 1)
  const float b = 1;              // Pole position        G * ---------
  const float LeadGain = 78.8;      // G                        (b*s + 1)

  // Z domain parameters:
  const float T = 0.1;              //sample period
  const float zA1 = 2 + (a * T);      //                    z(2 + aT) + (1 - aT)
  const float zA2 = 1 - (a * T);      //  G_c, eq[z] = G * ------------------------
  const float zB1 = 2 + (b * T);      //                    z(2 + bT) + (1 - bT)
  const float zB2 = 1 - (b * T);

  // Actual compensator:
  static float LastError;
  float currentError;
  static float LeadOutput;
  float LeadTimesGain;
  float lastoutput;
  while (1) {
    LastError = currentError;
    if (0 <= k_receive(pMsgGoTLead,&currentError,0,NULL) ) { // Wait for distance from GoT system (waits forever)
    lastoutput = LeadOutput;
    LeadOutput = ((zA1 * currentError) + (zA2 * LastError) - (zB2 * lastoutput)) / zB1;
    LeadTimesGain = LeadOutput*LeadGain;
    if (LeadTimesGain > 90) LeadTimesGain = 100;
    if (LeadTimesGain < -90) LeadTimesGain = -100;
    LeadTimesGain += (GetAngle()-22);
    k_send(pMsgLeadAngle,&LeadTimesGain);
    }
  }
}

void SteeringControl() {

  int servoPulseWidth = SERVO_MIDDLE_PW; // X seconds pulse width makes the vehicle go straight(-ish)
  float MAG_Heading_Old;                 // Heading to compare with from last run
  float MAG_Heading_New;                 // Current heading
  float MAG_Heading_Ref;                 // Reference heading
  float Omega_current;                   // Current angular velocity
  float Omega_error;                     // Error angular velocity
  float Theta_error;
  float Omega_wanted = 0;                // Wanted angular velocity
  float P_out;                           // Output from P controller

  float P_gain = 3;                      // to convert angle or speed error into ms

  const int rightOffset = -220;
  const int leftOffset = 250;

  int turningWanted = 0;

  k_set_sem_timer(sem2, 30); // krnl will signal sem every 30th tick

  /* Get initial heading */
  getHeading();
  values_from_magnetometer[0] = xv;
  values_from_magnetometer[1] = yv;
  values_from_magnetometer[2] = zv;
  transformation(values_from_magnetometer);
  MAG_Heading_Old = atan2(-calibrated_values[1], calibrated_values[0]) * (180.0 / 3.14);

  MAG_Heading_Ref = 0; //MAG_Heading_Old;        //initialize reference of the angle(first one)

  setServo(servoPulseWidth); // Initialized to the start value (SERVO_MIDDLE_PW)
  float angleBuf;
  while (1) {
    /* Check mailbox, to see if we have a new target heading */
    if (0 <= k_receive(pMsgLeadAngle,&angleBuf,-1,NULL) ) {
      MAG_Heading_Ref = angleBuf; //If we do, use it, if not, we carry on with the latest heading.
    }


    /* Get current heading */
    getHeading();
    values_from_magnetometer[0] = xv;
    values_from_magnetometer[1] = yv;
    values_from_magnetometer[2] = zv;
    transformation(values_from_magnetometer);

    MAG_Heading_New = atan2(-calibrated_values[1], calibrated_values[0]) * (180.0 / 3.14);
    


    Theta_error = MAG_Heading_New - MAG_Heading_Ref;
    if (Theta_error < 180) {
      Theta_error += 360; //if heading around +-180°
    }
    if (Theta_error > 180) {
      Theta_error -= 360;
    }



    /* P-controller */
    
    P_out = Theta_error * P_gain;

    if (P_out < 0) {
      servoPulseWidth = setServo(SERVO_MIDDLE_PW + leftOffset - P_out); //send middle PWM, plus offset to begin tunring, minus the error of angle times gain
    }
    if (P_out > 0) {
      servoPulseWidth = setServo(SERVO_MIDDLE_PW + rightOffset - P_out);
    }
    if (P_out == 0) {
      setServo(SERVO_MIDDLE_PW);
    }


    /* Print things out */
    Serial.print(millis());
    Serial.print(',');
    Serial.print(MAG_Heading_New);
    Serial.print(',');
    Serial.print(MAG_Heading_Ref);
    Serial.print(',');
    //Serial.print(Theta_error);
    //Serial.print(',');
    //Serial.print(servoPulseWidth);
    //Serial.print(',');
    Serial.println(' ');//Go back to the line


    k_wait(sem2, 0);    //wait for semaphore
  }
}

void SpeedControl() {

  const float Wantedspeed = 1;
  const float SysGain = 0.49;
  float Speedtoduty;
  float Actualspeed;
  int duty;
  float tmp;
  float Error;
  const float PGain = 1.0;
  float feedFwd = Wantedspeed;
  int batOK;
  k_set_sem_timer(sem3, 50); // krnl will signal sem every 50th tick
  while (1) {
    batReading = analogRead(8); //reading battery voltage
    if (batReading <= 584) enableMotor(0); // stop vehicle if battery voltage gets below 5,7V*102,4 = 584.
    
    speed0 = getSpeed(0);       //reading speed of first belt
    speed1 = getSpeed(1);       //reading speed of the other belt
    timestamp = millis();       //getting time at which data was recorded

    Actualspeed = (speed0 + speed1) / 2; // average speed of the vehicle

    // Vehicle starts after 2 seconds
    if (timestamp > 2000) //P-Controler with feed forward
    {
      Error = Wantedspeed - Actualspeed;
      Speedtoduty = 1.0 / (((float)batReading / 102.4) * SysGain); // Battery reading: 1024 = 10V, so 1V = 102.4. multiply that with the system gain to calculate the duty cycle.
      //duty = Speedtoduty*100.0;
      tmp = (  ((Error) * PGain + feedFwd + 0.38) * Speedtoduty) * 100.0; //actual P-Controller
      duty = tmp;
      if (duty > 100) duty = 100;
      if (duty < 0) duty = 0;
    }
    else speed(0);
    if (timestamp<8000) speed(duty);
    else speed(0);
     k_wait(sem3, 0);    //wait for semaphore;

  }
}



void setup() {
  k_init(5, 3, 2);

  pinMode(5, OUTPUT);
  initServo();

  pinMode(dPinMove1, OUTPUT);
  pinMode(dPinMove2, OUTPUT);
  pinMode(dPinOnOff, OUTPUT);

  // Set up the motor
  I2C_Init();
  Magn_Init();
  initMotor();
  enableMotor(1);
  direction(1);    //move forward

  // Set up course
   SetBothPoint(-1400,20,1820,0);
  
  // Set up the compass/gyro/accelerometer sensors
  //CompassSetup();
  Wire.begin();
  compass = HMC5883L();
  setupHMC5883L();
  // Init Hall sensors
  pinMode(35, INPUT);
  initHallTimers();
  sem3 = k_crt_sem(1, 2);
  sem2 = k_crt_sem(1, 2);

  Serial3.begin(9600);
  Serial.begin(115200);
  Serial.println("REBOOT");

  delay(2000);
  task1 = k_crt_task(tSpeed, 10, stack, 300);         //hall sensors
  task2 = k_crt_task(SpeedControl, 12, stack2, 300); // Velocity controller
  task3 = k_crt_task(SteeringControl, 11, stack3, 1000); // Steering controller
  task4 = k_crt_task(LeadCompensator, 13, stack4, 300); // Lead compensator
  task5 = k_crt_task(GoT,14,stack5,1000);          // GoT and protocol handling

  pMsgGoTLead = k_crt_send_Q(10,4,mar);     //mail box, GoT sends distance, Lead Compensator recieves it.
  pMsgLeadAngle = k_crt_send_Q(10,4,mar2);  //mail box, Lead Compensator sends angle, Angle controller recieves it.


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

