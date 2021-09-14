#include "mbed.h"
#include "uop_msb.h"
#include "PushSwitch.hpp"
#include "FlashingLED.hpp"

using namespace uop_msb;

void task1();
void task2();

Thread t1, t2;

int main() {

    FlashingLED yellow(TRAF_YEL1_PIN);
    t1.start(task1);
    t2.start(task2);
    
    //t1.set_priority(osPriorityRealtime);  //Try this

    //Wait for t1 and t2 to end (which they never do)
    t1.join();
    t2.join();
}

// Version 1 - Partially uses a spinning technique
void task1() {
    DigitalOut red_led(TRAF_RED1_PIN);  
    DigitalIn sw1(BTN1_PIN);
    red_led = sw1;
    
    while(true) {
        while (sw1 == 0) {};            //BLOCKS via SPINNING
        ThisThread::sleep_for(50ms);    //Blocks in the WAITING state
        while (sw1 == 1) {};            //BLOCKS via SPINNING
        red_led = !red_led;             
        ThisThread::sleep_for(50ms);    //Blocks in the WAITING state
    }    
}

// Version 2 - uses a much more power-friendly ISR driven method
void task2() {
    DigitalOut green_led(TRAF_GRN1_PIN);
    PushSwitch button2(BTN2_PIN);

    printf("Waiting for switch B\n");
    green_led = button2;    //Blocks until there is a change
    printf("Unblocked - let's go\n");

    while(true) {
        button2.waitForPress();         //Blocks in the WAITING state 
        ThisThread::sleep_for(50ms);    //Blocks in the WAITING state
        button2.waitForRelease();       //Blocks in the WAITING state
        green_led = !green_led;         
        ThisThread::sleep_for(50ms);    //Blocks in the WAITING state
    }    
}
