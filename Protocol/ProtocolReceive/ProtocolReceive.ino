#include "ProtocolRec.h"
#include "Route.h"
#include <Math.h>

float Dist = 0;
int sX = 0;
int sY = 0;
int eX = 0;
int eY = 0;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  SetBothPoint(0,0,3000,0);
}

void loop() {

  int Output[5];
  int Done = GetProtocol(Output);
  
  
  if (Done == 0)
  {
    Serial.print(millis());
    if (eX == 3000)
      {
        Serial.print("a");
      }
    else if (eY == 3000)
      {
        Serial.print("b");
      }
    else
      {
        Serial.print("c");
      }

    GetStart(&sX, &sY);
    GetEnd(&eX, &eY);
    Dist = DistanceCal(sX, sY, eX, eY, Output[2], Output[3]);
    Serial.print(" X ");
    Serial.print(Output[2]);
    Serial.print(" Y ");
    Serial.print(Output[3]);
    Serial.print(" To goal ");
    Serial.println(ToEndPoint(Output[2], Output[3], eX, eY));
    if (ToEndPoint(Output[2], Output[3], eX, eY) < 250)
    {
      if (eX == 3000)
      {
        SetNextPoint(0,3000);
      }
      else if (eY == 3000)
      {
        SetNextPoint(0,0);
      }
      else
      {
        SetNextPoint(3000,0);
      }
    }    
  }  
}

