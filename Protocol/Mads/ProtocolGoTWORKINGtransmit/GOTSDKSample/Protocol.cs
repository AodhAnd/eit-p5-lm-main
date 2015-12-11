using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace GOTSDKSample
{
    class Protocol
    {
        public byte[] ProtocolGet(int X, int Y, int Z)
        {

            //Length of the different parts of the protocol
            int lStart = 8;
            int lDestination = 8;
            int lLength = 7;
            int lCoordinate = 15;
            int lChecksum = 20;
            int lEnd = 8;
            int FinalBitCount = lStart + lDestination + lLength + 3*lCoordinate + lChecksum + lEnd;

            //Setup the numbers, so the 15th bit gonna be the sign bit
            X = NegToPos(X);
            Y = NegToPos(Y);
            Z = NegToPos(Z);


            BitArray finalPacket = new BitArray(FinalBitCount, false);                      //Bitarray for the final packet

            BitArray tPacket = new BitArray((lDestination + lLength + 3 * lCoordinate), false);    //Bitarray to all the parts, that the checksum checks on

            BitArray baStart = new BitArray(new int[] { 240 });                            //Bitarray for the Header

            BitArray baDestination = new BitArray(new int[] { 128 });                            //Bitarray for the Source

            BitArray baLength = new BitArray(new int[] { 96 });                               //Bitarray for the Type

            BitArray baXData = new BitArray(new int[] { X });                               //Bitarray for the X-coordinate

            BitArray baYData = new BitArray(new int[] { Y });                               //Bitarray for the Y-coordinate

            BitArray baZData = new BitArray(new int[] { Z });                               //Bitarray for the Z-coordinate

            BitArray baChecksum = new BitArray(lChecksum, false);                           //Bitarray for the checksum

            BitArray baEnd = new BitArray(new int[] { 15 });                           //Bitarray for the Trailer


            //Filling the tPacket with the source, type and coordinates
            int Place = 0;
            for(int i = 0; i < lDestination; i++)
            {
                tPacket[Place] = baDestination[i];
                Place++;
            }
            for (int i = 0; i < lLength; i++)
            {
                tPacket[Place] = baLength[i];
                Place++;
            }
            for (int i = 0; i < lCoordinate; i++)
            {
                tPacket[Place] = baXData[i];
                Place++;
            }
            for (int i = 0; i < lCoordinate; i++)
            {
                tPacket[Place] = baYData[i];
                Place++;
            }
            for (int i = 0; i < lCoordinate; i++)
            {
                tPacket[Place] = baZData[i];
                Place++;
            }

            //Generate the checksum
            baChecksum = ChecksumGenerator(tPacket, lChecksum);

            //Put all the small bitarrays together, into a final packet
            int Counter = 0;
            for (int i = 0; i < lStart; i++)
            {
                finalPacket[Counter] = baStart[i];
                Counter++;
            }
            for (int i = 0; i < (lDestination + lLength + 3 * lCoordinate); i++)
            {
                finalPacket[Counter] = tPacket[i];
                Counter++;
            }
            for (int i = 0; i < lChecksum; i++)
            {
                finalPacket[Counter] = baChecksum[i];
                Counter++;
            }
            for (int i = 0; i < lEnd; i++)
            {
                finalPacket[Counter] = baEnd[i];
                Counter++;
            }


            byte[] Transmitpacket = new byte[FinalBitCount/8];  //Initialize the byte array, there is gonna be send

            finalPacket.CopyTo(Transmitpacket, 0);              //Convert the final bitarray into the byte array that is gonna be send

            return Transmitpacket;                              //Return the final byte array aka. the package
        }

        private BitArray ChecksumGenerator(BitArray tPacket, int lChecksum) //Generates the checksum
        {

            BitArray Checksum = new BitArray(lChecksum, false);     //Bitarray for the checksum

            BitArray Temp = new BitArray((lChecksum + 2), false);   //Bitarray for the summation

            BitArray Temp2 = new BitArray((lChecksum + 2), false);  //Bitarray for the summation

            BitArray[] PacketPart = new BitArray[3];                //Array of bitarray, to split tPacket up into 20 bit pieces

            //Fill up the PacketPart with the tPacket
            for (int i = 0; i < 3; i++)
            {
                PacketPart[i] = new BitArray(20, false);

                for (int j = 0; j < 20; j++)
                {
                    PacketPart[i][j] = tPacket[j + (i * 20)];
                }
            }

            Temp = SumOfbitArrays(PacketPart[0], PacketPart[1], PacketPart[2], lChecksum); //Add the three pieces together

            if(Temp[20] || Temp[21]) //If there are carries (higher than 20th bit) these is added on the 20 first bits
            {
               Checksum = CarryAdd(Temp, lChecksum);
            }
            else //If not, the summed bitarray is put over in the checksum
            {
                for(int i = 0; i < 20; i++)
                {
                    Checksum[i] = Temp[i];
                }
            }

            //To have the correct checksum, it have to be the invers of the summed bitarray
            for(int i = 0; i < 20; i++)
            {
                Checksum[i] = !Checksum[i]; 
            }

            return Checksum; //Return the checksum
        }

        private BitArray CarryAdd(BitArray temp, int lChecksum) //Add carries on, for the checksum
        {
            bool Carry = false;                         //Bool to save the carry for time to time
            BitArray Final = new BitArray(20, false);   //Bitarray for the final summation
            BitArray Carries = new BitArray(22, false); //Bitarray for the carries

            //As long as there is carries
            while (temp[20] || temp[21]) 
            {
                //The old carries is moved over to the carry bitarray
                Carries[0] = temp[20];
                Carries[1] = temp[21];
                temp[20] = false;
                temp[21] = false;

                //Summation of the carry
                for (int i = 0; i < 22; i++)
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
                Carry = false; //Reset the carry after the summation
            }

            //Take the 20 first bits, which is the summation of the carries and the rest
            for(int i = 0; i < 20; i++) 
            {
                Final[i] = temp[i];
            }

            return Final;
        }

        private BitArray SumOfbitArrays(BitArray ba1, BitArray ba2, BitArray ba3, int lChecksum) //The three bit arrays of 20 is summed together
        {
            bool Carry = false;                                     //Bool to save the carry for time to time
            BitArray temp = new BitArray((lChecksum + 2), false);   //Bitarray to the summation

            //Add ba1 and ba2 together
            for (int i = 0; i < lChecksum; i++)
            {
                if (Carry && ba1[i] && ba2[i])
                {
                    Carry = true;
                    temp[i] = true;
                }
                else if ((ba1[i] && ba2[i])||(ba1[i] && Carry)||(ba2[i] && Carry))
                {
                    Carry = true;
                    temp[i] = false;
                }
                else if (ba1[i] || ba2[i]||Carry)
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

            temp[lChecksum] = Carry; //Insert carry from the last calculation into bit 21

            Carry = false; //Reset carry

            //Add ba3 and temp together
            for (int i = 0; i < lChecksum; i++)
            {
                if (Carry && ba3[i] && temp[i])
                {
                    Carry = true;
                    temp[i] = true;
                }
                else if ((ba3[i] && temp[i]) || (ba3[i] && Carry) || (temp[i] && Carry))
                {
                    Carry = true;
                    temp[i] = false;
                }
                else if (ba3[i] || temp[i] || Carry)
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

            //In case of carries, these is added together, into bit 21 and 22
            if (Carry && temp[lChecksum])
                {
                    temp[lChecksum + 1] = true;
                    temp[lChecksum] = false;
                }
                else if (Carry || temp[lChecksum])
                {
                    temp[lChecksum] = true;
                }

            return temp;
        }

        private int NegToPos(int Number) //Sets the sign bit for the coordinates
        {
            if (Number < 0) //If the number is negativ, it is converted to positive and added 16384, so the sign bit will be true
            {
                Number = (Number * (-1)) + 16384; 
            }

            return Number;
        }        
    }
}
