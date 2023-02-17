#ifndef __MBEDLIGHT__
#define __MBEDLIGHT__

#include "uop_msb.h"
#include "ILightNotify.hpp"

class MbedLight : public ILightNotify {
    private:
    DigitalInOut _gpio;

    public:
    MbedLight(PinName pin, PinDirection direction=PinDirection::PIN_OUTPUT, PinMode mode=PushPullNoPull, int value=0) : _gpio(pin, direction, mode, value) {
        _gpio.output();
        _gpio.mode(mode);
        _gpio.write(value);
    }

    virtual void lightOn() { 
        _gpio.write(1); 
    };
    virtual void lightOff() { 
        _gpio.write(0); 
    };
    virtual bool lightStatus() { 
        return (_gpio.read() == 1) ? true : false; 
    };
};

#endif