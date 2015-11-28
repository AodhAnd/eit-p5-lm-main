#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#define MOTOR_TIMER_PRESCALE 8              // Prescaler value for timer
#define MOTOR_TIMER_CLOCK F_CPU/MOTOR_TIMER_PRESCALE  // Clock speed (16 MHz) in Hz for timer controlling the servo
#define MOTOR_TIMER_PERIOD 1000000/MOTOR_TIMER_CLOCK  // Time in microseconds per timer tick 

#ifdef __cplusplus
extern "C"{
#endif




#define dPinMove1 2
#define dPinMove2 7
#define dPinOnOff 6

#define dPinCurrent1 0
#define dPinCurrent2 1

int initMotor();         // Initializes the motor timer
int speed(int iSpeed);    //tells to the motot the speed it should have
int direction(int iDir);   //tells to the motor the direction it should have
int motorCurrent();      //asks the current in the motor
int enableMotor(int iOnOff);
int test(int iTest);


#ifdef __cplusplus
} // extern "C"
#endif

#endif
