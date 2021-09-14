#include "mbed.h"
#include "SPL06-001.h"
#include "BMP280_SPI.h"


// main() runs in its own thread in the OS
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
            case 280:temperature=bmp280.getTemperature();pressure=bmp280.getTemperature();break;
            case 6:temperature=sensor.getTemperature();pressure=sensor.getTemperature();break;
            case -1:break;
            default:break;
        }

        printf("Temperature = %4.1f ",temperature);
        printf("Pressure = %4.1f\n\n",pressure);
        printf("hello %d\n",err);
        wait_us(1000000);
    }
}