#include "mbed.h"
static DigitalOut led3(LED3);

static int incrementUpTo10(int u)
{
    return (u+1) % 10;
}

int flashSlowly(int d)
{
    static int count = 0;
    count = incrementUpTo10(count);

    if (count < d) {
        led3 = 1;
    } else {
        led3 = 0;
    }    

    return count;
}