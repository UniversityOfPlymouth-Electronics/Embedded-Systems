#include "mbed.h"
static DigitalIn BlueButton(USER_BUTTON);
static void waitForSwitchBounce();

void waitForButtonPress()
{
    while (BlueButton == 0);
    waitForSwitchBounce();
    while (BlueButton == 1);
    waitForSwitchBounce();
}

static void waitForSwitchBounce()
{
    wait_us(200000);
}