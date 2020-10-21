#include "TrafficLight.h"

void TrafficLight::yellowFlashISR() {
    yellowLED = !yellowLED;
}

void TrafficLight::flashYellow(bool flash) {
    t.detach();
    if (flash) {
        t.attach(callback(this, &TrafficLight::yellowFlashISR), 200ms);
    }
}

void TrafficLight::updateOutput()
{
    switch (State)
    {
        case STOP:
            flashYellow(false);
            redLED = 1;
            yellowLED = 0;
            greenLED = 0;
            break;
        case READY:
            flashYellow(false);
            redLED = 1;
            yellowLED = 1;
            greenLED = 0;
            break;
        case GO:
            flashYellow(false);
            redLED = 0;
            yellowLED = 0;
            greenLED = 1;
            break;
        case WARNING:
            redLED = 0;
            flashYellow(true);
            greenLED = 0;
            break;                
    }       
}

TrafficLight::LIGHT_STATE TrafficLight::nextState()
{
    // Update State
    switch (State)
    {
        case STOP:
            State = READY;
            break;
        case READY:
            State = GO;
            break;
        case GO:
            State = WARNING;
            break;
        case WARNING:
            State = STOP;
            break;
    }

    //As it says
    updateOutput();

    //Return the current state
    return State; 
} 