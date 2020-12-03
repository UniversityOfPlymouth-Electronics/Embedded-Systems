#include "sample_hardware.hpp"

#define RED_DONE 1
#define YELLOW_DONE 2

//Digital outputs
DigitalOut onBoardLED(LED1);
DigitalOut redLED(TRAF_RED1_PIN);
DigitalOut yellowLED(TRAF_YEL1_PIN);
DigitalOut greenLED(TRAF_GRN1_PIN);

//Inputs
DigitalIn  onBoardSwitch(USER_BUTTON);
DigitalIn  SW1(BTN1_PIN);
DigitalIn  SW2(BTN2_PIN);
//Serial pc(USBTX, USBRX);

//POWER ON SELF TEST
void post() 
{
    //POWER ON TEST (POT)
    puts("ALL LEDs should be blinking");
    for (unsigned int n=0; n<10; n++) {
        redLED    = 1;
        yellowLED = 1;
        greenLED  = 1;
        wait_us(50000);
        redLED    = 0;
        yellowLED = 0;
        greenLED  = 0;     
        wait_us(50000);         
    }    
}