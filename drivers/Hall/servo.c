#include "servo.h"
#include <arduino.h>

int initServo(){									// Sets up pins and timers. Returns 0 if successful
	TCCR3B = 0; 										// Halt counter by setting clock select bits to 0 (No clock source)
	TCNT2 = 0x00;										// Start counting at bottom. 
	OCR2A = 0;											// Set TOP to 0. This effectively keeps us from counting becuase the counter just keeps reseting back to 0.
	


	TCCR3B = 2;											// Sets timer prescaler to F_CPU/8 = 2 MHz
	


}
