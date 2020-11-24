#include "mbed.h"

static DigitalOut led1(LED1);
static DigitalOut led2(LED2);

void toggle()
{
    led1 = !led1;
    led2 = !led2;
}