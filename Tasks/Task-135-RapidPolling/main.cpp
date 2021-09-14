#include "uop_msb.h"
using namespace uop_msb;

BusIn buttons(BTN1_PIN, BTN2_PIN, BTN3_PIN, BTN4_PIN);
// DigitalIn buttonA(BTN1_PIN);    //ButtonA is synonamous with buttons[0]
// DigitalIn buttonB(BTN2_PIN);
// DigitalIn buttonC(BTN3_PIN);
// DigitalIn buttonD(BTN4_PIN);

DigitalOut redLED(TRAF_RED1_PIN);       //Red Traffic 1
DigitalOut yellowLED(TRAF_YEL1_PIN);    //Yellow Traffic 1
DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

int main()
{
    volatile int count = 0;

    // This little C++ trick allows us to use BOTH BusIn and DigitalIn
    DigitalIn& buttonA = buttons[0];    //ButtonA is synonamous with buttons[0]
    DigitalIn& buttonB = buttons[1];
    DigitalIn& buttonC = buttons[2];
    DigitalIn& buttonD = buttons[3];

    //Configure switches
    buttonC.mode(PullDown);
    buttonD.mode(PullDown);

    //Turn ON the 7-segment display
    disp.enable(true);

    int btnA_prev = buttonA;
    int btnB_prev = buttonB;
    int btnA_curr;
    int btnB_curr;
    
    while (true) {

        // ************************************
        // Read all inputs and store the result
        // ************************************
        btnA_curr = buttonA;
        btnB_curr = buttonB;

        // ****************************
        // UPDATE IF THERE WAS A CHANGE
        // ****************************

        // Did button A change?
        if (btnA_curr != btnA_prev) {

            //Was it a press?
            if (btnA_curr == 1) {
                //Button A was pressed!
                if (count < 99) {
                    count+=1;
                }
            }

            // The previous value is now set to the current
            btnA_prev = btnA_curr;

            //Update display
            disp = count;            
        }

        // Did button B change?
        if (btnB_curr != btnB_prev) {

            //Was it a press?
            if (btnB_curr == 1) {
                //Button B was pressed!
                if (count > 0) {
                    count-=1;
                }
            }
            
            // The previous value is now set to the current
            btnB_prev = btnB_curr;

            //Update display
            disp = count;               
        }
        
        // Slow it down a bit (and debounce the switches)
        wait_us(250000);  
    }
}





