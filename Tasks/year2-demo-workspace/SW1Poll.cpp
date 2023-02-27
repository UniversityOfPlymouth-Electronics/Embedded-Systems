#include "SW1Poll.hpp"

//Change this to pick the LED and Switch
#define sw sw1
#define led red_led

//This is private to this file
enum State {LOW, LOW_DEBOUNCE, HIGH, HIGH_DEBOUNCE};
static State state;        // Internal state
static Timer t;            // Each instance has it's own timer, so this is is finite

//PUBLIC APIs
void sw1Controller_init()
{
    state = LOW;
    t.reset();
    led = 0;
}

//THIS IS REPETETIVE AND NOT BEST PRACTISE BUT I'VE HELD BACK TO MAINTAIN CLARITY

//The public API - poll the switches
//Bascially, a mealy machine - uses a timer to manage switch bounce
//Must be called rapidly
void sw1FSM()
{
    switch (state) {
            //Waiting for switch to rise:
        case LOW:
            if (sw == 1) {
                state = LOW_DEBOUNCE;
                t.reset();
                t.start();
            }
            break;

        case LOW_DEBOUNCE:
            if (t.elapsed_time() >= 200ms) {
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
            if (t.elapsed_time() >= 200ms) {
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