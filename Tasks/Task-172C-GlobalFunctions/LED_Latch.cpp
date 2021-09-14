#include "uop_msb.h"
using namespace uop_msb;

// LED Bar Display - all the hardware bits
BusOut dataBits(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN);
DigitalOut LED_BAR_OE(LED_BAR_OE_PIN,1);
DigitalOut LED_RED_LE(LED_RED_LE_PIN);
DigitalOut LED_GRN_LE(LED_GRN_LE_PIN);
DigitalOut LED_BLUE_LE(LED_BLUE_LE_PIN);

// Custom type for the Latch Enable (ON or OFF)
typedef enum {OFF=0, ON=1} LATCH_ENABLE_STATE;

// *********************
// FUNCTION DECLARATIONS
// *********************

// Set the state of all latch-enable pins
// u is either ON or OFF
void setAllLatches(LATCH_ENABLE_STATE u);

//Turn LED display on or off
// on should be true to turn the display on 
void setLEDDisplayON(bool on);

//Initialise the LED display
// dat is the initial data (ready for then the LEDs are enabled)
// enabled should be true to switch them on when initialised
void led_init(uint8_t dat, bool enabled);

//Set value of the output and latch
// dat is the 8-bit value to set
// col is the colour: 'r' for red, 'y' for yellow and 'g' for green
void setLatch(uint8_t dat, char col);

// ********************
// FUNCTION DEFINITIONS
// ********************

void setLatch(uint8_t dat, char col)
{
    //For safety
    setAllLatches(OFF);

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

void led_init(uint8_t dat, bool enabled=true)
{
    //Disable the LED outputs
    setLEDDisplayON(OFF);

    //Set data to initial value
    dataBits = dat;

    //Give a little time
    wait_us(1);

    //Enable all latches
    setAllLatches(ON);

    //Give a little time
    wait_us(1);

    //Disable all latches
    setAllLatches(OFF);

    if (enabled) {
        setLEDDisplayON(ON);
    }
}

void setAllLatches(LATCH_ENABLE_STATE u)
{
    LED_RED_LE = u;
    LED_GRN_LE = u;
    LED_BLUE_LE = u;
}

void setLEDDisplayON(bool on)
{
    if (on == true) {
        LED_BAR_OE = 0;
    } else {
        LED_BAR_OE = 1;
    }
}