#include "uop_msb.h"
using namespace uop_msb;

Buzzer buzz;

PortOut LED_PORTE(PortE, LED_MASK);

DigitalOut LED_BAR_OE(LED_BAR_OE_PIN,1);      //Off by default
DigitalOut LED_DIGIT_OE(LED_DIGIT_OE_PIN,1);   //Off by default

DigitalOut LED_D1_LE(LED_D1_LE_PIN,0);
DigitalOut LED_D2_LE(LED_D2_LE_PIN,0);
DigitalOut LED_RED_LE(LED_RED_LE_PIN,0);
DigitalOut LED_GRN_LE(LED_GRN_LE_PIN,0);
DigitalOut LED_BLUE_LE(LED_BLUE_LE_PIN,0);

DigitalIn BlueButton(USER_BUTTON);

BusOut ledData(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN);

int main()
{
    // Buzzer
    buzz.playTone("C",Buzzer::HIGHER_OCTAVE);
    
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
    buzz.rest();


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