#ifndef __ITIMER__
#define __ITIMER__

// Pure Abstract Class
#include <chrono>
using namespace std::chrono;

class ITimer {

    public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual milliseconds getTime_ms() = 0;
    virtual void wait_for(milliseconds t) = 0;
    protected:
    virtual void initialise() = 0;
};
#endif