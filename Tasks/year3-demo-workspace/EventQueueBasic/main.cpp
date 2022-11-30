#include "uop_msb.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace uop_msb;
using namespace std;

#include "string.h"
#include <stdio.h>
#include <ctype.h>

#define SWITCH1_RELEASE 1

void thread1();
void thread2();
void switchISR();

//Threads
Thread t1;

//IO
DigitalOut led(LED1);

//Queues - "A message can be a integer or pointer value  to a certain type T that is sent to a thread or interrupt service routine."
Queue<uint32_t, 10> queue;

// Call this on precise intervals
void ISR() {

    //Random sample to send to other thread
    uint32_t sample = rand();
    bool succeeded = queue.try_put((unsigned int*)sample);
    if (!succeeded) {
        led = 1;
    }
}

//Normal priority thread (consumer)
void thread1() 
{    
    while (true) {

        //Threads can use stdout        
        cout << "Thread Waiting.." << endl;

        //Read queue - block (with timeout)
        uint32_t* rx;   // Fancy type for a 32-bit integer :)

        //Block and wait for data
        bool succeeded = queue.try_get_for(10s, &rx);
        if (!succeeded) {
            led = 1;
        }

        unsigned int data = (unsigned int)rx;

        //Confirm
        cout << "Thread unblocked with data " << data << endl;
        
    } //end while
}


// Main thread
int main() {

    //Start message
    printf("Welcome\n");
           
    //Hook up timer interrupt   
    Ticker timer; 
    timer.attach(&ISR, 1s);
               
    //Threads
    t1.start(thread1);
    
    printf("Main Thread\n");
    t1.join();
}
