#include "mbed.h"

PortOut lights(PortC, 0b0000000001001100);

int main()
{
    //All OFF
    //lights = 4; // work in C
    lights = 0b0000000000000100; // work in C++
    while (true)
    {
        lights = 0b0000000000000110;
        wait_us(1000000);
        lights = 0b0000000000001000;
        wait_us(1000000);
        lights = 0b0000000001000000;
        wait_us(1000000);                
    }
}