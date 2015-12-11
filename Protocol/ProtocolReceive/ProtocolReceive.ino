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
   
  Serial.println(Done);   
}

