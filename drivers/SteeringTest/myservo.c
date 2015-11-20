#include "myservo.h"
#include <arduino.h>
int initServo(void){							// Sets up pins and timers. Returns 0 if successful

	TCCR3A = 0;
	TCCR3B = 0; 										// Halt counter by setting clock select bits to 0 (No clock source)
	TCNT3 = 0x00;										// Start counting the timer. 
  
// make the counter reset at 30ms (PWM)

  ICR3 = 60000;                   //


  OCR3A = 1450<<1;                  //To set the center pulsewidth, we want 1400 us and timerperiode is 0.5 us
  TCCR3A |= (1<<COM3A1) | (1<<WGM31) | (0<<WGM30);
  TCCR3B |= (1<<CS31)| (1<<WGM33) | (1<<WGM32);  											// Sets timer prescaler to F_CPU/8 = 2 MHz - makes the time timer count at 2 MHz (has to be a number which divides into 30ms)


}

int setServo(int pulsewidth){
  if(pulsewidth>=SERVO_MAX_WIDTH) pulsewidth = SERVO_MAX_WIDTH;
  if(pulsewidth<=SERVO_MIN_WIDTH) pulsewidth = SERVO_MIN_WIDTH;
  
  OCR3A = (pulsewidth<<1);
    
}

