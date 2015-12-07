#include "ProtocolReceive.h"

void setup() {
  Serial.begin(9600);

}

void loop() {

  int Output[5];
  int Done = GetProtocol(Output);

  Serial.print("Foul: ");
  Serial.println(Done);
  if(Done == 0)
  {
    for(int i = 0; i < 5; i++)
    {
      Serial.println(Output[i]);
    }

    Serial.println("Package received");
  }
  //Serial.println("Package received");
  
}


