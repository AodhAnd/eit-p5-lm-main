#include <krnl.h>
#include "motor_driver.h"

struct k_t *Test;
char stack[200];

void motorDriver(void)
{
  while(1)
  {
    int test1;
    delay(100);
    test1 = test(0);
    Serial.println(test1);
  }
}

void setup()
{
Serial.begin(9600);
k_init(1,0,0);

Test = k_crt_task(motorDriver, 1, stack, 200);

k_start(1);
}

void loop(){}
