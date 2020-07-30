#include "../lib/uopmsb/uop_msb_1_0_0.h"

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

// main() runs in its own thread in the OS
LCD_16X2_DISPLAY lcd;

int main()
{
    lcd.write(LCD_16X2_DISPLAY::DATA, 'X');
    lcd.write(LCD_16X2_DISPLAY::DATA, 'Y');
    lcd.character(1,1,'*');

    lcd.locate(1,5);
    lcd.printf("Hello");

    while (true) {
        led1 = !led1;
        wait_us(500000);
        lcd.write(LCD_16X2_DISPLAY::DATA, '1');
    }
}

