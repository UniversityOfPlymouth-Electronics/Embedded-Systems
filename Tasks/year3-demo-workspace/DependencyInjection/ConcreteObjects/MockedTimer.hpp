#ifndef __MOCKEDTIMER__
#define __MOCKEDTIMER__
#include <iostream>
#include "ITimer.hpp"
#include <chrono>
using namespace std;

class MockedTimer : public ITimer {
    private:
    milliseconds _T;

    public:
    MockedTimer(milliseconds T = 1000ms) {
        _T = T;
    }

    virtual void start() {
        cout << "Timer Started" << endl;
    }

    virtual void stop() {
        cout << "Timer Stopped" << endl;
    }

    virtual milliseconds getTime_ms() {
        return _T;
    }

    virtual void wait_for(milliseconds t) {
        cout << "Timer Blocking" << endl;
        volatile unsigned long n;
        for (n=0; n<10000*t.count(); n++) {
            asm("nop");
        }
        cout << "Timer Unblocked" << endl;
    }
    
    protected:
    virtual void initialise() {

    }
};

#endif