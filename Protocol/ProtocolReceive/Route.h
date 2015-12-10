#include <arduino.h>

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
