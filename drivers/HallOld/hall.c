#include "hall.h"
#include <arduino.h>
volatile unsigned int uiSpeed[2]; // Number of counter clocks between pulses

void initHallTimers()
{
  uiSpeed[0] = 0xFFFF;
  uiSpeed[1] = 0xFFFF;
  pinMode(48, INPUT);
  pinMode(49, INPUT);
  // Nothing interesting to set in TCCRnA:
  TCCR4A = 0;
  TCCR5A = 0;

  // Set the OCR (timeout) to 0 allows the full TCNT range for the initial period.
  OCR4A = 0;
  OCR5A = 0;

  // Set the interrupt sense and the prescaler
  TCCR4B  = (0 << ICES4) | ((1 << CS42) | (0 << CS41) | (1 << CS40)); //trigger on falling edge, prescaler = 1024 (counter clock = 15625 Hz)
  TCCR5B  = (0 << ICES5) | ((1 << CS52) | (0 << CS51) | (1 << CS50)); //trigger on falling edge, prescaler = 1024 (counter clock = 15625 Hz)

  sem1 = k_crt_sem(1,2);

}

void tSpeed(void){
unsigned int uiOld4,uiOld5,uiNew4, uiNew5;  
   k_set_sem_timer(sem1,1); // krnl will signal sem every tick
  
  while (1) {
    if (TIFR5 & (1 << ICF5)) {
       uiNew5 = ICR5;
       uiSpeed[1] = (uiNew5-uiOld5);
       uiOld5=uiNew5;
       TIFR5 = TIFR5 | (1<<ICF5);
    }
    if (TIFR4 & (1 << ICF4)) {
       uiNew4 = ICR4;
       uiSpeed[0] = (uiNew4-uiOld4);
       uiOld4=uiNew4;
       TIFR4 = TIFR4 | (1<<ICF4);
    }
    
    k_wait(sem1,0); 
}
}

float getSpeed(int belt) {
  float fT=(float)1/(float)uiSpeed[belt];
  float result = fT * (648.4375);
  return(result); // 648,4375 = 0.0415 m / 64 us
}
