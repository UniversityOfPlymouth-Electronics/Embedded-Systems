#include "uop_msb.h"
#include <chrono>
#include <ratio>
using namespace uop_msb;
using namespace chrono;

class Flashy : DigitalOut {
    private:
    //Less composition in action here
    Ticker tick;
    //Internal state
    microseconds _interval;
    bool _enabled = false;

    void timerISR()  {
        //Call the baseclass version to toggle the GPIO
        DigitalOut::write(1-this->read());
    }

    void enable(bool en)
    {
        if (en == _enabled) return;

        if (en) {
            tick.attach(callback(this, &Flashy::timerISR), _interval);
        } else {
            tick.detach();
        }
        _enabled = en;
    }

    public:
    //Note how the base-class constructor is called first
    Flashy(PinName pin, microseconds t) : DigitalOut(pin), _interval(t) {
        enable(false);
    }
    //OVERLOAD constructor
    Flashy(PinName pin) : Flashy(pin, 500ms) {
    }
    ~Flashy() {
        this->write(0);
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
    void operator<<(microseconds t) {
        setInterval(t);
    }
    // void operator<<(bool en) {
    //     enable(en);
    // }
    Flashy& operator=(int u) {
        this->write(u);
        return *this;
    }

    //Override write
    void write(int value)
    {
        if (value == 0) {
            this->enable(false);
        } else {
            this->enable(true);
        }
        //Don't call the baseclass version!
    }

};

DigitalIn blueButton(USER_BUTTON);

int main()
{
    Flashy flashRed(TRAF_RED1_PIN, 125ms);
    Flashy flashYellow(TRAF_YEL1_PIN, 250ms);
    Flashy flashGreen(TRAF_GRN1_PIN);

    while (true) {
        flashRed    = 1;
        flashYellow = 1;
        flashGreen  = 1;
        wait_us(5000000);              //5 seconds
        flashRed    = 0;
        flashYellow = 0;
        flashGreen  = 0;
        wait_us(5000000);              //5 seconds

        if (blueButton == 1) {
            flashGreen << 50ms;
        } else {
            flashGreen << 500ms;
        }
    }
}



