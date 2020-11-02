#include "../lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

DigitalIn ButtonA(PG_0); //Button A
DigitalIn ButtonB(PG_1); //Button B
DigitalIn ButtonC(PG_2, PullDown); //Button C
DigitalIn ButtonD(PG_3, PullDown); //Button D

DigitalOut redLED(PC_2); //Red Traffic 1

LatchedLED disp(LatchedLED::SEVEN_SEG);

int main()
{
    int count = 0;
    // Turn OFF the red LED
    redLED = 0;
    disp.enable(true);

    while (true) {
        //Update display
        disp = count;

        //Wait for ALL buttons to be pressed
        while (ButtonA == 0) {
            //Spin in a loop
        }

        redLED = !redLED;

        //Wait for noise to settle
        wait_us(10000);

        while (ButtonA == 1) {
            //Spin in a loop
        }

        //Wait for noise to settle
        wait_us(10000);        

        //Increment count
        if (count < 99) {
            count++;
        } else {
            count = 0;
        }
    }
}


