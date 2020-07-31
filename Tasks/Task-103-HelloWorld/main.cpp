#include "../lib/uopmsb/uop_msb_1_0_0.h"
using namespace uop_msb_100;

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);
LCD_16X2_DISPLAY lcd;

int main()
{
    // Write to serial terminal on host PC
    printf("Hello World\n");

    // Write to LCD using the LCD_16X2_DISPLAY driver class
    lcd.printf("Hello World");
    lcd.locate(1, 0);   //Row 1, Col 0
    lcd.printf("ELEC143");

    // printf can do a lot more
    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (true)
    {
        led1 = !led1;
        wait_us(WAIT_TIME_MS * 1000);
    }
}
