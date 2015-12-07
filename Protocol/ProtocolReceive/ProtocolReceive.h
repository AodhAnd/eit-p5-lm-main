#include <arduino.h>

typedef struct {
  uint8_t Source;
  uint8_t Type;
  int16_t Xcor;
  int16_t Ycor;
  int16_t Zcor;
}Protocol;

int GetProtocol(int out[5]);
