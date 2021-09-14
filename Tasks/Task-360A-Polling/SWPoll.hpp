#include "mbed.h"
#include "uop_msb.h"
using namespace uop_msb;

class SWPoll {
private:
    enum State {LOW, LOW_DEBOUNCE, HIGH, HIGH_DEBOUNCE};
    State state;        // Internal state
    DigitalIn sw;      // These are references (aliases) and MUST be initialised
    DigitalOut led;    // ""
    Timer tmr;         // Each instance has it's own timer, so this is is finite
    
public:
    //Constructor - MUST be given two parameters (for the switch and led) BY REFERENCE
    SWPoll(PinName gpioInPin, PinName gpioOutIn) : sw(gpioInPin), led(gpioOutIn) {
        state = LOW;
        tmr.reset();
        led = 0;
    }    
    //Destructor - should the instance go out of scope, this is called
    ~SWPoll() {
        //Shut down
        tmr.stop();
        tmr.reset();
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
                tmr.reset();
                tmr.start();
            }
            break;
            
        case LOW_DEBOUNCE:
            if (tmr.elapsed_time() >= 200ms) {
                state = HIGH;
                tmr.stop();
                tmr.reset();    
            }
            break;
        
        case HIGH:
            if (sw == 0) {
                led = !led; //Toggle output on state transition  
                state = HIGH_DEBOUNCE;
                tmr.reset(); //(purely defensive)
                tmr.start();
            }
            break;
        case HIGH_DEBOUNCE:
            if (tmr.elapsed_time() >= 200ms) {
                state = LOW;
                tmr.stop();
                tmr.reset();  
            }
            break;            
         default:
            tmr.stop();
            tmr.reset();    
            state = LOW;
            break;
        }  //end switch
        
        //This is a Mealy Machine - so no output logic follows  
    }
};