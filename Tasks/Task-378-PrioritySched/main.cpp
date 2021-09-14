#include "uop_msb.h"
#include <chrono>
using namespace uop_msb;

#include "mbed.h"

#include "string.h"
#include <stdio.h>
#include <ctype.h>
#include "sample_hardware.hpp"

#define DELAY 200

Buzzer buzz;

//Thread ID for the Main function (CMSIS API)
osThreadId tidMain;

void thread1() 
{
    printf("Entering thread 1\n");
    while (true) {
        yellowLED = !yellowLED;
        ThisThread::sleep_for(200ms);   
    }
}

//This thread has higher priority
void thread2() 
{
    printf("Entering thread 2\n");  
    while (true) {
        redLED = !redLED;
        if (buttonA == 1) {          
            wait_us(200000); 
        } else {
            ThisThread::sleep_for(200ms);    
        }           
    }
}


//Main thread
int main() {
    post();

    printf("Press button A to use a spinning wait in thread 2\n");
    printf("Hold down button B to elevate thread 2 priority\n");

    //Main thread ID
    tidMain = ThisThread::get_id();  
    
    //Create a thread with normal priority
    Thread t1(osPriorityNormal);
    t1.start(thread1);
    
    // 2) Select the Thread Priority
    Thread t2(osPriorityNormal);
    t2.start(thread2);

    wait_us(100000);

    if (buttonB == 1) {
        printf("Thread 2 running with elevated priority\n");
        t2.set_priority(osPriorityAboveNormal);        
    } else {
        printf("Thread 2 running with same priority\n");
    }
    

    while (onBoardSwitch == 0) {
        printf("Main Thread checking in!\n");
        buzz.playTone("G");
        ThisThread::sleep_for(125ms);
        buzz.rest();
        ThisThread::sleep_for(2s);
    }

    while(true);

}

   




   
