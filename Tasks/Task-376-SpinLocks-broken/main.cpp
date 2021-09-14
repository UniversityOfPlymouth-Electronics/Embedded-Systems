#include "uop_msb.h"
#include <chrono>
using namespace uop_msb;

// #include "string.h"
// #include <stdio.h>
// #include <ctype.h>
#include "sample_hardware.hpp"


#define RED_DONE 1
#define YELLOW_DONE 2


//Function declarations
void countUP();
void countDOWN();
extern void spinlock(volatile int *arg);
extern void spinunlock(volatile int *arg);

//MUTEX Lock
Mutex countLock;
volatile int _spinLock = 1;

//Thread ID for the Main function (CMSIS API)
osThreadId tidMain;

//Stared mutable state
volatile int counter = 0;

// *************************************************************
// * TRY THIS WITH AND WITHOUT UNCOMMENTING THE FOLLOWING LINE *
// * Note the speed difference for this particular case.
// *************************************************************

#define SPIN

void inline increment()
{
  //**** Take lock ****
    #ifdef SPIN
    spinlock(&_spinLock); 
    #else
    countLock.lock();
    #endif
    
    counter++;
    
    //**** Release lock ****
    #ifdef SPIN
  spinunlock(&_spinLock);   
    #else
    countLock.unlock();
    #endif
}



void inline decrement()
{
  //**** Take lock ****
    #ifdef SPIN
    spinlock(&_spinLock); 
    #else
    countLock.lock();
    #endif
    
    counter--;
    
    //**** Release lock ****
    #ifdef SPIN
    spinunlock(&_spinLock);   
    #else
    countLock.unlock();
    #endif
}
//Threads
void countUP()
{
    redLED = 1;
    
    for (unsigned int n=0; n<100000; n++) {      
                increment();
                increment();
                increment();
                increment();
                increment();
                increment();
                increment();
                increment();
                increment();
                increment();            
    }
    
    redLED = 0;
    osSignalSet(tidMain, RED_DONE);  //Signal main thread we are done
}

void countDOWN()
{
    yellowLED = 1;
    
    for (unsigned int n=0; n<100000; n++) {      
                decrement();
                decrement();
                decrement();
                decrement();
                decrement();
                decrement();
                decrement();
                decrement();
                decrement();
                decrement();
    }   
        
    yellowLED = 0;    
    osSignalSet(tidMain, YELLOW_DONE); //Signal main thread we are done
}


//Main thread
int main() {
    post();
    
    //Threads
    Thread t1;
    Thread t2;
    tidMain = ThisThread::get_id(); 
    
    //Press the switch to run concurrently
    if (onBoardSwitch == 1) {
        printf("Running sequntially\n");
        countUP();
        countDOWN();        
    } else {
        printf("Running concurrently\n");
        t1.start(countUP); 
        wait_us(10);          
        t2.start(countDOWN);    
  
        //Wait for the ALL_ON signal
        ThisThread::flags_wait_all(RED_DONE | YELLOW_DONE);
        // Thread::signal_wait(RED_DONE,osWaitForever);
        // Thread::signal_wait(YELLOW_DONE,osWaitForever);        
    }

    printf("Final result = %d\n", counter);
    if (counter == 0) {
        greenLED = 0;
    }
        
    while(true);
}



   
