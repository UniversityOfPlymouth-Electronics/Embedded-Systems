#include "uop_msb.h"
#include <chrono>
#include <ratio>
using namespace uop_msb;
using namespace chrono;

BusIn buttons(BTN1_PIN, BTN2_PIN, BTN3_PIN, BTN4_PIN);

DigitalOut redLED(TRAF_RED1_PIN);       //Red Traffic 1
DigitalOut yellowLED(TRAF_YEL1_PIN);    //Yellow Traffic 1
DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

//Timers
TimerCompat tmrA;
TimerCompat tmrB;

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

    // Storage for input devices
    typedef enum {WAITING_FOR_PRESS, DEBOUNCE_1, WAITING_FOR_RELEASE, DEBOUNCE_2} SWITCH_STATE;

    //Where we are in the sequence (Press - wait - release - wait)
    SWITCH_STATE stateA = WAITING_FOR_PRESS;
    SWITCH_STATE stateB = WAITING_FOR_PRESS;

    // Input storage variables
    int btnA = 0;
    int btnB = 0;
    long long timeA = 0;  
    long long timeB = 0;
    
    while (true) {

        // ************************************
        // Read all inputs and store the result
        // ************************************
        btnA = buttonA;
        btnB = buttonB;
        timeA = tmrA.read_ms();
        timeB = tmrB.read_ms();

        // ***************************
        // UPDATE "STATE" for button A
        // ***************************

        switch (stateA) {
            case WAITING_FOR_PRESS:
                if (btnA == 1) {
                    stateA = DEBOUNCE_1;
                    tmrA.reset();
                    tmrA.start();
                    if (count < 99) {
                        disp = ++count;
                    }
                }
            break;

            case DEBOUNCE_1:
                if (timeA >= 250) {
                    stateA = WAITING_FOR_RELEASE;
                    tmrA.stop();
                }
            break;

            case WAITING_FOR_RELEASE:
                if (btnA == 0) {
                    stateA = DEBOUNCE_2;
                    tmrA.reset();
                    tmrA.start();
                }
            break;

            case DEBOUNCE_2:
                if (timeA >= 250) {
                    stateA = WAITING_FOR_PRESS;
                    tmrA.stop();
                }
            break;            
        }

        // ***************************
        // UPDATE "STATE" for button B
        // ***************************

        switch (stateB) {
            case WAITING_FOR_PRESS:
                if (btnB == 1) {
                    stateB = DEBOUNCE_1;
                    tmrB.reset();
                    tmrB.start();
                    if (count > 0) {
                        disp = --count;
                    }
                }
            break;

            case DEBOUNCE_1:
                if (timeB >= 250) {
                    stateB = WAITING_FOR_RELEASE;
                    tmrB.stop();
                }
            break;

            case WAITING_FOR_RELEASE:
                if (btnB == 0) {
                    stateB = DEBOUNCE_2;
                    tmrB.reset();
                    tmrB.start();
                }
            break;

            case DEBOUNCE_2:
                if (timeB >= 250) {
                    stateB = WAITING_FOR_PRESS;
                    tmrB.stop();
                }
            break;            
        }

  
    }
}





