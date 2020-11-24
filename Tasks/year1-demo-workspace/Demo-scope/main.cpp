#include "mbed.h"
extern int flashSlowly(int);
extern void toggle();

int main()
{
    while (true) {
        toggle();

        wait_us(500000);
        
        flashSlowly(3);
    }

}

