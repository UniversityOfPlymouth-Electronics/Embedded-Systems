#include "../lib/uopmsb/uop_msb_1_0_0.h"
using namespace uop_msb_100;

#define WAIT_TIME_MS 500 

DigitalOut red(TRAFFIC1_RED_PIN,1);         //Note the initial state
DigitalOut amber(TRAFFIC1_YELL_PIN,0);
DigitalOut green(TRAFFIC1_GRN_PIN,0);

LCD_16X2_DISPLAY lcd;

int main()
{
    lcd.puts("RED");
    wait_us(1000000);

    amber = 1;
    lcd.cls();
    lcd.puts("Amber");
    wait_us(1000000);

    green = 1;
    lcd.cls();
    lcd.puts("Green");    
    wait_us(1000000);

    lcd.cls();
    lcd.puts("TASK-104");

    while (true)
    {
        red = !red;
        amber = !amber;
        green = !green;
        wait_us(WAIT_TIME_MS * 1000);
    }
}
