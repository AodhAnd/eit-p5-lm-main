using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace TransportLayerGr510
{

    class Program
    {

        static byte[] Protocol(int X, int Y, int Z)
        {

            int i = 0;
            int j = 0;

            int LengthSource = 7;
            int LengthOfCoordinate = 15;
            int FinalBitCount = 88;

                BitArray bPacket = new BitArray(FinalBitCount, false);  //creating the necessary quantity of bits for the source

                BitArray TemperaryPacket = new BitArray(60, false);     //To contain the source, length and the z, x, y coordinate temperary

                BitArray ZData = new BitArray(new int[] { Z });         //a bitarray for the Z-coordinate

                BitArray XData = new BitArray(new int[] { X });         //a bitarray for the X-coordinate

                BitArray YData = new BitArray(new int[] { Y });         //a bitarray for the Y-coordinate

                BitArray Checksum = new BitArray(20, false);            //a bitarray for the checksum

                BitArray ProtocolLength = IntToBitA(88, 7);             //The length of the protocol
   

            while (i != 60)
            {
                 for(j = 0; j < 8; j++)
                {
                    if(i == LengthSource)
                    {
                        TemperaryPacket[i] = true;                      //Source is set
                    }
                    i++;
                }
                for (j = 0; j < 7; j++)
                {
                    TemperaryPacket[i] = ProtocolLength[j];             //Protocol Length is set
                    i++;
                }
                for (j = 0; j < LengthOfCoordinate; j++)
                {
                    TemperaryPacket[i] = XData[j];                      //X data is set
                    i++;
                }
                 for(j = 0; j < LengthOfCoordinate; j++)
                {
                    TemperaryPacket[i] = YData[j];                      //Y data is set
                    i++;
                }
                 for (j = 0; j < LengthOfCoordinate; j++)
                {
                    TemperaryPacket[i] = ZData[j];                      //Z data is set
                    i++;
                }
            }

            Checksum = ChecksumGenerator(TemperaryPacket);

            for(i = 0; i < 88; i++)
            {
                if(i < 7)
                {
                    bPacket[i] = false;                                 //first seven bit of start character (first of the two sources) is set to zero and is placed into the transmit packet.
                }
                else
                {
                    bPacket[i] = true;                                  //last bit of the first bytes is set to a one is placed into the transmit packet
                }

                if (i < 68 && i > 7)
                {
                    bPacket[i] = TemperaryPacket[i-8];                  //the length and the coordinates is placed into the transmit packet
                }
                else if(i > 67)
                {
                    bPacket[i] = Checksum[i - 68];                      //The checksum is set into the transmit packet
                }
            }

            for(j = 0; j < 88; j++)
            {
                Console.WriteLine(bPacket[j] + j.ToString());
            }
            //Console.ReadLine();

            byte[] Transmitpacket = new byte[11];

            bPacket.CopyTo(Transmitpacket, 0);                          //The bit array bPacket is made into a bytearray which is placed in transmitpacket.

            return Transmitpacket;                                      //The packet which needs to be sent 
        }


        static BitArray ChecksumGenerator(BitArray protocolData) //generates the Checksum
        {
            int i = 0;
            int j = 0;

                BitArray Checksum = new BitArray(20, false);

                BitArray Temp = new BitArray(22, false);

                BitArray Temp2 = new BitArray(22, false);

                BitArray[] ProtocolDataSplit = new BitArray[3]; //To contain the data of 60 bits (source, length, x, y, z) in three 20 bitarray

            for (i = 0; i < 3; i++)
            {
                ProtocolDataSplit[i] = new BitArray(20, false);

                for (j = 0; j < 20; j++)
                {
                    ProtocolDataSplit[i][j] = protocolData[j + (i * 20)];
                }
            }

            Temp = SumOfbitArrays(ProtocolDataSplit[0], ProtocolDataSplit[1], ProtocolDataSplit[2]); //the three 20 bitarray is summed together

            if(Temp[20] || Temp[21])
            {
               Checksum = CarryAdd(Temp);
            }
            else
            {
                for(i = 0; i < 20; i++)
                {
                    Checksum[i] = Temp[i];
                }
            }

            for(i = 0; i < 20; i++)
            {
                Checksum[i] = !Checksum[i]; 
            }

            return Checksum;
        }

        static BitArray CarryAdd(BitArray temp) //The carries which can occure when summing the bitarrays of 20 is added to the summed bitarray
        {
            int i = 0;
            bool Carry = false;

                BitArray Final = new BitArray(20, false);
                BitArray Carries = new BitArray(22, false);

            while (temp[20] || temp[21])
            {
                Carries[0] = temp[20];
                Carries[1] = temp[21];
                temp[20] = false;
                temp[21] = false;

                for (i = 0; i < 22; i++)
                {
                    if (Carry && Carries[i] && temp[i])
                    {
                        Carry = true;
                        temp[i] = true;
                    }
                    else if ((Carries[i] && temp[i]) || (Carries[i] && Carry) || (temp[i] && Carry))
                    {
                        Carry = true;
                        temp[i] = false;
                    }
                    else if (Carries[i] || temp[i] || Carry)
                    {
                        temp[i] = true;
                        Carry = false;
                    }
                    else
                    {
                        Carry = false;
                        temp[i] = false;
                    }
                }
            }

            for(i = 0; i < 20; i++)
            {
                Final[i] = temp[i];
            }

            return Final;
        }

        static BitArray SumOfbitArrays(BitArray BitArray1, BitArray BitArray2, BitArray BitArray3) //The three bit arrays of 20 is summed together
        {
            int i = 0;
            bool Carry = false;

            BitArray ba1andba2 = new BitArray(22, false);

            for (i = 0; i < 20; i++)
            {
                if (Carry && BitArray1[i] && BitArray2[i])
                {
                    Carry = true;
                    ba1andba2[i] = true;
                }
                else if ((BitArray1[i] && BitArray2[i])||(BitArray1[i] && Carry)||(BitArray2[i] && Carry))
                {
                    Carry = true;
                    ba1andba2[i] = false;
                }
                else if (BitArray1[i] || BitArray2[i]||Carry)
                {
                    ba1andba2[i] = true;
                    Carry = false;
                }
                else
                {
                    Carry = false;
                    ba1andba2[i] = false;
                }
            }

            ba1andba2[20] = Carry;

            Carry = false;

            for (i = 0; i < 20; i++)
            {
                if (Carry && BitArray3[i] && ba1andba2[i])
                {
                    Carry = true;
                    ba1andba2[i] = true;
                }
                else if ((BitArray3[i] && ba1andba2[i]) || (BitArray3[i] && Carry) || (ba1andba2[i] && Carry))
                {
                    Carry = true;
                    ba1andba2[i] = false;
                }
                else if (BitArray3[i] || ba1andba2[i] || Carry)
                {
                    ba1andba2[i] = true;
                    Carry = false;
                }
                else
                {
                    Carry = false;
                    ba1andba2[i] = false;
                }
            }

            if (Carry && ba1andba2[20])
                {
                    ba1andba2[21] = true;
                    ba1andba2[20] = false;
                }
                else if (Carry || ba1andba2[20])
                {
                    ba1andba2[20] = true;
                }

            return ba1andba2;
        }


        static int NegToPos(int Number) //implements the signbit into a negative number
        {
            if (Number < 0)
            {
                Number = (Number * (-1)) + 16384; 
            }

            return Number;
        }

        static BitArray IntToBitA(int Number, int Lenght)   //converts integer to a certain length bitarray.
        {
            BitArray Out = new BitArray(Lenght, false);

                if (Number < 0)                             //example: -1 = 11111111 last bit is the sign bit
                {
                    Out[Lenght - 1] = true;                 //00000001 the output
                    Lenght = Lenght - 1;     
                    Number = Number * (-1);                 //10000000 - the number is inverted
                }

            BitArray Temp = new BitArray(new int[] { Number }); //number is put in a temp bitarray

                for (int i = 0; i < Lenght; i++)            //length is now 7
                    {
                     Out[i] = Temp[i];                      //number is put into our output = 10000001
                     }

            return Out;
        }

        static void Main(string[] args)
        {
            byte[] Transmitpacket = new byte[11];

            int X = 1;
            int Y = 1;
            int Z = 80;

            X = NegToPos(X);

            Y = NegToPos(Y);

            Z = NegToPos(Z);

            Transmitpacket = Protocol(X, Y, Z);

            System.IO.Ports.SerialPort Serialport = new System.IO.Ports.SerialPort("COM17");

            Serialport.Open();

            Serialport.Write(Transmitpacket,0,11);

            Serialport.Close();
        }
    }
}
