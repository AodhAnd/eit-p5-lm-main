#include <Arduino.h>

typedef struct {
  uint8_t Destination;
  uint8_t Length;
  int16_t Xcor;
  int16_t Ycor;
  int16_t Zcor;
}Protocol;

int GetProtocol(int out[5]);
