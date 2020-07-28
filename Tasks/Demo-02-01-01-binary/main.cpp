#include "setup_demo.h"

int main()
{

    /********
     LED BAR
    *********/
    setup_hardware();
    
    //Red Bar
    EnableRedLEDs();

    //Write pattern
    ledData = 0b11111111;

    //Wait
    wait_us(1000000);

    //Write pattern
    ledData = 0b11110000;

    //Wait
    wait_us(1000000);

    //Green Bar
    EnableGreenLEDs();
    ledData = 0b11001100;  

    //Blue Bar
    EnableBlueLEDs();
    ledData = 0b10100101;

    //Wait forever
    while (true);
}