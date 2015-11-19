void convertFromASCII(unsigned char iaRawCoord[15], int iaXYZ[3])
{
  int j = 0;
  int k = 0;
  int iCoord = 0;

  for( k = 0; k*5<15; k++ )
  {
    for( j=1; j<=4; j++ )
    {  
      if(iaRawCoord[j+k*5] >= '0' && iaRawCoord[j+k*5] <= '9')
      {
        iCoord *= 10;
        iCoord += iaRawCoord[j] - '0';
      }
    }
    if( iaRawCoord[k*5] == '-')       { iCoord *= -1; }
    else if( iaRawCoord[k*5] == '+')  { iCoord *= 1; }
  
    iaXYZ[k] = iCoord;
  }
}

void readCoord(int iaXYZ[3])
{
  unsigned char iaRawCoord[15];           //      |+/-| |2| |3| |4| |5|    |+/-| |2| |3| |4| |5|     |+/-| |2| |3| |4| |5|     |\n|

  int i = 0;
  int iCoord = 0;
  int iDigitASCII = -1;
  
  while(iDigitASCII == -1)
  {
    iDigitASCII = Serial.read();
    //Serial.println(iDigitASCII);
  }
  
  while( iDigitASCII != '\n' )
  {
    iaRawCoord[i] = iDigitASCII;
    while(iDigitASCII == -1){ iDigitASCII = Serial.read(); }
    i++;
    Serial.println(iDigitASCII);
  }

  //if( i != 16 )
  //{
  //  return;
  //}
  convertFromASCII(iaRawCoord, iaXYZ);
}


void setup()
{
  Serial.begin(9600);   //baud rate
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop()
{
  int iaXYZ[3];

  readCoord(iaXYZ);

  //if(iaXYZ[0] != 0 && iaXYZ[1] != 0 && iaXYZ[2] != 0)
  //{
    Serial.print("X: ");
    Serial.println(iaXYZ[0]);
    Serial.print("Y: ");
    Serial.println(iaXYZ[1]);
    Serial.print("Z: ");
    Serial.println(iaXYZ[2]);
  //}
}
