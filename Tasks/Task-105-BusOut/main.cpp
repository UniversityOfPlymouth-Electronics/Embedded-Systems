#include "../lib/uopmsb/uop_msb_1_0_0.h"
using namespace uop_msb_100;

#define WAIT_TIME_MS 500 

BusOut lights(TRAFFIC1_RED_PIN, TRAFFIC1_YELL_PIN, TRAFFIC1_GRN_PIN);

LCD_16X2_DISPLAY lcd;

int main()
{
    lcd.puts("All On");
    lights = 0b111;
    wait_us(1000000);

    lcd.cls();
    lcd.puts("All Off");
    lights = 0b000;
    wait_us(1000000);

    while (true)
    {
        wait_us(WAIT_TIME_MS * 1000);
    }
}