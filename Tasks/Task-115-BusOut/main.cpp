#include "mbed.h"
#define WAIT_TIME_MS 1000 


// DigitalOut redLED(PC_2,1);
// DigitalOut yellowLED(PC_3,1);
// DigitalOut greenLED(PC_6,1);

BusOut lights (PC_2, PC_3, PC_6, PB_0, PB_7, PB_14);
//BusOut lights(PC_2, PC_3, PC_6, PB_0, PB_7, PB_14);

int main()
{
    //All OFF
    //lights = 0b000;
    lights = 0b111111;

    while (true)
    {
        int count = 0;
        while (count <= 63) // 1= red, 2=red and yellow, 3=red,yellow anfd red and yellow together,4=red, yellow,red, green 5=red,yellow, yell-red,green, gre-red
        {
            printf("count = %d\n", count);
            lights = count;
            wait_us(1000000);

            count = count + 1;
        }
    }
}