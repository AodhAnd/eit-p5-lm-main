#include "SDcard_driver.h"

File myFile;

void SDinit()
{
  bool beginSDval;
  Serial.println("Initializing SD card...");
  
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  //pinMode(53, OUTPUT);
  beginSDval = SD.begin(53);
  if (!beginSDval)
  {
    Serial.println("initialization failed!");
    return;
  }
  else if (beginSDval)
  {
    Serial.println("initialization done.");
  }



  
}

void SDWrite()
{
  Serial.println("\nWriteBegin");
  delay(500);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE); //In standard it is in read mode.
  delay(1000);
  
  // if the file opened okay, write to it:
  if (myFile)
  {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
	  // close the file:
    myFile.close();
    Serial.println("done.");
  }
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  Serial.println("WriteEnd");
}

void SDread()
{
  Serial.println("\nReadBegin");
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read()); //write in the terminal what you read
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  Serial.println("ReadEnd");
}

