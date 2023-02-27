#include "mbed.h"
#include "demo-self-test.hpp"
#include "SW1Poll.hpp"
#include "SW2Poll.hpp"

#define N 1000000
#define RELEASED 0
#define PRESSED  1

//Function prototypes
void task1();
void task2();

//Hardware objects
DigitalOut red_led(PE_15);     //CountUp is in its critical section
DigitalOut yellow_led(PB_10);  //CountDown is in its critical section
DigitalOut green_led(PB_11);   //counter != 0
DigitalOut onboardLED(LED1);

DigitalIn button(USER_BUTTON);
DigitalIn sw1(PE_12);
DigitalIn sw2(PE_14);


//LOOK AT SWPoll.hpp for the definition of the SWPoll class

int main() {
    POST();
    
    //Main uses a Timer
    yellow_led = 1;
    Timer t;
       
    //Initialise the state machines
    sw1Controller_init();
    sw2Controller_init();   
        
    //Now loop forever
    t.start();
    while(1) { 
        
        //Flash the yellow on the "main thread"
        if (t.read_ms() >= 500) {
            yellow_led = !yellow_led;   
            t.reset(); 
        }
        
        //Update state machines
        sw1FSM();
        sw2FSM();
        
    };
}


