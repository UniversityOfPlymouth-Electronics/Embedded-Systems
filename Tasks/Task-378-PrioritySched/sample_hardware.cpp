#include "mbed.h"
#include "sample_hardware.hpp"

#define RED_DONE 1
#define YELLOW_DONE 2

//Digital outputs
DigitalOut onBoardLED(LED1);
DigitalOut redLED(PE_15);
DigitalOut yellowLED(PB_10);
DigitalOut greenLED(PB_11);

//Inputs
DigitalIn  onBoardSwitch(USER_BUTTON);
DigitalIn  SW1(PE_12);
DigitalIn  SW2(PE_14);
//Serial pc(USBTX, USBRX);

//POWER ON SELF TEST
void post() 
{
    //POWER ON TEST (POT)
    puts("TASK 616 - ALL LEDs should be blinking");
    for (unsigned int n=0; n<10; n++) {
        redLED    = 1;
        yellowLED = 1;
        greenLED  = 1;
        wait(0.05);
        redLED    = 0;
        yellowLED = 0;
        greenLED  = 0;     
        wait(0.05);         
    }    
}