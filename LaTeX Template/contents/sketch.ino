void setup()
{
  Serial.begin(9600);   //baud rate
}

void loop()
{
  int iDigitASCII = 0;
  
  iDigitASCII = Serial.read();  //Xbee is connected to the serial I/O
  
  if(iDigitASCII != -1)  //suppressing the nothing recieved characters
  {
    Serial.println(iDigitASCII); //printing recieved data to monitor
  }
}

//From the sending module we write: 
// 1  \n   2  \n   3  \n   4  \n   5  \n
//and we recieve the cooresponding ASCII values:  
// 49  10  50  10  51  10  52  10  53  10