#ifndef __sample_hardware__
#define __sample_hardware__
#include "../lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

extern DigitalOut onBoardLED;
extern DigitalOut redLED;
extern DigitalOut yellowLED;
extern DigitalOut greenLED;

extern DigitalIn  onBoardSwitch;
extern DigitalIn  SW1;
extern DigitalIn  SW2;
//extern Serial pc;

extern void post();

#endif