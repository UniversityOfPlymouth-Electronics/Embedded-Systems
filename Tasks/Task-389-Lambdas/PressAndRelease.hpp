#include "mbed.h"

class PressAndRelease {
private:
    typedef enum {BTN_PRESS=1, BTN_RELEASE=2} ISR_EVENT;
    Thread t1;
    InterruptIn button;

    void button_rise() {
        t1.flags_set(BTN_PRESS);
    }

    void button_fall() {
        t1.flags_set(BTN_RELEASE);    
    }

    void handler() 
    {
        while (true) {
            ThisThread::flags_wait_all(BTN_PRESS);
            button.rise(NULL);
            onPress();      //Call back

            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_PRESS);
            button.fall(callback(this, &PressAndRelease::button_fall));

            ThisThread::flags_wait_all(BTN_RELEASE);
            button.fall(NULL);
            onRelease();    //Call back

            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_RELEASE);
            button.rise(callback(this, &PressAndRelease::button_rise));
        }
    }

    //Hooks into the button press and release events
    function<void()> onPress;
    function<void()> onRelease;

public:
    PressAndRelease(PinName buttonPin, function<void()> press = [](){},  function<void()> rel = [](){}) : 
        button(buttonPin), onPress(press), onRelease(rel)
    {
        t1.start(callback(this, &PressAndRelease::handler));
        button.rise(callback(this, &PressAndRelease::button_rise));  
    }

    Thread& getThread() {
        return t1;
    }
};