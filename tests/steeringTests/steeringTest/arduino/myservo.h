#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H
#define SERVO_MIN_WIDTH 500								// Minimum pulsewidth for servo
#define SERVO_MAX_WIDTH 2000							// Maximum pulsewidth for servo
#define SERVO_TIMER_PRESCALE 8							// Prescaler value for timer
#define SERVO_TIMER_CLOCK F_CPU/SERVO_TIMER_PRESCALE	// Clock speed (16 MHz) in Hz for timer controlling the servo
#define SERVO_TIMER_PERIOD 1000000/SERVO_TIMER_CLOCK	// Time in microseconds per timer tick 

#ifdef __cplusplus
extern "C"{
#endif


int initServo(void);									// Sets up pins and timers. Returns 0 if successful
int setServo(int pulsewidth);							// Sets new pulsewidth to timer. Returns 0 if successful

#ifdef __cplusplus
} // extern "C"
#endif

#endif
