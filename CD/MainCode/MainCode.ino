#include <Wire.h>

#include <krnl.h>
#include <HMC5883L.h>

#include "hall.h"
#include "motor_driver.h"
#include "myservo.h"
#include "ProtocolRec.h"
#include "Route.h"



/* BEGIN -  Declaration of the global variables */
struct k_t *task1, *task2, *task3, *task4, *task5;

struct k_t *sem3; //semaphore for speed controller
struct k_t *sem2; //semaphore for Steering controller

struct k_msg_t *pMsgGoTLead,*pMsgLeadAngle; // create two message queues

char mar[10*4];
char mar2[10*4];

char stack[300];    // Stack of Hall sensor
char stack2[300];   // Stack of Speed Control
char stack3[1000];  // Stack of Steering control
char stack4[300];   // Stack of Lead Compensator
char stack5[1000];  // Stack of GoT stuff

float speed0;       // Speed of belt 1
float speed1;       // Speed of belt 2
long int timestamp; // Time of the system
char byte1;
char byte2;
int batReading;     // Battery voltage reading

/* END - Declaration of the global variables */









/* BEGIN - Magnetometer functions */
HMC5883L compass; //Copy the folder "HMC5883L" in the folder "C:\Program Files\Arduino\libraries" and restart the arduino IDE.

float xv, yv, zv;
float values_from_magnetometer[3];


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
/* End Of Magnetometer functions */











/* BEGIN - Task 3: GoT System and communication protocol */
void GoT()
{
    int Output[5];
    int Done;
    float Dist;
  
  while(1){
  Done = GetProtocol(Output); // wait for coordinate
  
   //digitalWrite(31, HIGH);
  if (Done == 0)
  {
    int sX = 0;
    int sY = 0;
    int eX = 0;
    int eY = 0;
    GetStart(&sX, &sY);
    GetEnd(&eX, &eY);
    if (ToEndPoint(Output[2], Output[3], eX, eY) < 250)
    {
      if (eX == 2000)
      {
        SetNextPoint(0,2000);
      }
      else if (eY == 2000)
      {
        SetNextPoint(0,0);
      }
      else
      {
        SetNextPoint(2000,0);
      }      
    }
    Dist = DistanceCal(sX, sY, eX, eY, Output[2], Output[3]);
    /*Serial.print(Output[2]);
    Serial.print(',');
    Serial.print(Output[3]);
    Serial.print(',');
    Serial.print(Dist);
    Serial.println(',');*/
    //digitalWrite(31, LOW);
    k_send(pMsgGoTLead,&Dist); 
   }
  }
}
/* END - Task 3: GoT System and communication protocol */








/* BEGIN - Task 4: Distance Controller with lead compensator */
void LeadCompensator() {
    /* --------------------------  Lead compensator -------------------------- */

  // Laplace domain parameters:
  const float a = 1;              // Zero position            (a*s + 1)
  const float b = 0.3;              // Pole position        G * ---------
  const float LeadGain = 95;      // G                        (b*s + 1)

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
  while (1) 
  {
    LastError = currentError;
    if (0 <= k_receive(pMsgGoTLead,&currentError,0,NULL) ) 
    { // Wait for distance from GoT system (waits forever)
        digitalWrite(31, HIGH);

      lastoutput = LeadOutput;
      LeadOutput = ((zA1 * currentError) + (zA2 * LastError) - (zB2 * lastoutput)) / zB1;
      LeadTimesGain = LeadOutput*LeadGain;
      if (LeadTimesGain > 90) LeadTimesGain = 90;
      if (LeadTimesGain < -90) LeadTimesGain = -90;
      LeadTimesGain += (GetAngle());
      //Serial.println(LeadTimesGain);
          digitalWrite(31, LOW);

      k_send(pMsgLeadAngle,&LeadTimesGain);
    }
  }
}
/* END - Task 4: Distance Controller with lead compensator */








/* BEGIN - Task 5: Angular Controller with Magnetometer Sensor */
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


    k_wait(sem2, 0);    //wait for semaphore
  }
}
/* END - Task 5: Angular Controller with Magnetometer Sensor */









/* BEGIN - Task 2: Speed Control with PI Controller */
void SpeedControl() {

  const float Wantedspeed = 1.4;
  float Actualspeed;
  float Error;
  float Integral = 0;
  float ControllerOutput;
  float DutyPrSpeed;
  float Duty = 0;
  const float Stiction = 1.1; // 0.38/0.486   [V]  .. that is:  stiction [m*s^-1] / SysGain [s*m^-1 *V]
  const float SysGain = 0.486;
  const float Kp = 2.0576; //.8;      // Tuned parameters: Kp = .8 and Ki = 6
  const float Ki = 9.7517; //6;       // For time constant equal to that of the plant Kp = 2.0576 and Ki = 9.7517
                                      // however, the rise is too fast for the battery, which drops voltage fast at big currnets,
                                      // so Kp and Ki are recalculated for half the time-constant of the plant
                                      // to allow for a longer rise-time and thus less drop in the battery voltage
                                     
  k_set_sem_timer(sem3, 10); // krnl will signal sem every 10th tick (1 tick set to 1 ms) = 10 ms
  
  
  
  while (1)
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
        Integral = Integral + (Error*0.010); //Delta t = 0.010 s = sample time i.e. 10 ms
      //}
                                                                                                                   //-------------IN THE CODE--------------------------------------------------------------
      ControllerOutput = ((Kp * Error) + (Ki * Integral) + Stiction);                                              // dutyNeeded = controllOut * 100 /( batVolt * SysGain )
      DutyPrSpeed = 100.0/((float)batReading/102.4); // Duty cycle pr volt (% pr V) (divided by 102.4 = volts)     // 
      Duty = ControllerOutput * DutyPrSpeed; // ------------------------------------------------------------------LINK TO MODEL------------------------------------------------------------------
      if(Duty > 100) Duty = 100;             // controllerOut = VoltNeeded --> plant --> m/s
      if(Duty < 0) Duty = 0;                 // batVolt/100 = [volt/duty] => ( batVolt/100 ) *dutyNeeded = VoltNeeded <=> dutyNeeded =   VoltNeeded        / ( batVolt/100 )
    }                                        //                                                                       <=> dutyNeeded =   controllOut       / ( batVolt/100 )
                                             //                                                                       <=> dutyNeeded =   (controllOut*100) /  batVolt

    //DutyPrSpeed = 100.0/((float)batReading/102.4);  //<
    //Duty =  Stiction * DutyPrSpeed;                 //<< For testing stiction
    //speed(Duty);                                    //<
    
    
    /* Code to do */
    if(timestamp > 2000 && timestamp <= 5000) speed(20);
    if(timestamp > 5000 && timestamp <= 15000) speed(Duty);
    if(timestamp > 15000) speed(0);
    
    k_wait(sem3, 0);    //wait for semaphore;
  }
}
/* END - Task 2: Speed Control with PI Controller */






void setup() {
  k_init(5, 3, 2);

  pinMode(5, OUTPUT);
  pinMode(31, OUTPUT); 
  initServo();

  pinMode(dPinMove1, OUTPUT);
  pinMode(dPinMove2, OUTPUT);
  pinMode(dPinOnOff, OUTPUT);

  // Set up the Magnetometer
  I2C_Init();
  Magn_Init();
  initMotor();
  enableMotor(1);
  direction(1);    //move forward

  // Set up course
   SetBothPoint(0,0,2000,0);
 
  Wire.begin();
  compass = HMC5883L();
  setupHMC5883L();
  // Init Hall sensors
  pinMode(35, INPUT);
  initHallTimers();
  sem3 = k_crt_sem(1, 2);
  sem2 = k_crt_sem(1, 2);

  Serial3.begin(9600);
  Serial.begin(230400);
  Serial.println("REBOOT");

  delay(2000);
  task1 = k_crt_task(tSpeed, 11, stack, 300);         	   // Hall Sensors
  task2 = k_crt_task(SpeedControl, 12, stack2, 300); 	   // Velocity controller
  task3 = k_crt_task(GoT,14,stack5,1000);                  // GoT and protocol handling
  task4 = k_crt_task(LeadCompensator, 13, stack4, 300);    // Distance Controller
  task5 = k_crt_task(SteeringControl, 10, stack3, 1000);   // Angular controller

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

