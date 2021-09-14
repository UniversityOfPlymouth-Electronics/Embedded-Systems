#include "uop_msb.h"
using namespace uop_msb;

//Declare functions
static int getDelayMS();
int getAverageDelay(double alpha);

//Devices
static AnalogIn pot(AN_POT_PIN);

static int getDelayMS() 
{
    float p = pot; // 0 ... 1
    int delay = 100 + 900*p;    //100...1000ms
    return delay;
}


//Calculate average delay by filtering the potentiometer value
int getAverageDelay(double alpha)
{
    static double meanPotValue = (double)getDelayMS();  //Mean pot value

    for (unsigned int n=0; n<32; n++) {
        int potValue = getDelayMS();                    //Get raw value (with noise)
        meanPotValue = alpha*meanPotValue + (1.0-alpha)*potValue; //Handy forumula!
    }
    return (int)meanPotValue;
}