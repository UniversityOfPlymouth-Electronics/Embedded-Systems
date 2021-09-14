#include "../../lib/uopmsb/uop_msb.h"
PortOut LED_PORTE(PortE, LED_MASK);

DigitalOut LED_BAR_OE(PE_0,1);      //Off by default
DigitalOut LED_DIGIT_OE(PE_15,1);   //Off by default

DigitalOut LED_D1_LE(PE_10,0);
DigitalOut LED_D2_LE(PE_11,0);
DigitalOut LED_RED_LE(PE_12,0);
DigitalOut LED_GRN_LE(PE_13,0);
DigitalOut LED_BLUE_LE(PE_14,0);

DigitalIn BlueButton(USER_BUTTON);

BusOut ledData(PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9);

void setup_hardware()
{
    LED_PORTE = LED_INIT; //LEDs enabled with data set to 0
    wait_us(1);
    LED_PORTE = LED_OFF;   //LEDs disabled
    wait_us(1);

    //Enable the LED Bar
    LED_BAR_OE = 0;

    //Disable the Digits
    LED_DIGIT_OE = 1;
}

void EnableRedLEDs()
{
    LED_BLUE_LE = 0;
    LED_GRN_LE = 0;
    LED_RED_LE = 1;
    wait_us(1);
    ledData = 0;
}

void EnableGreenLEDs()
{
    LED_BLUE_LE = 0;
    LED_RED_LE = 0;
    LED_GRN_LE = 1;
    wait_us(1);
    ledData = 0;
}

void EnableBlueLEDs()
{
    LED_GRN_LE = 0;
    LED_RED_LE = 0;
    LED_BLUE_LE = 1;    
    wait_us(1);
    ledData = 0;
}