#include "uop_msb.h"
#include "SwitchTimerLedManager.hpp"
#include "FlashingLED.hpp"
#include <chrono>
#include <ratio>
using namespace uop_msb;
using namespace chrono;

//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

//State machines 
SwitchTimerLedManager fsm1(BTN1_PIN, SwitchTimerLedManager::UP);
SwitchTimerLedManager fsm2(BTN2_PIN, SwitchTimerLedManager::DOWN);
FlashingLED ledGreen(TRAF_GRN1_PIN, 250ms);
FlashingLED ledYellow(TRAF_YEL1_PIN, 350ms);
FlashingLED ledRed(TRAF_RED1_PIN, 450ms);

int main()
{
    //This is to be displayed and is shared between two state machines
    int count = 0;

    //Turn ON the 7-segment display
    disp.enable(true);
    disp = 0;
    
    while (true) {

        // **********
        //Poll inputs
        // **********
        fsm1.readInputs();
        fsm2.readInputs();
        ledGreen.readInputs();
        ledYellow.readInputs();
        ledRed.readInputs();

        // **************
        // UPDATE "STATE" 
        // **************
        fsm1.updateState(count);
        fsm2.updateState(count);
        ledGreen.updateState();
        ledYellow.updateState();
        ledRed.updateState();

        // UPDATE OUTPUTS
        disp = count;
  
    }
}





