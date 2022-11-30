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
 
//Memory Pool - with capacity for 16 message_t types
MemoryPool<message_t, 16> mpool;

//Message queue - matched to the memory pool
Queue<message_t, 16> queue;

// Call this on precise intervals
void switchISR() {
    
    //Read sample - make a copy
    float sample = 0.01f*(float)(rand() % 100);

    //Grab switch state
    uint32_t switch1State = sw1;
    uint32_t switch2State = sw2;
    
    //Allocate a block from the memory pool (non blocking)
    //message_t* data = new message_t(sample, switch1State, switch2State);
    message_t* data = mpool.try_alloc();
    if (data == NULL) {
        led = 1;
        //reset
        system_reset();
    }

    //Fill in the data
    data->fValue = sample;
    data->sw1State = switch1State;
    data->sw2State = switch2State;
    
    //Write to queue
    bool ok = queue.try_put(data);
    
    //Check if succesful
    if (!ok) {
        led = 1;
        //reset
        system_reset();
    }
}

//Normal priority thread (consumer)
void thread1() 
{      
    while (true) {
        message_t* payload;

        //Block on the queue
        bool ok = queue.try_get_for(10s, &payload);

        //Check status
        if (!ok) {
            led = 1;
            system_reset();
        }

        //Make a copy
        message_t rx(payload->fValue, payload->sw1State, payload->sw2State);
        mpool.free(payload);

        //Display
        cout << rx.fValue << ", " << rx.sw1State << ", " << rx.sw2State << endl;
             
    } //end while
}


// Main thread
int main() {           
    //Start message
    printf("Welcome\n");           
   
    //Hook up interrupts   
    Ticker timer; 
    timer.attach(&switchISR, 100ms);
               
    //Threads
    t1.start(thread1);
    
    printf("Main Thread\n");
    t1.join();
}