#include "ProtocolRec.h"
#include "Route.h"
#include <Math.h>

float Dist = 0;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  SetBothPoint(0,0,1000,0);
}

void loop() {

  int Output[5];
  int Done = GetProtocol(Output);

  
  
  if (Done == 0)
  {
    int sX = 0;
    int sY = 0;
    int eX = 0;
    int eY = 0;
    GetStart(&sX, &sY);
    GetEnd(&eX, &eY);
    Dist = DistanceCal(sX, sY, eX, eY, Output[2], Output[3]);
  }  
}

float DistanceCal(int Point1x, int Point1y, int Point2x, int Point2y, int Actx, int Acty) {

  float p1x = Point1x / 1000.0; 
  float p1y = Point1y / 1000.0;
  float p2x = Point2x / 1000.0;
  float p2y = Point2y / 1000.0;
  float acx = Actx / 1000.0;
  float acy = Acty / 1000.0;
  
  float temp1 = ((p2y -p1y) * acx) - ((p2x -p1x) * acy) + (p2x * p1y) - (p2y * p1x);
  float temp2 = (float)sqrt(pow((p2y - p1y),2) + pow((p2x - p1x),2));

  return temp1/temp2;
}

