#include "uop_msb.h"
#include "SW1Poll.hpp"
#include "SW2Poll.hpp"

#define N 1000000
#define RELEASED 0
#define PRESSED  1

//Function prototypes
extern void sw1Controller_init();
extern void sw2Controller_init();   
extern void sw1FSM();
extern void sw2FSM();

void task1();
void task2();

//Hardware objects
DigitalOut red_led(TRAF_RED1_PIN);     
DigitalOut yellow_led(TRAF_YEL1_PIN);  
DigitalOut green_led(TRAF_GRN1_PIN);  
DigitalOut onboardLED(LED1);

DigitalIn button(USER_BUTTON);
DigitalIn sw1(BTN1_PIN);
DigitalIn sw2(BTN2_PIN);

// This project contains a lot of repetition.
// This is done to keep it as simple as possible.
// More elegant versions are presented in later tasks 
int main() {
    
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
        if (t.elapsed_time() >= 500ms) {
            yellow_led = !yellow_led;   
            t.reset(); 
        }
        
        //Update state machines
        sw1FSM();
        sw2FSM();
        
    };
}


