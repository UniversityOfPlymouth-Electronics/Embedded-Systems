#include "../lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
using namespace uop_msb_200;

AnalogIn pot(AN_POT_PIN);
DigitalOut redLED(TRAF_RED1_PIN);
PwmOut dispBackLight(LCD_BKL_PIN);
LCD_16X2_DISPLAY disp;

extern int getAverageDelay(double alpha);

int main()
{
    //Update display
    disp.cls();
    disp.printf("PwmOut");
    dispBackLight = 1;

    //Implement a delay (BLOCKING)
    wait_us(2000000);

    //Update display
    disp.locate(1, 0);
    disp.printf("Turn the POT");

    //Implement another delay (BLOCKING)
    wait_us(2000000);

    //Get initial delay value
    float Ton = pot;

    //Configure the PWM
    dispBackLight.pulsewidth_us(500);
    dispBackLight.period_ms(1);

    //Timer for the pot
    Timer tmr;
    tmr.start();

    while(true) {
        
        //Once every 100ms, re-read the POT and update the duty
        if (tmr.elapsed_time() >= 100ms) {
            Ton = pot;
            dispBackLight.pulsewidth_us(1000*Ton);
            tmr.reset();
        }
        
        //Other code?

    }

}




