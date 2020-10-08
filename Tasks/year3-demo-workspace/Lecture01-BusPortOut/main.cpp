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
    //ledData = 0xFF;

    //Wait
    wait_us(1000000);

    //Write pattern - least significant bit set to 1
    ledData = 0b00000001;
    wait_us(1000000);

    ledData = 0b00000010;
    wait_us(1000000);

    ledData = 0b00000100;
    wait_us(1000000);

    // most significant bit set to 1
    ledData = 0b10000000;
    wait_us(1000000);

    ledData = 0b11110000;
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