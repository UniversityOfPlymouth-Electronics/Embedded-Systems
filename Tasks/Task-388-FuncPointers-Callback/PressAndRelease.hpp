#include "mbed.h"

class PressAndRelease {
private:
    typedef enum {BTN_PRESS=1, BTN_RELEASE=2} ISR_EVENT;
    typedef void(*funcPointer_t)(void);
    
    //Composition
    Thread t1;                              
    InterruptIn button;                     

    // ISR for rising edge
    void button_rise() {
        t1.flags_set(BTN_PRESS);
    }

    // ISR for falling edge
    void button_fall() {
        t1.flags_set(BTN_RELEASE);    
    }

    // Main thread loop that handles all the events
    void handler() 
    {
        while (true) {
            ThisThread::flags_wait_all(BTN_PRESS);                          //Wait for ISR to signal, then unblock
            button.rise(NULL);                                              //Turn off interrupt 
            if (onPress) onPress();                                         //Callback (from this thread)
            ThisThread::sleep_for(50ms);                                    //Debounce
            ThisThread::flags_clear(BTN_PRESS);                             //Clear any additional signals (due to bounce)
            button.fall(callback(this, &PressAndRelease::button_fall));     //Enable ISR for switch release

            ThisThread::flags_wait_all(BTN_RELEASE);                    
            button.fall(NULL);
            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_RELEASE);
            button.rise(callback(this, &PressAndRelease::button_rise));     //Enable ISR for switch press
        }
    }
    //Hook into the button press
    void(*onPress)(void);                                                   //Member variable (function pointer)

public:
    PressAndRelease(PinName buttonPin, funcPointer_t press=NULL) : button(buttonPin), onPress(press) {
        t1.start(callback(this, &PressAndRelease::handler));
        button.rise(callback(this, &PressAndRelease::button_rise));  
    }
};

