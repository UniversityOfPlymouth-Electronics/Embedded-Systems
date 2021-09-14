#include "mbed.h"
#include "uop_msb.h"
#include "PushSwitch.hpp"
#include "FlashingLED.hpp"

using namespace uop_msb;

void task1();
void task2();
void blueISR_rise();
void buttonC_rise();
void buttonD_rise();


//Threads
Thread t1, t2;
osThreadId_t mainThreadID;

//Yellow LED
DigitalOut yellow_led(TRAF_YEL1_PIN);

//Interrupt
InterruptIn blueSwitch(USER_BUTTON);
InterruptIn buttonC(BTN3_PIN, PullDown);
InterruptIn buttonD(BTN4_PIN, PullDown);

#define TIMEOUT_MS 10000
int main() {   
    blueSwitch.rise(blueISR_rise);
    buttonC.rise(buttonC_rise);
    buttonD.rise(buttonD_rise);

    t1.start(task1);
    t2.start(task2);

    //Main is a thread - but there is no `Thread` object, so 
    //we use the C API 
    mainThreadID = ThisThread::get_id();

    while (true) {
        ThisThread::flags_wait_all(1 | 2);  // (1 | 2) => 3 
        printf("Buttons C and D have been pressed\n");
        ThisThread::sleep_for(50ms);    //Debounce
        ThisThread::flags_clear(1 | 2);     //Clear both flags
    }
}

void task1() 
{
    DigitalOut red_led(TRAF_RED1_PIN);  
    PushSwitch sw(BTN1_PIN);

    printf("Task 1 Waiting to start\n");
    ThisThread::flags_wait_any(4);
    printf("Task 2 starts\n");
    ThisThread::sleep_for(50ms);
    ThisThread::flags_clear(4); //Switch bounce can send multiples

    while(true) {

        sw.waitForPress();
        red_led = !red_led;

        // Signal thread 2
        t2.flags_set(1); //osSignalSet(t2.get_id(), 1);    
        ThisThread::sleep_for(50ms);

        sw.waitForRelease();
        ThisThread::sleep_for(50ms);

        //Wait for thread 2
        printf("Thread 1 waiting for signal\n");
        ThisThread::flags_wait_any(1);     
    }    
}

void task2() 
{
    DigitalOut green_led(TRAF_GRN1_PIN);  
    PushSwitch sw(BTN2_PIN);
    
    printf("Task 2 Waiting to start\n");
    ThisThread::flags_wait_any(4);
    printf("Task 2 starts\n");
    ThisThread::sleep_for(50ms);
    ThisThread::flags_clear(4); //Switch bounce can send multiples

    while(true) {

        //Wait for thread 1
        printf("Thread 2 waiting for signal\n");
        ThisThread::flags_wait_any(1); 

        sw.waitForPress();
        green_led = !green_led;

        // Signal thread 1 
        t1.flags_set(1);    //osSignalSet(t1.get_id(), 1);   
        ThisThread::sleep_for(50ms);

        sw.waitForRelease();
        ThisThread::sleep_for(50ms);
    }      
}

void blueISR_rise()
{
    blueSwitch.rise(NULL);
    yellow_led = !yellow_led;
    t1.flags_set(4);
    t2.flags_set(4);
}

void buttonC_rise()
{
    osSignalSet(mainThreadID, 1);
}

void buttonD_rise()
{
    osSignalSet(mainThreadID, 2);
}



