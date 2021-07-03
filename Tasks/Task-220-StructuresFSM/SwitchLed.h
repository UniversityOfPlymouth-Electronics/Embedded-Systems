#ifndef _SWITCH_LED_
#define _SWITCH_LED_

#include "../lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

typedef enum {
  WAIT_FOR_PRESS,
  WAITING_1,
  WAIT_FOR_REL,
  WAITING_2
} SWITCH_STATE;

typedef struct  {
    //Input states
    int switch_state = 0;   
    long long tmr_ms = 0;
    //Internal state
    SWITCH_STATE state = WAIT_FOR_PRESS;
    //Devices / outputs
    DigitalIn& sw;
    TimerCompat& tmr;
    DigitalOut& led;
} SwitchLedState;

extern void readInputs(SwitchLedState &context);
extern void updateState(SwitchLedState &context);

#endif
