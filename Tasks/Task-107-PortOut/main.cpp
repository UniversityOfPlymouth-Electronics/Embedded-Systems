#include "../uopmsb/uop_msb_1_0_0.h"

PwmOut Buzzer(BUZZER);

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

int main()
{
    // Buzzer
    Buzzer.period(0.001);   //1kHz
    Buzzer = 0.5;           //50% Duty
    
    /********
     LED BAR
    *********/
    LED_PORTE = LED_INIT; //LEDs enabled with data set to 0
    wait_us(1);
    LED_PORTE = LED_OFF;   //LEDs disabled
    wait_us(1);

    //Enable the LED Bar
    LED_BAR_OE = 0;
    
    //Red Bar
    ledData = 0b10101010;
    LED_RED_LE = 1;
    wait_us(1);
    LED_RED_LE = 0;
    wait_us(1);

    //Green Bar
    ledData = 0b11001100;
    LED_GRN_LE = 1;
    wait_us(1);
    LED_GRN_LE = 0;
    wait_us(1);    

    //Blue Bar
    ledData = 0b10100101;
    LED_BLUE_LE = 1;
    wait_us(1);
    LED_BLUE_LE = 0;
    wait_us(1); 

    /*****************************
     Enable the 7-Segment Displays
     *****************************/
    LED_DIGIT_OE = 0;
    wait_us(1);

    //Left Digit
    ledData = 0b01010101;
    LED_D1_LE = 1;
    wait_us(1);
    LED_D1_LE = 0;
    wait_us(1);

    //Right Digit
    ledData = 0b00101010;
    LED_D2_LE = 1;
    wait_us(1);
    LED_D2_LE = 0;
    wait_us(1);

    //Wait for the button press
    while (BlueButton == 0);
    Buzzer.suspend();


    volatile unsigned int pattern = 0b00000001;
    volatile unsigned int dot = 0;

    while (true) {
        ledData = pattern | dot;
        LED_D1_LE = 1; 
        wait_us(1);
        LED_D1_LE = 0; 
        wait_us(1);

        ledData = pattern | dot;
        LED_D2_LE = 1; 
        wait_us(1);
        LED_D2_LE = 0; 
        wait_us(1);

        wait_us(250000);

        //Toggle fullstop
        dot ^= 0b10000000;
        pattern <<= 1;

        //Recycle pattern
        if (pattern & 0b10000000) {
            pattern = 0b00000001;
        }
    }
}