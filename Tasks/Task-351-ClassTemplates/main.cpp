#include "uop_msb.h"
#include "RunningMean.hpp"

#include <iostream>
using namespace std;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
AnalogIn pot(AN_POT_PIN);

//Defines an object with a fixed-size internal buffer
RunningMean<uint16_t, double, 4> buf4;

int main()
{
    printf("\n\rStart\n\r");

    while (true) {
        //Read the ADC     
        uint16_t uPot = pot.read_u16() >> 4;    //12-bit Integer 0..4095
        float    fPot = (float)uPot / 4095.0f;  //Scaled 0.0-1.0      
 
        //Add sample to buffer.
        buf4 += uPot;

        //Output running mean
        cout << "Mean: " << buf4 << endl;
        wait_us(500000);
    }
}




