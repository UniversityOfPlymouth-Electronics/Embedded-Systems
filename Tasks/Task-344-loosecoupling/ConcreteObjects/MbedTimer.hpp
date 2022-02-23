
#ifndef __MBEDTIMER__
#define __MBEDTIMER__

#include "uop_msb.h"
#include "ITimer.hpp"

class MbedTimer : public ITimer {
    private:
    Timer _tmr;

    public:
    MbedTimer() {
        this->initialise();
    }
    virtual void start() {
        _tmr.start();
    }
    virtual void stop() {
        _tmr.stop();
    }
    virtual milliseconds getTime_ms() {
        return chrono::duration_cast<chrono::milliseconds>(_tmr.elapsed_time());
    }
    virtual void wait_for(milliseconds t) {
        _tmr.start();
        milliseconds t0 = getTime_ms();
        while ((getTime_ms()-t0) < t);
    }

    protected:
    virtual void initialise() {
        _tmr.stop();
        _tmr.reset();
    }
};

#endif