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

// Initialise the digital pin LED1 as an output
DigitalOut led1(LED1);
DigitalOut led2(LED2);

Thread printingThread(osPriorityBelowNormal);
EventQueue printQueue;

int main()
{
    //Set up low priority serial terminal thread 
    auto q = []() {
        printQueue.dispatch_forever();
    };
    printingThread.start(q);

    // PressAndRelease b1(USER_BUTTON, []() {printQueue.call(printf, "BOING\n\r");});

    auto callBack = []() {
        led2 = !led2;
        printQueue.call(printf, "BOING\n\r");
    };
    PressAndRelease b1(USER_BUTTON, callBack);

    while (true) {
        led1 = !led1;
        ThisThread::sleep_for(BLINKING_RATE);
        printQueue.call(printf, "Welcome to ELEC350 and ELEC351 - you know you really love coding with threads now, or do you?\n\r");
    }
}
