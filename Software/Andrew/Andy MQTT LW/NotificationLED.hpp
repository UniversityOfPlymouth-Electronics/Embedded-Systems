#include "mbed.h"
class NotificationLED{
    private: 
    DigitalOut led;
    Thread th;
    Semaphore sem;
    void thr(){
        while(1){
            sem.acquire();
            led=1;
            ThisThread::sleep_for(200ms);
            led=0;
            ThisThread::sleep_for(200ms);
        }
    }     


    public:
    NotificationLED(PinName led_pin) : led(led_pin){
        th.start(callback(this,&NotificationLED::thr));
    }

    void notify(){
        sem.release();
    }
};