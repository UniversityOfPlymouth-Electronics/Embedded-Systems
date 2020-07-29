/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

//#include "mbed.h"
#include "../lib/uopmsb/uop_msb_1_0_0.h"
#include "TextLCD.h"

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

 TextLCD lcd(PD_11, PD_13, PD_4, PD_5, PD_6, PD_7); // rs, e, d4-d7

int main()
{
    puts("Hello World");
    lcd.printf("Hello World");

    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (true)
    {
        led1 = !led1;
        wait_us(WAIT_TIME_MS * 1000);
    }
}
