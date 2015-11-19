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

        static int Protocol(int X, int Y, int Z)
        {

            int i = 0;
            int j = 0;

            int Source = 7;
            int LengthOfCoordinate = 15;
            int FinalBitCount = 80;

            BitArray bData = new BitArray(FinalBitCount, false); //creating the necessary quantity of bits for the source

            BitArray ZData = new BitArray(new int[] { Z });

            BitArray XData = new BitArray(new int[] { X });

            BitArray YData = new BitArray(new int[] { Y });

            BitArray ProtocolLength = IntToBitA(80, 7);

            while (i != 60)
            {
                 for(j = 0; j < 8; j++)
                {
                    if(i == Source)
                    {
                        bData[i] = true; //Source is set
                    }
                    i++;
                }
                 for(j = 0; j < LengthOfCoordinate; j++)
                {
                    bData[i] = XData[j]; //X data is set
                    i++;
                }
                 for(j = 0; j < LengthOfCoordinate; j++)
                {
                    bData[i] = YData[j]; //Y data is set
                    i++;
                }
                 for (j = 0; j < LengthOfCoordinate; j++)
                {
                    bData[i] = ZData[j]; //Z data is set
                    i++;
                }
                for (j = 0; j < 7; j++)
                {
                    bData[i] = ProtocolLength[j]; //Protocol Length is set
                    i++;
                }
            }

            for (j = 0; j < 63; j++)
            {
                Console.WriteLine(bData[j] + j.ToString());
            }
            Console.ReadLine();


            //Transform Data to a bit array



            //int LengthTemperary = Data.Length + ComSource.Length + Checksum.Length; //The length of the data which is send

            //string Length = LengthTemperary.ToString(); //makes the int LengthTemperary a string

            //string Transmit = (ComSource + Data + Length + Checksum); //Which needs to be transmitted

            return 0;

        }


       /* static BitArray ChecksumGenerator(BitArray protocolData)
        {
            int i = 0;
            int j = 0;

            BitArray Checksum = new BitArray(20, false);

            BitArray Temp = new BitArray(22, false);

            BitArray Temp2 = new BitArray(22, false);

            BitArray[] ProtocolDataSplit = new BitArray[3];

            for (i = 0; i < 3; i++)
            {
                ProtocolDataSplit[i] = new BitArray(20, false);

                for (j = 0; j < 20; j++)
                {
                    ProtocolDataSplit[i][j] = protocolData[j + ((i - 1) * 20)];
                }
            }

            Temp = SumOfbitArrays(ProtocolDataSplit[1], ProtocolDataSplit[2], 20);

            return Checksum;
        }

        static BitArray SumOfbitArrays(BitArray ba1, BitArray ba2, int lengthba1)
        {
            int i = 0;


            BitArray ba1andba2 = new BitArray(22, false);

            for(i = 0; i < lengthba1; i++)
            {

            }

            return ba1andba2;
        }*/


        static int NegToPos(int Number)
        {
            if (Number < 0)
            {
                Number = (Number * (-1)) + 16384; //implements the signbit into the number
            }

            return Number;
        }

        static BitArray IntToBitA(int Number, int Lenght) //converts integer to a certain length bitarray.
        {
            BitArray Out = new BitArray(Lenght, false);

                if (Number < 0)  //example: -1 = 11111111 last bit is the sign bit
                {
                    Out[Lenght - 1] = true;  //00000001 the output
                    Lenght = Lenght - 1;     
                    Number = Number * (-1);  //10000000 - the number is inverted
                }

            BitArray Temp = new BitArray(new int[] { Number }); //number is put in a temp bitarray
                for (int i = 0; i < Lenght; i++) //length is now 7
                    {
                     Out[i] = Temp[i];  //number is put into our output = 10000001
                     }

            return Out;
        }

        static void Main(string[] args)
        {
            int X = -1;
            int Y = -1;
            int Z = -1;

            X = NegToPos(X);

            Y = NegToPos(Y);

            Z = NegToPos(Z);


            Protocol(X, Y, Z);

        }
    }
}
