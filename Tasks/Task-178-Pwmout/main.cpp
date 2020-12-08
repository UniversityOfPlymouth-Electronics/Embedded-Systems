#include "../lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;
extern int getAverageDelay(double alpha);

AnalogIn pot(AN_POT_PIN);
DigitalOut redLED(TRAF_RED1_PIN);
LCD_16X2_DISPLAY disp;
PwmOut dispBackLight(LCD_BKL_PIN);

int main()
{
    //Configure the PWM for the backlight 
    dispBackLight.period(0.001f);
    dispBackLight.write(1.0);

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
            float u = pot;
            dispBackLight.write(u);
            tmr.reset();
        }
        
        //Other code here

    }

}




