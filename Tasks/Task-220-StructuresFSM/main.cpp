#include "uop_msb.h"
#include "SwitchLed.h"
#include <cstring>

// Inputs
DigitalIn SWB(USER_BUTTON); // THIS IS THE BLUE BUTTON
DigitalIn SW2(BTN1_PIN);    // SW2
DigitalIn SW3(BTN2_PIN);    // SW3

// Outputs
DigitalOut ledRed(TRAF_RED1_PIN);
DigitalOut ledYel(TRAF_YEL1_PIN);
DigitalOut ledGrn(TRAF_GRN1_PIN);

// Timers (modified version from Timer)
TimerCompat tmr_debounce2;
TimerCompat tmr_debounce3;
TimerCompat tmr_flash;

// By-reference must always be initialised
SwitchLedState pair1 = {.sw=SW2, .tmr=tmr_debounce2, .led = ledRed };
SwitchLedState pair2 = {.sw=SW3, .tmr=tmr_debounce3, .led = ledGrn };


int main() {
  // Start flashing timer
  tmr_flash.start();

  while (true) {

    // READ INPUTS **WITHOUT** BLOCKING
    readInputs(pair1);
    readInputs(pair2);

    long long flash_time = tmr_flash.read_ms();

    // Update yellow LED state and mealy outputs
    if (flash_time >= 500) {
      ledYel = !ledYel;
      tmr_flash.reset();
    }

    // Update switch2 state machine and mealy outputs
    updateState(pair1);
    updateState(pair2);
 
  }
}
