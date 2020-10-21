#ifndef __TRAFFICLIGHT__
#define __TRAFFICLIGHT__

#include "mbed.h"
using namespace chrono;

#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

class TrafficLight 
{
    private:
    DigitalOut redLED;
    DigitalOut yellowLED;
    DigitalOut greenLED;
    Ticker t;
    enum {STOP, READY, GO, WARNING} State;

    void yellowFlashISR() {
        yellowLED = !yellowLED;
    }

    void flashYellow(bool flash) {
        t.detach();
        if (flash) {
            t.attach(callback(this, &TrafficLight::yellowFlashISR), 200ms);
        }
    }

    void updateOutput()
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


    public:
    //Constructor
    TrafficLight(PinName redPin = TRAF_RED1_PIN, PinName yellowPin = TRAF_YEL1_PIN, PinName greenPin=TRAF_GRN1_PIN) 
                                                            : redLED(redPin,1), yellowLED(yellowPin,0), greenLED(greenPin,0)
    {
        flashYellow(false);
    }
    ~TrafficLight()
    {
        redLED = 1;
        yellowLED = 0;
        greenLED = 0;
    } 

    void nextState()
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
    } 

};


#endif