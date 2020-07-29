/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../lib/uopmsb/uop_msb_1_0_0.h"
/* 
DigitalOut LCD_RS(PD_11);
DigitalOut LCD_E(PD_13);
DigitalOut LCD_RW(PD_12);
DigitalOut LCD_BKL(PD_14,0);
BusOut LCD_DATA(PD_0, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7);
*/

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

int main()
{   
    led1 = 1;

    while (true)
    {
        led1 = !led1;
        wait_us(500000);
    }
}
