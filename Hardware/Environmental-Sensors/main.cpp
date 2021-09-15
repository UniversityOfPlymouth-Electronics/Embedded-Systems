#include "mbed.h"
#include "SPL06-001.h"
#include "BMP280_SPI.h"

SPL06_001_SPI sensor(PB_5, PB_4, PB_3, PB_2); // mosi, miso, sclk, cs
BMP280_SPI bmp280(PB_5, PB_4, PB_3, PB_2); // mosi, miso, sclk, cs

//main() runs in its own thread in the OS
int main()
{
    int err=0, count=0;
    float temperature,pressure;
    
    err = sensor.initialize();
    DEBUG_PRINT("ERROR CODE IS %d\n",err);
    switch (err){
        case 280: sensor.~SPL06_001_SPI(); bmp280.initialize();printf("BMP280 found\n");break;      //BMP280 found so Destruct SPL06 driver and initialize BMP280 !!
        case   6: bmp280.~BMP280_SPI();sensor.initialize();printf("SPL06_001 found\n");break;                           //SPL06_001 found so Destruct BMP280
        case  -1: printf("No Environmental Sensor found!\n");break;            //None found
        default : break;                                 
    }

    while(true)
    {
        switch (err)
        {
            case 280:temperature=bmp280.getTemperature();pressure=bmp280.getPressure();break;
            case 6:temperature=sensor.getTemperature();pressure=sensor.getPressure();break;
            case -1:break;
            default:break;
        }

        printf("Temperature = %4.1f ",temperature);
        printf("Pressure = %4.1f\n",pressure);
        wait_us(5000000);
    }
}

/*
    int a;

    for (a=0; a < 5; a = a + 1) 
    {
        printf("a = %d\n",a);
    }

    printf("Final value of a is %d\n", a);
*/