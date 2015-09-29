void setup()
{
  Serial.begin(9600);   //baud rate for USB
  Serial3.begin(9600);   //baud rate
}

void loop()
{
  int iDigitASCII = 0;
  
  //Xbee is connected to one of the serial I/O ports
  iDigitASCII = Serial3.read();  
  
  //suppressing the nothing recieved characters
  if(iDigitASCII != -1)  
  {
  	//printing recieved data to monitor
    Serial.println(iDigitASCII); 
  }
}

//From the sending module we write:                
//  1  \n   2  \n   3  \n   4  \n   5  \n
//and we recieve the cooresponding ASCII values:
// 49  10  50  10  51  10  52  10  53  10