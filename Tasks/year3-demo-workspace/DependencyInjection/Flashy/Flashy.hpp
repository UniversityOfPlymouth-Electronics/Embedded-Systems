// Decoupling using composition
#ifndef __FLASHY__
#define __FLASHY__

#include "ITimer.hpp"
#include "ILightNotify.hpp"

class Flashy {
    protected:
    ITimer& _tmr;           //Reference to an object type ITimer
    ILightNotify& _light;   //Reference to an object type ILightNotify
    milliseconds  _rate;
    public:
    // Initialisation list set the private referenes - keeping a reference to the 
    Flashy(ITimer& tmr, ILightNotify& light, milliseconds rate) : _tmr(tmr), _light(light), _rate(rate) {
        _light.lightOff();
        _tmr.stop();
    }
    void flashOnce() {
        _light.lightOn();
        _tmr.start();
        _tmr.wait_for(_rate);
        _light.lightOff();
        _tmr.wait_for(_rate);       
        _tmr.stop();
    }
};

#endif