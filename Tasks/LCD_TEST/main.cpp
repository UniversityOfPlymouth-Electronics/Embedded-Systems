#include "uop_msb.h"
using namespace uop_msb;

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

// main() runs in its own thread in the OS
LCD_16X2_DISPLAY lcd;
EnvSensor sensor(PB_5, PB_4, PB_3, PB_2);

int main()
{
    lcd.cls();
    lcd.write(LCD_16X2_DISPLAY::DATA, 'X');
    lcd.write(LCD_16X2_DISPLAY::DATA, 'Y');
    lcd.character(1,1,'*');

    lcd.locate(1,5);
    lcd.printf("Hello");
    wait_us(1000000);

    while (true) {
        led1 = !led1;
        wait_us(500000);
        lcd.write(LCD_16X2_DISPLAY::DATA, '1');
    }
}

