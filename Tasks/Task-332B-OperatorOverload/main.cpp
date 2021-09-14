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

    //Operator overload
    void operator=(microseconds t) {
        setInterval(t);
    }
    void operator<<(bool en) {
        enable(en);
    }

};

DigitalIn blueButton(USER_BUTTON);

int main()
{
    Flashy flashRed(TRAF_RED1_PIN, 125ms);
    Flashy flashYellow(TRAF_YEL1_PIN, 250ms);
    Flashy flashGreen(TRAF_GRN1_PIN);

    while (true) {
        flashRed    << true;
        flashYellow << true;
        flashGreen  << true;
        wait_us(5000000);              //5 seconds
        flashRed    << false;
        flashYellow << false;
        flashGreen  << false;
        wait_us(5000000);              //5 seconds

        if (blueButton == 1) {
            flashGreen = 50ms;
        } else {
            flashGreen = 500ms;
        }
    }
}

