#include "uop_msb.h"
#include <chrono>
#include <cstdint>
using namespace uop_msb;
extern int getAverageDelay(double alpha);

AnalogIn pot(AN_POT_PIN);
DigitalOut redLED(TRAF_RED1_PIN);
DigitalOut lcdBackLight(LCD_BKL_PIN);

LCD_16X2_DISPLAY disp;
AnalogOut dac1(DAC1_AN_PIN);

int main()
{
    //Update display
    disp.cls();
    disp.printf("AnalogueOut");
    lcdBackLight = 1;

    //Implement a delay (BLOCKING)
    wait_us(2000000);

    //Update display
    disp.locate(1, 0);
    disp.printf("Attach the scope");

    //Implement another delay (BLOCKING)
    wait_us(2000000);

    //Timer for the pot
    Timer tmr;
    tmr.start();

    double Fs = 1000.0;
    double T = 1.0/Fs;
    double freq = 20.0;
    double DELTA = 2.0*3.1415926*freq*T;
    uint32_t n = 0;

    while(true) {
        
        //Once every 100ms, re-read the POT and update the duty
        if (tmr.elapsed_time() >= 1ms) {
            tmr.reset();

            //Write a value every 1ms
            double amplitude = pot;                     // Get amplitude from the POT
            dac1 = 0.5f + amplitude * 0.5f * cos(n*DELTA); // Calculate the cosine
            n = (n == 999) ? 0 : (n+1);
        }
        
        //Other non-blocking code could go here
        
    }

}




