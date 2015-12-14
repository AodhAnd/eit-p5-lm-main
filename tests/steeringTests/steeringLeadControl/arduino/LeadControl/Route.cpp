#include "Route.h"
//#include <arduino.h>
#include <math.h>

CurrentRoute CR;

void CalAngle(int StartX, int StartY, int EndX, int EndY){
  CR.Angle = ((float)atan2((EndY - StartY),(EndX - StartX)))*(180.0/3.141592);
}

float GetAngle(){
  return CR.Angle;
}

void GetStart(int* X, int* Y){
  *X = CR.StartX;
  *Y = CR.StartY;
}

void GetEnd(int* X, int* Y){
  *X = CR.EndX;
  *Y = CR.EndY;
}

void SetNextPoint(int X, int Y){
  CR.StartX = CR.EndX;
  CR.StartY = CR.EndY;
  CR.EndX = X;
  CR.EndY = Y;
  CalAngle(CR.StartX, CR.StartY, CR.EndX, CR.EndY);
}

void SetBothPoint(int StartX, int StartY, int EndX, int EndY){
  CR.StartX = StartX;
  CR.StartY = StartY;
  CR.EndX = EndX;
  CR.EndY = EndY;
  CalAngle(CR.StartX, CR.StartY, CR.EndX, CR.EndY);
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

float ToEndPoint(int Actx, int Acty, int EndX, int EndY){
 return (float)sqrt(pow((EndX - Actx),2) + pow((EndY - Acty),2));
}



