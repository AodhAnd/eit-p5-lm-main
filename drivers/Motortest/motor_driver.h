#define dPinMove1 2
#define dPinMove2 7
#define dPinOnOff 6

#define dPinCurrent1 0
#define dPinCurrent2 1
#define dPinSpeed 9

struct motor_info
{
    int iSpeed;         //by PWM, (0-100%)
    int iDir;            //0, break, 1 forward, 2 backward
    int iCurrent;        //motor current
    int iOnOff;
};

#ifdef __cplusplus
extern "C"{
#endif


int speed(int iSpeed);    //tells to the motot the speed it should have
int direction(int iDir);   //tells to the motor the direction it should have
int motorCurrent();      //asks the current in the motor
int enableMotor(int iOnOff);
int test(int iTest);


#ifdef __cplusplus
} // extern "C"
#endif
