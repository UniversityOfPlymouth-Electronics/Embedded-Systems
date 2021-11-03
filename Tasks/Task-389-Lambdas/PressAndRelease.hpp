#include "mbed.h"

class PressAndRelease {
private:
    typedef enum {BTN_PRESS=1, BTN_RELEASE=2} ISR_EVENT;
    Thread t1;
    InterruptIn button;

    void handler() 
    {
        while (true) {
            ThisThread::flags_wait_all(BTN_PRESS);
            button.rise(NULL);
            onPress();      //Call back

            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_PRESS);
            button.fall( [&]() { t1.flags_set(BTN_RELEASE); } );

            ThisThread::flags_wait_all(BTN_RELEASE);
            button.fall(NULL);
            onRelease();    //Call back

            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_RELEASE);
            button.rise( [&]() { t1.flags_set(BTN_PRESS); } );
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
        button.rise( [&]() { t1.flags_set(BTN_PRESS); } );
    }

    Thread& getThread() {
        return t1;
    }
};