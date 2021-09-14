#ifndef __sample_hardware__
#define __sample_hardware__
#include "uop_msb.h"
extern DigitalOut onBoardLED;
extern DigitalOut redLED;
extern DigitalOut yellowLED;
extern DigitalOut greenLED;

//Inputs
extern DigitalIn  onBoardSwitch;
extern DigitalIn  buttonA;
extern DigitalIn  buttonB;
//extern Serial pc;

extern void post();

#endif