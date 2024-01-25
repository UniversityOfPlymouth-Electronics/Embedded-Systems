/**
 ******************************************************************************
 * @file    BMP280_SPI.cpp
 * @author  Toyomasa Watarai
 * @version V1.0.0
 * @date    8 Feb 2018
 * @brief   BMP280_SPI class implementation
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
 
#include "mbed.h"
#include "BMP280_SPI.h"

BMP280_SPI::BMP280_SPI(PinName mosi, PinName miso, PinName sclk, PinName cs)
    :
    _spi(mosi, miso, sclk),
    _cs(cs),
    t_fine(0)
{
    //initialize();
}


BMP280_SPI::~BMP280_SPI()
{
}

void BMP280_SPI::initialize()
{
    char cmd[18];

    _cs = 1;
    _spi.format(8, 0); // 8-bit, mode=0
    _spi.frequency(1000000); // 1MHZ

    _cs = 0;
    _spi.write(0xd0); // read chip_id
    cmd[0] = _spi.write(0); // read chip_id
    _cs = 1;
    
    DEBUG_PRINT("chip_id = 0x%x\n", cmd[0]);

    _cs = 0;
    _spi.write(0xf4 & BMP280_SPI_WRITE); // ctrl_meas
    _spi.write((3<<5) | (3<<2) | 3); // Temparature oversampling x4, Pressure oversampling x4, Normal mode
    _cs = 1;

    _cs = 0;
    _spi.write(0xf5 & BMP280_SPI_WRITE); // config
    _spi.write((5<<5) | (0<<2) | 0); // Standby 1000ms, Filter off, 4-wire SPI interface
    _cs = 1;

    wait_us(1000000);
    
    _cs = 0;
    _spi.write(0x88); // read dig_T regs
    for(int i = 0; i < 6; i++)
        cmd[i] = _spi.write(0);
    _cs = 1;

    dig_T1 = (cmd[1] << 8) | cmd[0];
    dig_T2 = (cmd[3] << 8) | cmd[2];
    dig_T3 = (cmd[5] << 8) | cmd[4];

    DEBUG_PRINT("dig_T = 0x%x, 0x%x, 0x%x\n", dig_T1, dig_T2, dig_T3);
    DEBUG_PRINT("dig_T = %d, %d, %d\n", dig_T1, dig_T2, dig_T3);

    _cs = 0;
    _spi.write(0x8e); // read dig_P regs
    for(int i = 0; i < 18; i++)
        cmd[i] = _spi.write(0);
    _cs = 1;

    dig_P1 = (cmd[ 1] << 8) | cmd[ 0];
    dig_P2 = (cmd[ 3] << 8) | cmd[ 2];
    dig_P3 = (cmd[ 5] << 8) | cmd[ 4];
    dig_P4 = (cmd[ 7] << 8) | cmd[ 6];
    dig_P5 = (cmd[ 9] << 8) | cmd[ 8];
    dig_P6 = (cmd[11] << 8) | cmd[10];
    dig_P7 = (cmd[13] << 8) | cmd[12];
    dig_P8 = (cmd[15] << 8) | cmd[14];
    dig_P9 = (cmd[17] << 8) | cmd[16];

    DEBUG_PRINT("dig_P = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9);
    DEBUG_PRINT("dig_P = %d, %d, %d, %d, %d, %d, %d, %d, %d\n", dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9);

}

float BMP280_SPI::getTemperature()
{
    int32_t temp_raw, var1, var2, temp;
    float tempf;
    char cmd[3];

    _cs = 0;
    _spi.write(0xfa);
    for(int i = 0; i < 3; i++)
        cmd[i] = _spi.write(0);
    _cs = 1;

    temp_raw = (cmd[0] << 12) | (cmd[1] << 4) | (cmd[2] >> 4);

    var1 = ((((temp_raw >> 3) - (dig_T1 << 1))) * dig_T2) >> 11;
    var2 = (((((temp_raw >> 4) - dig_T1) * ((temp_raw >> 4) - dig_T1)) >> 12) * dig_T3) >> 14;

    t_fine = var1 + var2;
    temp = (t_fine * 5 + 128) >> 8;
    tempf = (float)temp;

    return (tempf/100.0f);
}

float BMP280_SPI::getPressure()
{
    int32_t press_raw;
    float pressf;
    char cmd[3];

    _cs = 0;
    _spi.write(0xf7); // press_msb
    for(int i = 0; i < 3; i++)
        cmd[i] = _spi.write(0);
    _cs = 1;

    press_raw = (cmd[0] << 12) | (cmd[1] << 4) | (cmd[2] >> 4);

    int64_t var1, var2, p;
    uint32_t press;

    var1 = (int64_t)t_fine - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + ((int64_t)dig_P4 << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
    
    if (var1 == 0) {
        return 0;
    }
    p = 1048576 - press_raw;
    p = (((p<<31)-var2)*3125)/var1;
    var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);
    press = (uint32_t)p/256;

    pressf = (float)press;
    return (pressf/100.0f);
}

