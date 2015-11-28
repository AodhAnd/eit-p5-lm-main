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

struct k_t *sem1;
struct k_t *Test;
char stack[500];

void SDdriver(void)
{
  File myFile;
  
  while (1)
  {
    Serial.println("\nWriteBegin");
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    noInterrupts();
    k_wait(sem1,0);
      myFile = SD.open("AEST.TXT", FILE_WRITE); //In standard it is in read mode.
  
      // if the file opened okay, write to it:
      if (myFile)
      {
        Serial.println("Writing to file...");
        myFile.println("testing 1, 2, 3.");
        myFile.close();
        Serial.println("Done writing to file");
      }
      else if (myFile == 0)
      {
        // if the file didn't open the file, print an error:
        Serial.println("error opening test.txt");
      }
    k_signal(sem1);
    Serial.println("WriteEnd");
    delay(500);
  }
}



void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }

  Serial.println("REBOOT");

  Serial.println(SD.begin(53));
  k_init(1, 1, 0);
  Test = k_crt_task(SDdriver, 1, stack, 500);
  sem1 = k_crt_sem(1,120);
  Serial.println("SETUP DONE");

  k_start(10);
}


void loop()
{
  // nothing happens after setup
}


