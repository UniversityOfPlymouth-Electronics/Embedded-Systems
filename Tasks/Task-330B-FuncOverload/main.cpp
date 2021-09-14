#include "uop_msb.h"
#include <chrono>
#include <ratio>
using namespace uop_msb;
using namespace chrono;

class Flashy {
    private:
    //Composition in action here
    DigitalOut led;
    Ticker tick;
    //Internal state
    microseconds _interval;
    PinName _pin;
    bool _enabled = false;

    void timerISR()  {
        led = !led;
    }

    void enable(bool en)
    {
        if (en == _enabled) return;

        if (en) {
            tick.attach(callback(this, &Flashy::timerISR), _interval);
        } else {
            tick.detach();
            led = 0;
        }
        _enabled = en;
    }

    public:
    Flashy(PinName pin, microseconds t) : led(pin,0), _pin(pin), _interval(t) {
        enable(false);
    }
    //OVERLOAD constructor
    Flashy(PinName pin) : Flashy(pin, 500ms) {
    }
    ~Flashy() {
        enable(false);
        led = 0;
    }

    //OVERLOAD private enable
    void enable() {
        enable(true);
    }

    void disable() {
        enable(false);
    }

    //Setter and getter for _inteval
    void setInterval(microseconds t) {
        _interval = t;
        if (_enabled) {
            //Reenable to force update
            disable();
            enable();
        }
    }
    microseconds getInterval() {
        return _interval;
    }
};

DigitalIn blueButton(USER_BUTTON);

int main()
{
    Flashy flashRed(TRAF_RED1_PIN, 125ms);
    Flashy flashYellow(TRAF_YEL1_PIN, 250ms);
    Flashy flashGreen(TRAF_GRN1_PIN);

    while (true) {
        flashRed.enable();
        flashYellow.enable();
        flashGreen.enable();
        wait_us(5000000);              //5 seconds
        flashRed.disable();
        flashYellow.disable();
        flashGreen.disable();
        wait_us(5000000);              //5 seconds

        if (blueButton == 1) {
            flashGreen.setInterval(50ms);
        } else {
            flashGreen.setInterval(500ms);
        }
    }
}

