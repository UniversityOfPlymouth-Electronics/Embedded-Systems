/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "uop_msb.h"
#include <iostream>
using namespace std;
using namespace uop_msb;

#include "PressAndRelease.hpp"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

Thread printingThread(osPriorityBelowNormal);
EventQueue printQueue;

int main()
{
    //Set up low priority serial terminal thread 
    printingThread.start([](){printQueue.dispatch_forever();});

    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    PressAndRelease b1(USER_BUTTON, []() {printQueue.call(printf, "BOING\n\r");});


    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
        printQueue.call(printf, "Welcome to ELEC350 and ELEC351 - you know you really love coding with threads now, or do you?\n\r");
    }
}
