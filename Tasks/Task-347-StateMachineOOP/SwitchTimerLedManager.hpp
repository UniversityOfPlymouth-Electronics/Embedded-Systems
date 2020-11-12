#include "mbed.h"
#include <chrono>
using namespace std::chrono;

class SwitchTimerLedManager {
public:
    typedef enum {DOWN=-1, UP=1} DIRECTION;

private:
    typedef enum {WAIT4PRESS, WAIT_RISING, WAIT4REL, WAIT_FALLING} STATE;
    DigitalIn  _switch;
    Timer _tmr;

    STATE _state;
    DIRECTION _dir;
    uint8_t _switchValue;
    microseconds _timerVal;

    int updateCount(int count)
    {
        int newCount = count + _dir;
        if ((newCount<0) || (newCount>99)) {
            return count;
        } else {
            return newCount;
        }
    }

protected:

public:

    SwitchTimerLedManager(PinName switchPin, DIRECTION dir) : _switch(switchPin), _dir(dir) {
        _state = WAIT4PRESS;
    }

    void readInputs() {
        _timerVal = _tmr.elapsed_time();
        _switchValue = _switch;
    }

    void updateState(int& count)
    {
        switch (_state) {
            case WAIT4PRESS:
            if (_switchValue == 1) {
                count = updateCount(count);
                _tmr.reset();
                _tmr.start();
                _state = WAIT_RISING;
            }
            break;

            case WAIT_RISING:
            if (_timerVal >= 50ms) {
                _tmr.stop();
                _state = WAIT4REL;
            }
            break;

            case WAIT4REL:
            if (_switchValue == 0) {
                _tmr.reset();
                _tmr.start();
                _state = WAIT_FALLING;
            }
            break;

            case WAIT_FALLING:
            if (_timerVal >= 50ms) {
                _tmr.stop();
                _state = WAIT4PRESS;
            }
            break;
        }
    }
    
};