#include "mbed.h"
#include <functional>

class PressAndRelease {
private:
    typedef enum {BTN_PRESS=1, BTN_RELEASE=2} ISR_EVENT;
    // typedef void(*funcPointer_t)(void);
    
    //Composition
    Thread t1;                              
    InterruptIn button;                     

    // ISR for rising edge
    void button_rise() {
        button.rise(NULL);
        t1.flags_set(BTN_PRESS);
    }

    // ISR for falling edge
    void button_fall() {
        button.fall(NULL);
        t1.flags_set(BTN_RELEASE);    
    }

    // Main thread loop that handles all the events
    void handler() 
    {
        while (true) {
            ThisThread::flags_wait_all(BTN_PRESS);                          //Wait for ISR to signal, then unblock

            if (onPress) onPress();                                         //Callback (from this thread)
            ThisThread::sleep_for(50ms);                                    //Debounce
            ThisThread::flags_clear(BTN_PRESS);                             //Clear any additional signals (due to bounce)
            button.fall(callback(this, &PressAndRelease::button_fall));     //Enable ISR for switch release

            ThisThread::flags_wait_all(BTN_RELEASE);                    
            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_RELEASE);
            button.rise(callback(this, &PressAndRelease::button_rise));     //Enable ISR for switch press
        }
    }
    //Hook into the button press
    function<void(void)> onPress;

public:
    PressAndRelease(PinName buttonPin, function<void(void)> press=NULL) : button(buttonPin), onPress(press) {
        t1.start(callback(this, &PressAndRelease::handler));
        button.rise(callback(this, &PressAndRelease::button_rise));  
    }

};

