#include "uop_msb.h"
#include <chrono>
using namespace uop_msb;

#include "PushSwitch.hpp"

Thread t1;
Thread t2;
Thread t3;

typedef struct {
    PinName pin;
    PinMode mode = PullDefault;
    Kernel::Clock::duration_u32 interval = 500ms;

} FlashyParam;

void FlashLED(PinName* p)
{
    PinName pin = *p;
    DigitalOut led(pin);
    while (true) {
        led = !led;
        ThisThread::sleep_for(500ms);
    }
}

void FlashLED2(FlashyParam* p)
{
    FlashyParam params = *p;
    DigitalInOut led(params.pin, PIN_OUTPUT, params.mode, 1);

    while (true) {
        led = !led;
        ThisThread::sleep_for(params.interval);
    }
}


int main(void)
{
    PinName redPin(TRAF_RED1_PIN);
    PinName yellowPin(TRAF_YEL1_PIN);
    t1.start(callback(FlashLED, &redPin));
    
    FlashyParam p1 = {.pin=TRAF_YEL2_PIN, .mode= PinMode::OpenDrainNoPull, .interval=250ms};
    t2.start(callback(FlashLED2, &p1));

    FlashyParam p2 = {.pin=TRAF_GRN1_PIN, .interval = 150ms};
    t3.start(callback(FlashLED2, &p2));

    t1.join();
}   