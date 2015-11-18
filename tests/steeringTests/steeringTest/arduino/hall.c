#include "hall.h"
#include <arduino.h>
volatile unsigned int uiTimeOfRotation[2]; // micro seconds for one rotation of the front(drive) wheel

void initHallTimers()
{
  uiTimeOfRotation[0] = 0xFFFF;
  uiTimeOfRotation[1] = 0xFFFF;
  pinMode(48, INPUT);
  pinMode(49, INPUT);
  // Nothing interesting to set in TCCRnA:
  TCCR4A = 0;
  TCCR5A = 0;

  // Set the OCR (timeout) to 0 allows the full TCNT range for the initial period.
  OCR4A = 0;
  OCR5A = 0;

  // Set the interrupt sense and the prescaler
  TCCR4B  = (0 << ICES4) | ((1 << CS42) | (0 << CS41) | (1 << CS40) | (1<<ICNC5)); //trigger on falling edge, prescaler = 1024 (counter clock = 15625 Hz)
  TCCR5B  = (0 << ICES5) | ((1 << CS52) | (0 << CS51) | (1 << CS50) | (1<<ICNC5)); //trigger on falling edge, prescaler = 1024 (counter clock = 15625 Hz)

  sem1 = k_crt_sem(1,2);

}

void tSpeed(void){
unsigned int uiNewTimerVal4, uiNewTimerVal5;
int i;
unsigned int uiTimer4Buffer[4], uiTimer5Buffer[4]; //used for storing clock pulse count for each magnet pass
for(i = 0;i<5;i++){
    uiTimer4Buffer[i] = 0xFFFF;
    uiTimer5Buffer[i] = 0xFFFF;
}

  k_set_sem_timer(sem1,1); // krnl will signal sem every tick
  
  while (1)
  {
    if (TIFR5 & (1 << ICF5))
    {
      uiNewTimerVal5 = ICR5;                                            //<--reading value of timer 5

      uiTimeOfRotation[0] = (uiNewTimerVal5 - uiTimer5Buffer[3] );  //<--calculating time from a magnet passes till it passes again
                                                                        //   => time of one rotation of front wheel in us
      for( i = 2; i >= 0 ; i-- )                                        //   1/(15625 Hz) = 64 us per colck tick
      {
        uiTimer5Buffer[i+1] = uiTimer5Buffer[i];                        //<--moving each timer value 1 up in the buffer to make space for the new timer value
      }
      uiTimer5Buffer[0] = uiNewTimerVal5;                               //<--new timer value stored in buffer

      TIFR5 = TIFR5 | (1<<ICF5);
    }
    
    if (TIFR4 & (1 << ICF4))
    {
      uiNewTimerVal4 = ICR4;                                            //<--reading value of timer 4

      uiTimeOfRotation[1] = (uiNewTimerVal4 - uiTimer4Buffer[3] );  //<--calculating time from a magnet passes till it passes again
                                                                        //   => time of one rotation of front wheel in us
      for( i = 2; i >= 0 ; i-- )                                        //   1/(15625 Hz) = 64 us per colck tick
      {
        uiTimer4Buffer[i+1] = uiTimer4Buffer[i];                        //<--moving each timer value 1 up in the buffer to make space for the new timer value
      }
      uiTimer4Buffer[0] = uiNewTimerVal4;                               //<--new timer value stored in buffer

      TIFR4 = TIFR4 | (1<<ICF4);
    }

    k_wait(sem1,0); 
  }
}

float getSpeed(int belt)
{
  float result = (((float)0.166) / ((float)uiTimeOfRotation[belt] *((float)0.000064)));  //<--0.166 m / front wheel rotation (us)  [m/us]  =>  * 1 000 000 = [m/s]
  return(result);
}






// 648,4375 = 0.0415 m / 64 us

// 1 clock tick = 64 us
//
// 64 us  *  uiSpeed = diffVal [us] <-> uiSpeed = diffVal / 64 us [.]
// fT = 1 / uiSpeed;           [1/. = .]
// result = fT * (648.4375);   [m/us]
//               


// diffVal = 64 us  *  uiSpeed                       [us]
// result = dist/diffVal                             [m/us]
// result = 0.0415/(uiSpeed * 64)                    [m/us]
// final result = 0.0415/(uiSpeed * 64) *1 000 000   [m/s]










