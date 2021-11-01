#ifndef __PUSHSWITCH_HPP__
#define __PUSHSWITCH_HPP__
#include "mbed.h"

class PushSwitch {

private:
    typedef enum {RISING_EVENT=1, FALLING_EVENT=2} SWITCH_EVENT;
    InterruptIn switchInterrupt;
    osThreadId_t threadID;

    void switchPressed() {
        switchInterrupt.rise(NULL);
        osSignalSet(threadID, RISING_EVENT);
    }
    void switchReleased() {
        switchInterrupt.fall(NULL);
        osSignalSet(threadID, FALLING_EVENT);
    }
    void switchChanged() {
        switchInterrupt.rise(NULL);
        switchInterrupt.fall(NULL);
        osSignalSet(threadID, RISING_EVENT | FALLING_EVENT);
    }
    
public:
    PushSwitch(PinName pin, PinMode mode = PinMode::PullDefault) : switchInterrupt(pin)
    {
       threadID = ThisThread::get_id();
       switchInterrupt.mode(mode);
    }
    ~PushSwitch() {
        switchInterrupt.rise(NULL);
        switchInterrupt.fall(NULL);
    }

    void waitForPress() {       
        switchInterrupt.rise(callback(this, &PushSwitch::switchPressed));
        ThisThread::flags_wait_any(RISING_EVENT);      
    }

    void waitForRelease() {       
        switchInterrupt.fall(callback(this, &PushSwitch::switchReleased));
        ThisThread::flags_wait_any(FALLING_EVENT);      
    }

    operator int() {
        switchInterrupt.rise(callback(this, &PushSwitch::switchChanged));
        switchInterrupt.fall(callback(this, &PushSwitch::switchChanged));
        ThisThread::flags_wait_any(RISING_EVENT | FALLING_EVENT); 
        return switchInterrupt.read();
    }
};
#endif