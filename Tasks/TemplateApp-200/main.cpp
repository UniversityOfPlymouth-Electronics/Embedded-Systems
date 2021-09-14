//#include "mbed.h"
#include "uop_msb.h"
using namespace uop_msb;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        led1 = 1;
        led2 = 1;
        led3 = 1;
        wait_us(500000);
        led1 = 0;
        led2 = 0;
        led3 = 0;  
        wait_us(500000);    
    }
}

