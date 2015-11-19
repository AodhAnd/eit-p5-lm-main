/*
  SD card read/write
 
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 	 
 */
#include <krnl.h> 
#include <SD.h>
#include <SPI.h>
#include "SDcard_driver.h"


struct k_t *Test;
char stack[200];


void SDdriver(void)
{
  while(1)
  {
    SDWrite();
    SDread();
      delay(1000);

  }
}



void setup()
{
Serial.begin(9600);
SDinit();
k_init(1,0,0);

Test = k_crt_task(SDdriver, 1, stack, 200);

k_start(1);
}


void loop()
{
	// nothing happens after setup
}


