#include "ProtocolReceive.h"
#include <arduino.h>

Protocol decript;

void T88XposCal(uint8_t Data[10]) //X coordinate for type 88
{
  uint8_t Tempx =  Data[4] << 2; //Get the coordinate from the data array
  uint16_t TempX2 = Tempx;
  TempX2 = TempX2 << 6;
  TempX2 += Data[3];
  TempX2 = TempX2 << 1;
  TempX2 += (Data[2] >> 7);
  if (TempX2 > 16384) //If the sign bit is equal to 1, subtract the sign bit and multiply the rest by minus one
  {
    decript.Xcor = (TempX2 - 16384) * -1;
  }
  else
  {
    decript.Xcor = TempX2;
  }
}

void T88YposCal(uint8_t Data[10]) //Y coordinate for type 88
{
  uint8_t Tempy =  Data[6] << 3; //Get the coordinate from the data array
  uint16_t TempY2 = Tempy;
  TempY2 = TempY2 << 5;
  TempY2 += Data[5];
  TempY2 = TempY2 << 2;
  TempY2 += (Data[4] >> 6);
  if (TempY2 > 16384) //If the sign bit is equal to 1, subtract the sign bit and multiply the rest by minus one
  {
    decript.Ycor = (TempY2 - 16384) * -1;
  }
  else
  {
    decript.Ycor = TempY2;
  }
}

void T88ZposCal(uint8_t Data[10]) //Z coordinate for type 88
{
  uint8_t Tempz =  Data[8] << 4; //Get the coordinate from the data array
  uint16_t TempZ2 = Tempz;
  TempZ2 = TempZ2 << 4;
  TempZ2 += Data[7];
  TempZ2 = TempZ2 << 3;
  TempZ2 += (Data[6] >> 5);
  if (TempZ2 > 16384) //If the sign bit is equal to 1, subtract the sign bit and multiply the rest by minus one
  {
    decript.Zcor = (TempZ2 - 16384) * -1;
  }
  else
  {
    decript.Zcor = TempZ2;
  }
}

int T88ChecksumCheck(uint8_t Data[10]) //Checksum calculation for type 88
{
  uint8_t Tempcf = Data[2] << 4; //Put the first 20 bit into TempC1
  uint32_t TempC1 = Tempcf;
  TempC1 = TempC1 << 4;
  TempC1 += Data[1];
  TempC1 = TempC1 << 8;
  TempC1 += Data[0];

  uint32_t TempC2 = Data[4]; //Put the next 20 bit into TempC2
  TempC2 = TempC2 << 8;
  TempC2 += Data[3];
  TempC2 = TempC2 << 4;
  TempC2 += (Data[2] >> 4);

  uint8_t Tempct = (Data[7] << 4); //Put the next 20 bit into TempC3
  uint32_t TempC3 = Tempct;
  TempC3 = TempC3 << 4;
  TempC3 += Data[6];
  TempC3 = TempC3 << 8;
  TempC3 += Data[5];

  uint32_t TempCS = Data[9]; //Put the last 20 bit into TempCS
  TempCS = TempCS << 8;
  TempCS += Data[8];
  TempCS = TempCS << 4;
  TempCS += (Data[7] >> 4);

  uint32_t TempC = TempC1 + TempC2 + TempC3 + TempCS; //Add the four bit sections together 

  while(TempC > 1048575) //If there are any carries above the 20th bit, these are added to the first 20 bits again.
  {
    uint32_t TempAdd = TempC >> 20;
    uint32_t TempRest = TempC & 1048575;
    TempC = TempAdd + TempRest;
  }

  if (TempC == 1048575) //If the 20 bit is not all equal to 1, return error 4
  {
    return 0;
  }
  return 4;
}




int GetProtocol(int out[5])
{
  int iTemp = -1;

  //Header
  while(iTemp == -1) //Searching for the next byte
  {
    if (Serial.available() > 0)
    {
      iTemp = Serial.read();
    }
  }
  
  if(iTemp != 240) //If the Header is not equal to 129, return error 1
  {
    return 1;
  }
  iTemp = -1;

  //Source
  while(iTemp == -1) //Searching for the next byte
  {
    if (Serial.available() > 0)
    {
      iTemp = Serial.read();
    }
  }
  
  if(iTemp != 128) //If the Source is not equal to 128, the data is not send from the compurter, return error 2
  {
    return 2;
  }
  decript.Source = iTemp;
  iTemp = -1;

  //Type
  while(iTemp == -1) //Searching for the next byte
  {
    if (Serial.available() > 0)
    {
      iTemp = Serial.read();
    }
  }
  
  decript.Type = iTemp; //Get the type
  decript.Type = decript.Type & 127; //As the type only is 7 bit long, the last bit is set to zero.

  int lengthofarray = 0;
  int trailer = 0;

  if(decript.Type = 96) //If the type is 88, the length of the package and the trailer value is set.
  {
    lengthofarray = 10;
    trailer = 15;
  }
  else //If the type is not the type 88, the package don't have the right type, return error 3
  {
    return 3;
  }

  //Get rest of the package
  uint8_t Data[lengthofarray]; //The array to keep the data in
  Data[0] = decript.Source; //As the Header is only used to find the start, the first byte in the data array is the source
  Data[1] = iTemp; //The type and the first bit from the x coordinate is the second byte

  int BytesRead = 2;
  while(BytesRead < lengthofarray)
  {
    if(Serial.available() < 0)
    {
      iTemp = Serial.read();
      Data[BytesRead] = iTemp;
      BytesRead++;
    }
  }
  iTemp = -1;

  //Trailer
  while(iTemp == -1) //Searching for the next byte
  {
    if (Serial.available() > 0)
    {
      iTemp = Serial.read();
    }
  }

  if(iTemp != trailer) //If the byte is not equal to the trailer value from the type settings, return error 5;
  {
    return 5;
  }

  //Checksum
  if(decript.Type = 96) //Set the calculation for the checksum to the specific type
  {
    iTemp = T88ChecksumCheck(Data);
  }

  if(iTemp != 0) //If the error return from the checksum calculation, return error from the calculation
  {
    return iTemp;
  }


  //All error handeling have been done and the coordinates can now be read

  
  //Get Data
  if(decript.Type = 96) //Get the data, from the know setup of type 88
  {
    T88XposCal(Data);
    T88YposCal(Data);
    T88ZposCal(Data);
  }

  //Output Data
  if(decript.Type = 96) //Set the data, from the know setup of type 88
  {
    out[0] = decript.Source;
    out[1] = decript.Type;
    out[2] = decript.Xcor;
    out[3] = decript.Ycor;
    out[4] = decript.Zcor;
  }

  //Cleanup
  if(decript.Type = 96) //Reset the whole decript struct
  {
    decript.Source = 0;
    decript.Type = 0;
    decript.Xcor = 0;
    decript.Ycor = 0;
    decript.Zcor = 0;
  } 
  
}

