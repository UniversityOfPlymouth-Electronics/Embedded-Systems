#include "uop_msb.h"
using namespace uop_msb;

#include "string.h"
#include <stdio.h>
#include <ctype.h>
#include "sample_hardware.hpp"

#define SWITCH1_RELEASE 1

void thread1();
void thread2();
void switchISR();


//Threads
Thread t1;

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
// MemoryPool<message_t, 16> mpool;

//Message queue - matched to the memory pool
// Queue<message_t, 16> queue;

Mail<message_t, 16> mail_box;

// Call this on precise intervals
void switchISR() {
    
    //Read sample - make a copy
    float sample = 0.01f*(float)(rand() % 100);

    //Grab switch state
    uint32_t switch1State = buttonA;
    uint32_t switch2State = buttonB;
    
    //Allocate a block from the memory pool (non blocking version)
    //For a thread context, there is also a blocking version (with timeout)
    message_t* message = mail_box.try_alloc();
    if (message == NULL) {
        //Out of memory
        redLED = 1;
        return;   
    }
    
    //Fill in the data
    message->fValue   = sample;
    message->sw1State = switch1State;
    message->sw2State = switch2State;
    
    //Write pointer to the queue
    osStatus stat = mail_box.put(message);    //Note we are sending the "pointer" not the data
    
    /*
    typedef enum {
    osOK                      =  0,         ///< Operation completed successfully.
    osError                   = -1,         ///< Unspecified RTOS error: run-time error but no other error message fits.
    osErrorTimeout            = -2,         ///< Operation not completed within the timeout period.
    osErrorResource           = -3,         ///< Resource not available.
    osErrorParameter          = -4,         ///< Parameter error.
    osErrorNoMemory           = -5,         ///< System is out of memory: it was impossible to allocate or reserve memory for the operation.
    osErrorISR                = -6,         ///< Not allowed in ISR context: the function cannot be called from interrupt service routines.
    osStatusReserved          = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
    } osStatus_t;
    */

    //Check if succesful
    if (stat != osOK) {
        redLED = 1; 
        printf("mail_box.put() Error code: %4Xh, Resource not available\r\n", stat);   
        mail_box.free(message);
        return;
    }
}

//Normal priority thread (consumer)
void thread1() 
{      
    while (true) {
        message_t* payload;

        //Block on the queue
        payload = mail_box.try_get();
        
        //Also consider this
        //payload = mail_box.try_get_for(10s);

        //Check status
        if (payload) {
            //Make a copy
            message_t msg(payload->fValue, payload->sw1State, payload->sw2State);
            //We are done with this, so give back the memory to the pool
            mail_box.free(payload);
            
            //Echo to the terminal
            printf("Float Value: %.2f\t",    msg.fValue);
            printf("SW1: %u\t",              msg.sw1State);
            printf("SW2: %u\n\r",            msg.sw2State);
        } else {
            //ERROR HANDLER TO BE DONE

        }
             
    } //end while
}


// Main thread
int main() {
    redLED    = 0;
    yellowLED = 0;
    greenLED  = 0;
           
    //Start message
    printf("Welcome\n");           
   
    //Hook up interrupts   
    Ticker timer; 
    timer.attach(&switchISR, 100ms);
               
    //Threads
    t1.start(thread1);
    
    printf("Main Thread\n");
    while (true) {
        ThisThread::sleep_for(5s);
        puts("Main Thread Alive");
    }
}