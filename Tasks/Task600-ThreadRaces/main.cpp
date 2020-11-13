#include "mbed.h"
void countUp();
void countDown();

#define N 1000000
#define RELEASED 0
#define PRESSED  1

//Hardware
DigitalOut red_led(PE_15);     //CountUp is in its critical section
DigitalOut yellow_led(PB_10);  //CountDown is in its critical section
DigitalOut green_led(PB_11);   //counter != 0
DigitalIn button(USER_BUTTON);

//Additional Threads
Thread t1;
Thread t2;

//Shared mutable state
volatile long long counter = 0; //Volatile means it must be stored in memory

//Increment the shared variable 
void countUp()
{
    //RED MEANS THE COUNT UP FUNCTION IS IN ITS CRITICAL SECTION
    red_led = 1;
    for (unsigned int n=0; n<N; n++) {
        counter++; 
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;           
    }  
    red_led = 0; 
    
}

//Decrement the shared variable
void countDown()
{
    //YELLOW MEANS THE COUNT DOWN FUNCTION IS IN ITS CRITICAL SECTION
    yellow_led = 1;
    for (unsigned int n=0; n<N; n++) {
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;           
    }
    yellow_led = 0;
          
}
int main() {
    
    green_led = 1;
    
    //Start competing threads
    t1.start(countUp);
    t2.start(countDown);
    
    //These threads DO exit, so let's wait for BOTH to finish
    t1.join();  //Wait for thread t1 to finish
    t2.join();  //Wait for thread t2 to finish
    
    //Did the counter end up at zero?
    if (counter == 0) {
        green_led = 0;   
    }
        
    //Now spin-lock for ever
    while(1) { 
        asm("nop");
    };
}

