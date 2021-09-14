#include "uop_msb.h"
#include "SwitchTimerLedManager.hpp"
#include <chrono>
#include <ratio>
using namespace uop_msb;
using namespace chrono;

Timer tmrLED;
SwitchTimerLedManager fsm1(BTN1_PIN, SwitchTimerLedManager::UP);
SwitchTimerLedManager fsm2(BTN2_PIN, SwitchTimerLedManager::DOWN);

DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

microseconds timeLED;

int main()
{
    int count = 0;

    //Turn ON the 7-segment display
    disp.enable(true);
    disp = 0;
    
    //Start LED timer
    tmrLED.start();
    disp = count;

    while (true) {

        // **********
        //Poll inputs
        // **********
        timeLED = tmrLED.elapsed_time();
        fsm1.readInputs();
        fsm2.readInputs();

        // **********************************
        // UPDATE "STATE" for buttons A and B
        // **********************************
        fsm1.updateState(count);
        fsm2.updateState(count);

        // ********************************
        // UPDATE "STATE" for LED and Timer
        // ********************************
        if (timeLED >= 250ms) {
            greenLED = !greenLED;
            tmrLED.reset();
        }

        // UPDATE OUTPUTS
        disp = count;
  
    }
}





