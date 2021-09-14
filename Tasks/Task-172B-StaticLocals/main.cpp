#include "uop_msb.h"
using namespace uop_msb;

// LED Bar Display
BusOut dataBits(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN);
DigitalOut LED_BAR_OE(LED_BAR_OE_PIN,1);
DigitalOut LED_RED_LE(LED_RED_LE_PIN);
DigitalOut LED_GRN_LE(LED_GRN_LE_PIN);
DigitalOut LED_BLUE_LE(LED_BLUE_LE_PIN);
AnalogIn pot(AN_POT_PIN);
LCD_16X2_DISPLAY disp;
DigitalOut dispBackLight(LCD_BKL_PIN,1);

void setLatch(uint8_t dat, char col);
void led_init(uint8_t dat, bool enabled);
int getDelayMS();

uint8_t pattern_red[] =  {0,   1,  2,  4,  8,  16, 32, 64, 128,  0xFF};
uint8_t pattern_grn[] =  {0,   3,  6,  12, 24, 48, 96, 192, 128, 0xFF};
uint8_t pattern_blue[] = {128, 64, 32, 16, 8,  4,  2,  1,  0,    0xFF};
uint8_t idx = 0;

//Mean pot value
double meanPotValue = (double)getDelayMS();     // 2. Comment out this line

//Calculate average delay by filtering the potentiometer value
int getAverageDelay(double alpha)
{
    // static double meanPotValue = 0.0;        // 3. Uncomment this line
    for (unsigned int n=0; n<32; n++) {
        int potValue = getDelayMS();                    //Get raw value (with noise)
        meanPotValue = alpha*meanPotValue + (1.0-alpha)*potValue; //Handy forumula!
    }
    return (int)meanPotValue;
}

int main()
{
    printf("Functions demo\n");

    led_init(0x00, true);

    //Update the red
    setLatch(0,'r');

    //Update the green
    setLatch(0, 'g');

    //Update the blue
    setLatch(0, 'b');

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

        //Enable all the LED BAR Latch Outputs
        LED_BAR_OE = 0;

        //Wait
        wait_us(delay_ms*1000);

        //Disable the latch outputs
        LED_BAR_OE = 1;

        //Wait
        wait_us(delay_ms*1000);            
    }

}

void setLatch(uint8_t dat, char col)
{
    //For safety
    LED_RED_LE = 0;
    LED_GRN_LE = 0;
    LED_BLUE_LE = 0;

    //Now follow the sequence
    wait_us(1);
    dataBits = dat;    //Set the 8-bit data pattern
    wait_us(1);

    //Depending on the chosen colour
    switch (col)
    {
        case 'r':
            LED_RED_LE  = 1;    //Copy dataBits to red latch outputs
            wait_us(1);         
            LED_RED_LE  = 0;    //Ignore inputs (dataBits)
            break;
        case 'g':
            LED_GRN_LE  = 1;    //Copy dataBits to red latch outputs
            wait_us(1);         
            LED_GRN_LE  = 0;    //Ignore inputs (dataBits)
            break;
        case 'b':
            LED_BLUE_LE  = 1;    //Copy dataBits to red latch outputs
            wait_us(1);         
            LED_BLUE_LE  = 0;    //Ignore inputs (dataBits)
            break;
    }
    wait_us(1); 
}

void led_init(uint8_t dat, bool enabled)
{
    //Disable the LED outputs
    LED_BAR_OE = 1;

    //Set data to 0
    dataBits = dat;

    //Give a little time
    wait_us(1);

    //Enable all latches
    LED_RED_LE  = 1;
    LED_GRN_LE  = 1;
    LED_BLUE_LE  = 1;

    //Give a little time
    wait_us(1);

    //Enable all latches
    LED_RED_LE  = 0;
    LED_GRN_LE  = 0;
    LED_BLUE_LE  = 0;

    if (enabled) {
        LED_BAR_OE = 0;
    }
}

int getDelayMS() 
{
    float p = pot; // 0 ... 1
    int delay = 100 + 900*p;    //100...1000ms
    return delay;
}



