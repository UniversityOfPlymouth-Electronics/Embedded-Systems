#include "uop_msb.h"
using namespace uop_msb;

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

// main() runs in its own thread in the OS
LCD_16X2_DISPLAY lcd;
EnvSensor sensor;

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
        float t = sensor.getTemperature();
        float p = sensor.getPressure();
        lcd.cls();
        lcd.locate(0, 0);
        lcd.printf("Temp=%4.3f", t);
        lcd.locate(1, 0);
        lcd.printf("Pres=%4.3f", p);
    }
}

