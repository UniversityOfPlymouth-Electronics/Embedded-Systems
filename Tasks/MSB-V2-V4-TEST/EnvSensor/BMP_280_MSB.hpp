#ifndef MBED_BMP280_SPI_MSB_H
#define MBED_BMP280_SPI_MSB_H

// BMP280 Wrapper for Module Support Board
// Nicholas Outram

#include "mbed.h"
#include <cmath>
#include <optional>
#include "EnvSensor_t.hpp"
#include "BMP280_SPI/BMP280_SPI.h"
#include "LazyValueType.hpp"

#ifdef _DEBUG
extern Serial pc;
#define DEBUG_PRINT(...) pc.printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

class BMP280_SPI_MSB : public EnvSensor_t {
    protected:
    BMP280_SPI *bmp280 = NULL;
    SPI _spi;
    DigitalOut _cs;
    LazyValueType<bool> _present;

    public:
    /** Create a BMP280 instance
     *  which is connected to specified SPI pins
     *
     * @param mosi SPI MOSI pin
     * @param miso SPI MISO pin
     * @param sclk SPI SCLK pin
     * @param cs device CS pin
     */
    BMP280_SPI_MSB(PinName mosi, PinName miso, PinName sclk, PinName cs) : _spi(mosi, miso, sclk), _cs(cs)
    {
        if ( isPresent() ) {
            bmp280 = new BMP280_SPI(mosi, miso, sclk, cs);
        }
    }
    ~BMP280_SPI_MSB()
    {
        if (bmp280) {
            delete bmp280;
        }
    }

    float getTemperature(void) {
        return bmp280->getTemperature();
    }

    float getPressure(void) {
        return bmp280->getPressure();
    }

    float getHumidity(void) {
        return EnvSensor_t::getHumidity();
    }

    bool isPresent() {

        if (_present) {
            return true;
        }

        // Setup SPI
        _cs = 1;
        _spi.format(8, 0); // 8-bit, mode=0
        _spi.frequency(1000000); // 1MHZ

        //Check device ID
        _cs = 0;
        _spi.write(0xd0);        // command to read chip_id
        int cmd = _spi.write(0); // read chip_id
        _cs = 1;

        if (cmd == 0x58) {
            DEBUG_PRINT("BMP280 found\n");
            _present = true;
            return true;
        } else {
            DEBUG_PRINT("NO Environmental Sensor found!");
            _present = false;
            return false;
        }        
    }
};



#endif