#include "mbed.h"
#include "../lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

class SWPoll {
private:
    enum State {LOW, LOW_DEBOUNCE, HIGH, HIGH_DEBOUNCE};
    State state;        // Internal state
    DigitalIn sw;      // These are references (aliases) and MUST be initialised
    DigitalOut led;    // ""
    TimerCompat t;            // Each instance has it's own timer, so this is is finite
    
public:
    //Constructor - MUST be given two parameters (for the switch and led) BY REFERENCE
    SWPoll(PinName gpioInPin, PinName gpioOutIn) : sw(gpioInPin), led(gpioOutIn) {
        state = LOW;
        t.reset();
        led = 0;
    }    
    //Destructor - should the instance go out of scope, this is called
    ~SWPoll() {
        //Shut down
        t.stop();
        t.reset();
        led = 0;   
    }
    //The public API - poll the switches
    //Bascially, a mealy machine - uses a timer to manage switch bounce
    void poll() {
        switch (state) 
        {
        //Waiting for switch to rise:
        case LOW:
            if (sw == 1) {
                state = LOW_DEBOUNCE;
                t.reset();
                t.start();
            }
            break;
            
        case LOW_DEBOUNCE:
            if (t.read_ms() >= 200) {
                state = HIGH;
                t.stop();
                t.reset();    
            }
            break;
        
        case HIGH:
            if (sw == 0) {
                led = !led; //Toggle output on state transition  
                state = HIGH_DEBOUNCE;
                t.reset(); //(purely defensive)
                t.start();
            }
            break;
        case HIGH_DEBOUNCE:
            if (t.read_ms() >= 200) {
                state = LOW;
                t.stop();
                t.reset();  
            }
            break;            
         default:
            t.stop();
            t.reset();    
            state = LOW;
            break;
        }  //end switch
        
        //This is a Mealy Machine - so no output logic follows  
    }
};