#include "mbed.h"
#include "uop_msb.h"
#include <chrono>
#include <iostream>
using namespace std;

class LedFlash {
    private:
    DigitalOut led;
    chrono::milliseconds delayTime;
    Thread thread;

    void doLedFlash() {
        while (true) {
            led = !led;
            ThisThread::sleep_for(delayTime);
        }
    }

    public:
    LedFlash(PinName ledPin, chrono::milliseconds t) : led(ledPin) {
        delayTime = t;
        thread.start(callback(this, &LedFlash::doLedFlash));
    }

};

int main() {

    LedFlash obj1(LED1, 200ms);
    LedFlash obj2(LED2, 300ms);
    LedFlash obj3(LED3, 500ms);
    while (true) {
        ThisThread::sleep_for(10s);
    }
    return 0;
}
