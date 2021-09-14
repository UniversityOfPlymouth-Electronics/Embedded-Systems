#include "uop_msb.h"
#include "CanBeEnabled.hpp"
#include <chrono>
#include <cstdint>
#include <ratio>

using namespace uop_msb;
using namespace chrono;

// This class now inherits TWO parent classes
class Flashy : public DigitalOut, public CanBeEnabled {
    private:
        static uint32_t count;
    protected:
    //Less composition in action here
    Ticker tick;
    //Internal state
    microseconds _interval;

    //Can be overridden!
    virtual void timerISR()  {
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
        std::cout << "Flashy Constructor: call number->" << ++count << std::endl;
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


    // TODO: Uncomment this code
    // virtual void displayStatus() {
    //     if (this->isEnabled()) {
    //         cout << "Flashy is enabled" << endl;
    //     }
    // }
};

class Flickery : public Flashy {
    private:
        static uint32_t count;
    protected:
    
    virtual void timerISR()  {
        // Call the baseclass version to flicker the GPIO
        // Not nice this
        int r = rand();
        if ((r % 4) == 0) {
            DigitalOut::write(1-this->read());
        }        
    } 

    public:
        Flickery(PinName p, microseconds t) : Flashy(p, t) { 
            std::cout << "Flickery Constructor: call number->" << ++count << std::endl;
        }

        Flickery& operator=(int val) {
            Flashy::operator=(val);
            return *this;
        }

    // TODO: Uncomment this code
    // virtual void displayStatus() {
    //     if (this->isEnabled()) {
    //         cout << "Flickery is enabled but a bit dodgy :)" << endl;
    //     }
    // }        

};

//Instantiate the static members
uint32_t Flashy::count = 0;
uint32_t Flickery::count = 0;

DigitalIn blueButton(USER_BUTTON);

int main()
{
    Flickery flashRed(TRAF_RED1_PIN, 250ms); 
    Flashy flashYellow(TRAF_YEL1_PIN, 250ms);
    Flashy flashGreen(TRAF_GRN1_PIN);

    while (true) {
        flashRed    = 1;
        flashYellow = 1;
        flashGreen  = 1;

        flashRed.displayStatus();
        flashYellow.displayStatus();
        flashGreen.displayStatus();

        wait_us(5000000);              //5 seconds
        flashRed    = 0;
        flashYellow = 0;
        flashGreen  = 0;

        flashRed.displayStatus();
        flashYellow.displayStatus();
        flashGreen.displayStatus();

        wait_us(5000000);              //5 seconds
    }
}



