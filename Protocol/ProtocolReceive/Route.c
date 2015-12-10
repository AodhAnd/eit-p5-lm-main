#include "Route.h"
#include <arduino.h>
#include <Math.h>

CurrentRoute CR;

float GetAngle(){
  return CR.Angle;
}

void GetStart(int* X, int* Y){
  X = CR.StartX;
  Y = CR.StartY;
}

void GetEnd(int* X, int* Y){
  X = CR.EndX;
  Y = CR.EndY;
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

void CalAngle(int StartX, int StartY, int EndX, int EndY){
  CR.Angle = (float)atan2((EndY - StartY),(EndX - StartX));
}

