#include "SwitchLed.h"

void readInputs(SwitchLedState &context)
{
    context.switch_state = context.sw.read();
    context.tmr_ms = context.tmr.read_ms();
}

void updateState(SwitchLedState &context) 
{
  switch (context.state) {

  case WAIT_FOR_PRESS:
    if (context.switch_state == 1) {
      context.state = WAITING_1;
      context.tmr.start();
      context.led = !context.led;
    }
    break;
  case WAITING_1:
    if (context.tmr_ms >= 300) {
      context.state = WAIT_FOR_REL;
      context.tmr.stop();
      context.tmr.reset();
    }
    break;

  case WAIT_FOR_REL:
    if (context.switch_state == 0) {
      context.state = WAITING_2;
      context.tmr.start();
    }
    break;
  case WAITING_2:
    if (context.tmr_ms >= 300) {
      context.state = WAIT_FOR_PRESS;
      context.tmr.stop();
      context.tmr.reset();
    }
    break;

  default:
    context.state = WAIT_FOR_PRESS;
  }
}