#pragma once
#include "mbed.h"
extern DigitalOut red_led;     //CountUp is in its critical section
extern DigitalOut yellow_led;  //CountDown is in its critical section
extern DigitalOut green_led;   //counter != 0
extern DigitalOut onboardLED;

extern DigitalIn button;
extern DigitalIn sw1;
extern DigitalIn sw2;