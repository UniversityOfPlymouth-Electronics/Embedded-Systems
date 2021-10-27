#include "mbed.h"
#include "uop_msb.h"
#include <iostream>
using namespace uop_msb;
using namespace std;

class PressAndRelease {
private:
    typedef enum {BTN_PRESS=1, BTN_RELEASE=2} ISR_EVENT;
    typedef const function<void()>& FUNC;
    Thread t1;
    InterruptIn button;
    DigitalOut gpioOutput;

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
            gpioOutput = 1;
            onPress();
            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_PRESS);
            button.fall(callback(this, &PressAndRelease::button_fall));

            ThisThread::flags_wait_all(BTN_RELEASE);
            button.fall(NULL);
            gpioOutput = 0;
            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_RELEASE);
            button.rise(callback(this, &PressAndRelease::button_rise));
        }
    }
    //Hook into the button press
    std::function<void()> onPress;

public:
    PressAndRelease(PinName buttonPin = BTN1_PIN, PinName ledPin = TRAF_RED1_PIN, FUNC press = [](){}) : button(buttonPin), gpioOutput(ledPin), onPress(press)
    {
        t1.start(callback(this, &PressAndRelease::handler));
        button.rise(callback(this, &PressAndRelease::button_rise));  
    }

    Thread& getThread() {
        return t1;
    }
};

int main() {  
    DigitalOut led1(LED1);
    DigitalOut led2(LED2);
    EventQueue ledFlashQueue;

    auto pA = [&]() {
        ledFlashQueue.call( [&](){ led1 = !led1; } );
    };
    auto pB = [&]() {
        led2 = !led2;
    };    

    PressAndRelease btnA(BTN1_PIN, TRAF_RED1_PIN, pA);
    PressAndRelease btnB(BTN2_PIN, TRAF_YEL1_PIN, pB);

    ledFlashQueue.dispatch_forever();
}









