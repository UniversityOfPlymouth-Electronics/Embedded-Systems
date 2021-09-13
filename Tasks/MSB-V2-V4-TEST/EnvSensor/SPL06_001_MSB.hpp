#ifndef SPL06_001_MSB_H
#define SPL06_001_MSB_H

// BMP280 Wrapper for Module Support Board
// Nicholas Outram

#include "mbed.h"
#include "EnvSensor_t.hpp"
#include "SPL06-001/SPL06-001.h"

#ifdef _DEBUG
extern Serial pc;
#define DEBUG_PRINT(...) pc.printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

class SPL06_001_MSB : protected SPL06_001_SPI, public EnvSensor_t {
    public:
    /** Create a SPL06_001 instance
     *  which is connected to specified SPI pins
     *
     * @param mosi SPI MOSI pin
     * @param miso SPI MISO pin
     * @param sclk SPI SCLK pin
     * @param cs device CS pin
     */
    SPL06_001_MSB(PinName mosi, PinName miso, PinName sclk, PinName cs) : SPL06_001_SPI(mosi, miso, sclk, cs)
    {

    }
    void initialize(void) {
        SPL06_001_SPI::initialize();
    }

    float getTemperature(void) {
        return SPL06_001_SPI::getTemperature();
    }

    float getPressure(void) {
        return SPL06_001_SPI::getPressure();
    }

    float getHumidity(void) {
        return EnvSensor_t::getHumidity();
    }

    bool isPresent() {
        _cs = 1;                    // make sure SPI device not selected
        _spi.format(8, 0);          // 8-bit, mode=0
        _spi.frequency(1000000);    // 1MHZ

        //Check device ID
        _cs = 0;                    // Select Device nCS active low
        _spi.write(regs::ID | spi_mask::SPL06_001_SPI_READ);
        cmd[0] = _spi.write(0); // read
        _cs = 1;                    // Deselect Device nCS active low

        return (cmd[0] == 0x10);   
    }
};



#endif