#include "uop_msb.h"
using namespace uop_msb;


AnalogIn pot(AN_POT_PIN);
LCD_16X2_DISPLAY disp;
DigitalOut dispBackLight(LCD_BKL_PIN,1);

extern void setLatch(uint8_t dat, char col);
extern void led_init(uint8_t dat, bool enabled=true);
extern void setLEDDisplayON(bool on);

int getAverageDelay(double alpha);
int getDelayMS();

uint8_t pattern_red[] =  {0,   1,  2,  4,  8,  16, 32, 64, 128,  0xFF};
uint8_t pattern_grn[] =  {0,   3,  6,  12, 24, 48, 96, 192, 128, 0xFF};
uint8_t pattern_blue[] = {128, 64, 32, 16, 8,  4,  2,  1,  0,    0xFF};
uint8_t idx = 0;


int main()
{
    printf("Functions demo\n");

    led_init(0x00);

    while(true) {
        
        //Get average delay value
        int delay_ms = getAverageDelay(0.95); 

        //Update display
        disp.cls();
        disp.printf("Delay: %dms", delay_ms);

        //Set the patterns
        setLatch(pattern_red[idx],  'r');
        setLatch(pattern_grn[idx],  'g');
        setLatch(pattern_blue[idx], 'b');
        idx++;
        if (idx == 10) {
            idx = 0;
        }

        //Turn LEDs ON
        setLEDDisplayON(true);

        //Wait
        wait_us(delay_ms*1000);

        //Turn LEDs OFF
        setLEDDisplayON(false);

        //Wait
        wait_us(delay_ms*1000);            
    }

}

int getDelayMS() 
{
    float p = pot; // 0 ... 1
    int delay = 100 + 900*p;    //100...1000ms
    return delay;
}


//Calculate average delay by filtering the potentiometer value
int getAverageDelay(double alpha)
{
    static double meanPotValue = (double)getDelayMS();  //Mean pot value

    for (unsigned int n=0; n<32; n++) {
        int potValue = getDelayMS();                    //Get raw value (with noise)
        meanPotValue = alpha*meanPotValue + (1.0-alpha)*potValue; //Handy forumula!
    }
    return (int)meanPotValue;
}


