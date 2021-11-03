#include "mbed.h"
#include "uop_msb.h"
#include <iostream>
#include "PressAndRelease.hpp"

using namespace uop_msb;
using namespace std;

int main() {  
    //Event queue for main (normal priority thread)
    EventQueue mainQueue;

    //Setup a lower-priority event queue for printf statements
    EventQueue msgQueue;
    Thread t1(osPriorityBelowNormal);
    t1.start([&]() {msgQueue.dispatch_forever();});

    //Instantiate a couple DigitalOut objects for controlling LEDs 
    DigitalOut led1(LED1);
    DigitalOut led2(LED2);

    //Write closures for capturing the LEDs (by reference) and performing call-back operations
    auto lFuncApress = [&]() {
        led1 = 1;                                   
        msgQueue.call(printf, "Button A pressed\n");
    };
    auto lFuncArel = [&]() {
        led1 = 0;
    };    

    // Note that no DigitalOut type needs to be passed via the constructor.
    // It is all "captured" inside the two closures
    PressAndRelease btnA(BTN1_PIN, lFuncApress, lFuncArel);

    //Dispatch jobs on the main thread
    mainQueue.dispatch_forever();
}









