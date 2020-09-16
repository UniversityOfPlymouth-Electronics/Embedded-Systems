#include "../lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#define WAIT_TIME_MS 1000 

BusOut lights(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);

LCD_16X2_DISPLAY lcd;

int main()
{
    lcd.puts("All On");
    lights = 0b111;
    wait_us(WAIT_TIME_MS * 1000);

    lcd.cls();
    lcd.puts("All Off");
    lights = 0b000;
    wait_us(WAIT_TIME_MS * 1000);

    while (true)
    {
        wait_us(WAIT_TIME_MS * 1000);
    }
}