/**
 ******************************************************************************
 * @file    SPL06-001.h
 * @author  Martin R Simpson
 * @version V1.0.0
 * @date    16 July 2021
 * @brief   This file contains the class of a SPL06-001 Digital pressure sensor library with SPI interface
 ******************************************************************************
 * @attention
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 
#ifndef SPL06_001_H
#define SPL06_001_H

#include "mbed.h"
//#define _DEBUG
#ifdef _DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
//now can use DEBUG_PRINT("Battle of Hastings was in %d\n",1066);
#else
#define DEBUG_PRINT(...)
#endif

/**  Interface for controlling Goertek-SPL06-001 temperature pressure sensor
 *
 * @code
 * #include "mbed.h"
 * #include "SPL06-001.h"
 *
 * SPL06_001_SPI sensor(PB_5, PB_4, PB_3, PB_2); // mosi, miso, sclk, cs
 *
 * int main() {
 *     while(1)
 *     {
 *         printf("%2.2f degC, %04.2f hPa\n", sensor.getTemperature(), sensor.getPressure());
 *         wait_us(1000000);
 *     }
 * }
 *
 * @endcode
 */

/** SPL06_001_SPI class
 *
 *  SPL06_001_SPI: A library to correct data using Goertek-SPL06-001 Temerature and Pressure sensor device
 *
 */
// SPL06-001 Register Mapping

class SPL06_001_SPI
{
public:

    enum spi_mask {
        SPL06_001_SPI_WRITE = 0x7F,     // Clear Bit 7 WRITE use AND &
        SPL06_001_SPI_READ = 0x80       // Set   Bit 7 READ  use OR  |
    };

    enum regs {
        PSR_B2  =  0x00,   // read concurrent 3 times MSB first and manipulate into one 24bit Word
        PSR_B1  =  0x01,
        PSR_B0  =  0x02,
        TMP_B2  =  0x03,   // read concurrent 3 times MSB first and manipulate into one 24bit Word
        TMP_B1  =  0x04,
        TMP_B0  =  0x05,
        PRS_CFG =  0x06,
        TMP_CFG  = 0x07,
        MEAS_CFG = 0x08,
        CFG_REG  = 0x09,
        INT_STS  = 0x0A,
        FIFO_STS = 0x0B,
        RESET    = 0x0C,
        ID       = 0x0D
    };

    enum coeff_regs {
        SPL06_001_c0_1  = 0x10,
        SPL06_001_c0_2  = 0x11,
        SPL06_001_c1_1  = 0x11,
        SPL06_001_c1_2  = 0x12,
        SPL06_001_c00_1 = 0x13,
        SPL06_001_c00_2 = 0x14,
        SPL06_001_c00_3 = 0x15,
        SPL06_001_c10_1 = 0x15,
        SPL06_001_c10_2 = 0x16,
        SPL06_001_c10_3 = 0x17,
        SPL06_001_c01_1 = 0x18,
        SPL06_001_c01_2 = 0x19,
        SPL06_001_c11_1 = 0x1A,
        SPL06_001_c11_2 = 0x1B,
        SPL06_001_c20_1 = 0x1C,
        SPL06_001_c20_2 = 0x1D,
        SPL06_001_c21_1 = 0x1E,
        SPL06_001_c21_2 = 0x1F,
        SPL06_001_c30_1 = 0x20,
        SPL06_001_c30_2 = 0x21
    };

    /** Create a SPL06_001 instance
     *  which is connected to specified SPI pins
     *
     * @param mosi SPI MOSI pin
     * @param miso SPI MISO pin
     * @param sclk SPI SCLK pin
     * @param cs device CS pin
     */
    SPL06_001_SPI(PinName mosi, PinName miso, PinName sclk, PinName cs);

    /** Destructor of SPL06_001_SPI
     */
    virtual ~SPL06_001_SPI();

    /** Initialize SPL06_001 sensor
     *
     *  Configure sensor setting and read parameters for calibration
     *
     */
    int initialize(void);

    /** Read the current temperature value (degree Celsius) from SPL06_001 sensor
     *
     * @return Temperature value (degree Celsius)
     */
    float getTemperature(void);

    /** Read the current pressure value (hectopascal) from SPL06_001 sensor
     *
     * @return Pressure value (hectopascal)
     */
    float getPressure(void);

private:
    SPI         _spi;
    DigitalOut  _cs;
    uint8_t cmd[15]={0};
    int32_t temp_raw=0, press_raw=0;
    int32_t kT = 524288;//675000;//524288;//7864320;//1572684;
    int32_t kP = 524288;//675000;//524288;//7864320;//1572684;
    int32_t c0, c1, c00, c10, c01, c11, c20, c21, c30;
    float tempf, temp_sc;
    float pressf, press_sc;
};

#endif // SPL06_001_H
