#include "uop_msb.h"
#include <cstring>
using namespace uop_msb;

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

// Switch states
typedef enum {
  WAIT_FOR_PRESS,
  WAITING_1,
  WAIT_FOR_REL,
  WAITING_2
} SWITCH_STATE;

SWITCH_STATE sw_state2 = WAIT_FOR_PRESS;
SWITCH_STATE sw_state3 = WAIT_FOR_PRESS;

int main() {
  // Start flashing timer
  tmr_flash.start();

  while (true) {

    // READ INPUTS **WITHOUT** BLOCKING
    long long flash_time = tmr_flash.read_ms();
    int sw2 = SW2.read();
    int sw3 = SW3.read();
    long long sw2_time = tmr_debounce2.read_ms();
    long long sw3_time = tmr_debounce3.read_ms();

    // Update yellow LED state and mealy outputs
    if (flash_time >= 500) {
      ledYel = !ledYel;
      tmr_flash.reset();
    }

    // Update switch2 state machine and mealy outputs
    switch (sw_state2) {

    case WAIT_FOR_PRESS:
      if (sw2 == 1) {
        sw_state2 = WAITING_1;
        tmr_debounce2.start();
        ledGrn = !ledGrn;
      }
      break;
    case WAITING_1:
      if (sw2_time >= 300) {
        sw_state2 = WAIT_FOR_REL;
        tmr_debounce2.stop();
        tmr_debounce2.reset();
      }
      break;

    case WAIT_FOR_REL:
      if (sw2 == 0) {
        sw_state2 = WAITING_2;
        tmr_debounce2.start();
      }
      break;
    case WAITING_2:
      if (sw2_time >= 300) {
        sw_state2 = WAIT_FOR_PRESS;
        tmr_debounce2.stop();
        tmr_debounce2.reset();
      }
      break;

    default:
      sw_state2 = WAIT_FOR_PRESS;
    }

    // Update switch3 state machine and mealy outputs
    // VERY REPETETIVE CODE!
    switch (sw_state3) {

    case WAIT_FOR_PRESS:
      if (sw3 == 1) {
        sw_state3 = WAITING_1;
        tmr_debounce3.start();
        ledRed = !ledRed;
      }
      break;
    case WAITING_1:
      if (sw3_time >= 300) {
        sw_state3 = WAIT_FOR_REL;
        tmr_debounce3.stop();
        tmr_debounce3.reset();
      }
      break;

    case WAIT_FOR_REL:
      if (sw3 == 0) {
        sw_state3 = WAITING_2;
        tmr_debounce3.start();
      }
      break;
    case WAITING_2:
      if (sw3_time >= 300) {
        sw_state3 = WAIT_FOR_PRESS;
        tmr_debounce3.stop();
        tmr_debounce3.reset();
      }
      break;

    default:
      sw_state3 = WAIT_FOR_PRESS;
    }
  }
}
