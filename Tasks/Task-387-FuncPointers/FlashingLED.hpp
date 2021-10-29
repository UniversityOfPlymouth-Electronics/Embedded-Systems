#ifndef __FLASHING_LED_HPP__
#define __FLASHING_LED_HPP__
#include "mbed.h"

class FlashingLED {
    private:
    DigitalOut led;
    Thread t;

    private:
    void flash()
    {
        while(true) {
            led = !led;
            ThisThread::sleep_for(500ms);
        }
    }

    public:
    FlashingLED(PinName pin) : led(pin)
    {
        t.start(callback(this, &FlashingLED::flash));
    }

};

#endif