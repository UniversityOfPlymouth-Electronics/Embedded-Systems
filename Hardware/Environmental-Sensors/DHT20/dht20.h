#pragma once
#include "PinNames.h"
#include "mbed.h"

class DHT20 {
private:
    I2C _sensor;

public:
    DHT20(PinName SDA = ARDUINO_UNO_D14, PinName SCL = ARDUINO_UNO_D15) : _sensor(SDA,SCL)
    {
        
    }

};

