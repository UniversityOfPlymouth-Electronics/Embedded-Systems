#include "mbed.h"
#include "uop_msb.h"
#include <iostream>
#include "PressAndRelease.hpp"

using namespace uop_msb;
using namespace std;

//Globals
DigitalOut led1(LED1);
DigitalOut led2(LED2);

//Event queue for main
EventQueue mainQueue;

//Flash a given LED - parameter passed by reference
void flashLed(DigitalOut& led) {
    led = !led;
}
 
void flashLed1() {
    // This is NOT on the main thread
    flashLed(led1);                         
    //Dispatch printf on main thread
    mainQueue.call(printf, "Button A\n");    
}

void flashLed2() {
    flashLed(led2);     
    mainQueue.call(printf, "Button B\n");
}

int main() {  
    PressAndRelease btnA(BTN1_PIN, &flashLed1);
    PressAndRelease btnB(BTN2_PIN, &flashLed2);
    //Start main queue - dispatch
    mainQueue.dispatch_forever();
}









