#include <Arduino.h>
#include <Wire.h>
#include "Magnetometer.h"
void setup()
{
  Serial.begin(9600);
  CompassSetup();
}

void loop()
{
  Serial.println(CompassGet());
  delay(20);
}

