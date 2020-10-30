#include "mbed.h"
#include "SWPoll.hpp"

#define N 1000000
#define RELEASED 0
#define PRESSED  1

//Hardware objects
DigitalOut yellow_led(TRAF_YEL1_PIN);  //CountDown is in its critical section
SWPoll switch1(BTN1_PIN, TRAF_RED1_PIN);
SWPoll switch2(BTN2_PIN, TRAF_GRN1_PIN);

int main() {
    
    //Main uses a Timer
    yellow_led = 1;
    TimerCompat t;
        
    //Now loop forever
    t.start();
    while(1) { 
        //Flash the yellow on the "main thread"
        if (t.read_ms() >= 500) {
            yellow_led = !yellow_led;   
            t.reset(); 
        }
        switch1.poll();
        switch2.poll();
        
    };
}


