#include <Arduino.h>
#include <Wire.h>
#include "Magnetometer.h"
float magnetom[3];

void compensate_sensor_errors() ;
void CompassSetup();
double CompassGet();
double output_sensors();
void I2C_Init();
void Magn_Init();
void Read_Magn();

void compensate_sensor_errors() 
{
  int r;
  Serial.print(magnetom[0]);
  Serial.print(",");

  //magnetom[0] = (magnetom[0] - MAGN_X_OFFSET) * MAGN_X_SCALE;
  magnetom[0] = magnetom[0] + 110;
  Serial.print(magnetom[0]);
  Serial.print(",");



  Serial.print(magnetom[1]  );
  Serial.print(",");
  //magnetom[1] = (magnetom[1] - MAGN_Y_OFFSET) * MAGN_Y_SCALE;
  magnetom[1] = magnetom[1] -134;

  Serial.print(magnetom[1]  );
  Serial.print(",");
  
  
  
  
  Serial.print(magnetom[2]  );
  Serial.print(",");
  //magnetom[2] = (magnetom[2] - MAGN_Z_OFFSET) * MAGN_Z_SCALE;
  magnetom[2] = magnetom[2] +18;
  Serial.print(magnetom[2]  );
  Serial.print(",");
  
  
  //r = sqrt(pow(magnetom[0],2)+pow(magnetom[1],2)+pow(magnetom[2],2));
  //Serial.print(r);
  Serial.print("\n\r");
}

void CompassSetup()
{  
  // Init sensors
  delay(50);  // Give sensors enough time to start
  I2C_Init();
  Magn_Init();
  
  // Read sensors, init DCM algorithm
  delay(20);  // Give sensors enough time to collect data
  Read_Magn();
}

double CompassGet()
{
    Read_Magn();    
    double angle = output_sensors();
    return angle;
}

double output_sensors()
{
  compensate_sensor_errors();
  double CompassAngle = 180*(acos(-magnetom[0]/sqrt(pow(magnetom[0],2)+pow(magnetom[1],2)))/3.14);
  if (magnetom[1] < 0.0)
  {
    CompassAngle = CompassAngle * -1;
  }
  
  return CompassAngle;
}

// Arduino backward compatibility macros
#if ARDUINO >= 100
  #define WIRE_SEND(b) Wire.write((byte) b) 
  #define WIRE_RECEIVE() Wire.read() 
#else
  #define WIRE_SEND(b) Wire.send(b)
  #define WIRE_RECEIVE() Wire.receive() 
#endif


void I2C_Init()
{
  Wire.begin();
}

void Magn_Init()
{
  Wire.beginTransmission(MAGN_ADDRESS);
  WIRE_SEND(0x02); 
  WIRE_SEND(0x00);  // Set continuous mode (default 10Hz)
  Wire.endTransmission();
  delay(5);

  Wire.beginTransmission(MAGN_ADDRESS);
  WIRE_SEND(0x00);
  WIRE_SEND(0b00011000);  // Set 50Hz
  Wire.endTransmission();
  delay(5);
}

void Read_Magn()
{
  int i = 0;
  byte buff[6];
 
  Wire.beginTransmission(MAGN_ADDRESS); 
  WIRE_SEND(0x03);  // Send address to read from
  Wire.endTransmission();
  
  Wire.beginTransmission(MAGN_ADDRESS); 
  Wire.requestFrom(MAGN_ADDRESS, 6);  // Request 6 bytes
  while(Wire.available())  // ((Wire.available())&&(i<6))
  { 
    buff[i] = WIRE_RECEIVE();  // Read one byte
    i++;
  }
  Wire.endTransmission();
  
  if (i == 6)  // All bytes received?
  {

    // MSB byte first, then LSB; Y and Z reversed: X, Z, Y
    magnetom[0] = (((int) buff[0]) << 8) | buff[1];         // X axis (internal sensor x axis)
    magnetom[1] = -1 * ((((int) buff[4]) << 8) | buff[5]);  // Y axis (internal sensor -y axis)
    magnetom[2] = -1 * ((((int) buff[2]) << 8) | buff[3]);  // Z axis (internal sensor -z axis)

  }
}
