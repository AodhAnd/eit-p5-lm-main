typedef struct {
  uint8_t Source;
  uint8_t Length;
  int16_t Xcor;
  int16_t Ycor;
  int16_t Zcor;
  uint32_t Checksum;
}Protocol;

void DataToStruct(uint8_t Data[11])
{
  Protocol decript;
  
  decript.Source = Data[1];
  decript.Length = Data[2] << 1;
  
  uint8_t Tempx =  Data[4] << 2;
  uint16_t TempX2 = Tempx;
  TempX2 = TempX2 << 6;
  TempX2 += Data[3];
  TempX2 = TempX2 << 1;
  TempX2 += (Data[2] >> 7);
  if (TempX2 > 16384)
  {
    decript.Xcor = (TempX2 - 16384) * -1;
  }
  else
  {
    decript.Xcor = TempX2;
  }

  uint8_t Tempy =  Data[6] << 3;
  uint16_t TempY2 = Tempy;
  TempY2 = TempY2 << 5;
  TempY2 += Data[5];
  TempY2 = TempY2 << 2;
  TempY2 += (Data[4] >> 6);
  if (TempY2 > 16384)
  {
    decript.Ycor = (TempY2 - 16384) * -1;
  }
  else
  {
    decript.Ycor = TempY2;
  }

  uint8_t Tempz =  Data[8] << 4;
  uint16_t TempZ2 = Tempz;
  TempZ2 = TempZ2 << 4;
  TempZ2 += Data[7];
  TempZ2 = TempZ2 << 3;
  TempZ2 += (Data[6] >> 5);
  if (TempZ2 > 16384)
  {
    decript.Zcor = (TempZ2 - 16384) * -1;
  }
  else
  {
    decript.Zcor = TempZ2;
  }

  decript.Checksum = Data[10];
  decript.Checksum = decript.Checksum << 8;
  decript.Checksum += Data[9];
  decript.Checksum = decript.Checksum << 4;
  decript.Checksum += (Data[8] >> 4);

  uint8_t Tempcf = Data[3] << 4;
  uint32_t TempC1 = Tempcf;
  TempC1 = TempC1 << 4;
  TempC1 += Data[2];
  TempC1 = TempC1 << 8;
  TempC1 += Data[1];

  uint32_t TempC2 = Data[5];
  TempC2 = TempC2 << 8;
  TempC2 += Data[4];
  TempC2 = TempC2 << 4;
  TempC2 += (Data[3] >> 4);

  uint8_t Tempct = (Data[8] << 4);
  uint32_t TempC3 = Tempct;
  TempC3 = TempC3 << 4;
  TempC3 += Data[7];
  TempC3 = TempC3 << 8;
  TempC3 += Data[6];

  uint32_t TempC = TempC1 + TempC2 + TempC3 + decript.Checksum;

  Serial.println(TempC,BIN);

  Serial.println(TempC1,BIN);
  Serial.println(TempC2,BIN);
  Serial.println(TempC3,BIN);
  Serial.println(decript.Checksum,BIN);

  while(TempC > 1048575)
  {
    uint32_t TempAdd = TempC >> 20;
    uint32_t TempRest = TempC & 1048575;
    TempC = TempAdd + TempRest;
  }

  Serial.println(TempC,BIN);

  
}


void setup() {
  Serial.begin(9600);
}

void loop() {

  uint8_t Data[11];
  int TempLook = -1;
  int Done;
  
  while(TempLook == -1)
  {
    if (Serial.available() > 0)
    {
      TempLook = Serial.read();
      Data[0] = TempLook;
    }
  }
  
  TempLook = -1;
  while(TempLook == -1)
  {
    if (Serial.available())
    {
      TempLook = Serial.read();
      Data[1] = TempLook;

      if (Data[1] = 128)
      {
        TempLook = -1;
        while(TempLook == -1)
        {          
          if (Serial.available())
          {
            TempLook = Serial.read();

            char Temp = TempLook >> 1;
            Data[2] = TempLook;

            if (Temp = 160)
            {
              int BytesRead = 3;
              while (BytesRead < 11)
              {
                if (Serial.available())
                {
                  Data[BytesRead] = Serial.read();
                  BytesRead++;
                }
              }

              DataToStruct(Data);
            }                   
          }          
        }        
      }
    }
  }
}


