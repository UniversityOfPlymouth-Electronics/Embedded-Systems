#include "uop_msb.h"
#include <chrono>
#include <ratio>
using namespace uop_msb;
using namespace chrono;

//Count variable
int counter=0;

InterruptIn btnA(BTN1_PIN);
InterruptIn btnB(BTN2_PIN);
Ticker tick;

DigitalOut redLED(TRAF_RED1_PIN);       //Red Traffic 1
DigitalOut yellowLED(TRAF_YEL1_PIN);    //Yellow Traffic 1
DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);


void funcA()
{
    redLED = !redLED;
}

void funcTmr()
{
    greenLED = !greenLED;
}

int main()
{
    //Set up interrupts
    btnA.rise(&funcA);
    tick.attach(&funcTmr, 500ms);
    
    //Main loop - mostly sleeps :)
    while (true) {
        sleep();

        printf("I have been woken %d times\n", ++counter);
    }
}





