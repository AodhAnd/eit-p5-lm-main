#include <Arduino.h>

typedef struct {
  int StartX;
  int StartY;
  int EndX;
  int EndY;
  float Angle;
}CurrentRoute;

float GetAngle();
void GetStart(int* X, int* Y);
void GetEnd(int* X, int* Y);
void SetNextPoint(int X, int Y);
void SetBothPoint(int StartX, int StartY, int EndX, int EndY);
float DistanceCal(int Point1x, int Point1y, int Point2x, int Point2y, int Actx, int Acty);
float ToEndPoint(int Actx, int Acty, int EndX, int EndY);
