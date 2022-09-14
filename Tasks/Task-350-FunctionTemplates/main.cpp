#include "uop_msb.h"
#include "util_functions.hpp"

#include <iostream>
using namespace std;

DigitalOut led1(LED1);
DigitalOut led2(LED2);

AnalogIn pot(AN_POT_PIN);

// Template function to see if a value is significantly larger than the previous value
template<class T>
bool hasIncreasedBy(T next, T delta)
{
    // Remember that the value in a static local is retained
    static T prev = (T)0;

    T threshold = (prev + delta);
    prev = next;

    //Is the new value significantly larger than the previous?
    if (next > threshold) {
        return true;
    } else {
        return false;
    }

}

// Template function to see if a value is significantly smaller than the previous value
template<class U>
bool hasDecreasedBy(U next, U delta)
{
    // Remember that the value in a static local is retained
    static U prev = (U)0;

    U threshold = (prev - delta);
    prev = next;

    //Is the new value significantly smaller than the previous?
    if (next < threshold) {
        return true;
    } else {
        return false;
    }
}

int main()
{

    printf("Start\n\r");

    while (true) {
        //Read the ADC     
        uint16_t uPot = pot.read_u16() >> 4;    //12-bit Integer
        float fPot    = (float)uPot / 4095.0f;  //Scaled 0.0-1.0      
        
        //Floating point version
        if (hasIncreasedBy<float>(fPot, 0.1f)) {
            led1 = 1;
        }
        else if (hasDecreasedBy<float>(fPot, 0.1f)) {
            led1 = 0;
        }


        //16-bit unsigned integer version
        if (hasIncreasedBy<uint16_t>(uPot, 410)) {
            led2 = 1;
        }
        else if (hasDecreasedBy<uint16_t>(uPot, 410)) {
            led2 = 0;
        }

        wait_us(500000);
    }
}




