#include "uop_msb.h"
#include <chrono>
using namespace uop_msb;
extern int getAverageDelay(double alpha);

AnalogIn pot(AN_POT_PIN);
DigitalOut redLED(TRAF_RED1_PIN);
LCD_16X2_DISPLAY disp;
PwmOut dispBackLight(LCD_BKL_PIN);

int main()
{
    //Configure the PWM for the backlight 
    dispBackLight.period(0.001f);   // 1ms
    dispBackLight.write(1.0);       // 100% duty

    //Update display
    disp.cls();
    disp.printf("PwmOut");

    //Implement a delay (BLOCKING)
    wait_us(2000000);

    //Update display
    disp.locate(1, 0);
    disp.printf("Turn the POT");

    //Implement another delay (BLOCKING)
    wait_us(2000000);

    //Timer for the pot
    Timer tmr;
    tmr.start();

    while(true) {
        
        //Once every 100ms, re-read the POT and update the duty
        if (tmr.elapsed_time() >= 250ms) {
            float u = pot;              // Every 250ms, read the pot... 
            dispBackLight.write(u);     // ... and update the brightness.
            tmr.reset();
        }
        
        //Other non-blocking code could go here
        
    }

}




