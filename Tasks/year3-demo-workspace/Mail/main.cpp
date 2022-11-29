#include "uop_msb.h"
#include <iostream>
using namespace uop_msb;
using namespace std;

#include "string.h"
#include <stdio.h>
#include <ctype.h>
#define SWITCH1_RELEASE 1

void thread1();
void switchISR();


//Threads
Thread t1;

//IO
DigitalIn sw1(BTN1_PIN);
DigitalIn sw2(BTN2_PIN);
DigitalOut led(LED1);

//Class type
class message_t {
public:    
    float fValue;    
    int sw1State;
    int sw2State;
    
    //Constructor
    message_t(float f, int s1, int s2) {
        fValue = f;
        sw1State = s1;
        sw2State = s2;    
    }
};

EventQueue queue;

// Call this on precise intervals
void switchISR() {
    
    //Read sample - make a copy
    float sample = 0.01f*(float)(rand() % 100);

    //Grab switch state
    uint32_t switch1State = sw1;
    uint32_t switch2State = sw2;

    message_t data(sample, switch1State, switch2State);

    auto c1 = [=]() {
        cout << data.fValue << "," << data.sw1State << "," << data.sw2State << endl;
    };
    queue.call(c1);
}

//Normal priority thread (consumer)
void thread1() 
{      
    queue.dispatch_forever();
}

// Main thread
int main() {           
    //Start message
    printf("Welcome ELEC35X\n");           
   
    //Threads
    t1.start(thread1);

    ThisThread::sleep_for(1s);

    //Hook up interrupts   
    Ticker timer; 
    timer.attach(&switchISR, 100ms);
               
    printf("Main Thread\n");
    t1.join();
}