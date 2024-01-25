/**
 ******************************************************************************
 * @file    SPL06-001.cpp
 * @author  Martin R Simpson
 * @version V1.0.0
 * @date    16 July 2018
 * @brief   SPL06_001_SPI class implementation
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
#include "SPL06-001.h"

SPL06_001_SPI::SPL06_001_SPI(PinName mosi, PinName miso, PinName sclk, PinName cs)
    :
    _spi(mosi, miso, sclk),
    _cs(cs,1)                  // Chip Select active LOW so assert HIGH ",1" on instantiation
{
    //initialize();
}


SPL06_001_SPI::~SPL06_001_SPI()
{
}

int SPL06_001_SPI::initialize()
{
    _cs = 1;                    // make sure SPI device not selected
    _spi.format(8, 0);          // 8-bit, mode=0
    _spi.frequency(1000000);    // 1MHZ

    _cs = 0;                    // Select Device nCS active low
        _spi.write(regs::ID | spi_mask::SPL06_001_SPI_READ);
        cmd[0] = _spi.write(0); // read
    _cs = 1;                    // Deselect Device nCS active low
    DEBUG_PRINT("\nchip_id = 0x%X\n", cmd[0]); // display ID in ID Reg at 0x04 content should be 0x10

    if (cmd[0] != 0x10) // if NOT SPL06_001 then do further checks else carry on initializing
    {
        _cs = 0;
            _spi.write(0xd0); // read chip_id
            cmd[0] = _spi.write(0); // read chip_id
        _cs = 1;
        if (cmd[0] == 0x58)
        {
            DEBUG_PRINT("BMP280 found\n");
            return 280;
        }
        else 
        {
            DEBUG_PRINT("NO Environmental Sensor found!");
            return -1;
        }
    
    }
    DEBUG_PRINT("SPL06_001 found\n");
    
    _cs = 0;                    // Select Device nCS active low
        _spi.write(regs::MEAS_CFG & spi_mask::SPL06_001_SPI_WRITE); // ctrl_meas register
        _spi.write(7);          // 7(111)== continuous Temp Press
    _cs = 1;                    // Deselect Device nCS active low

    _cs = 0;                    // Select Device nCS active low
        _spi.write(regs::CFG_REG & spi_mask::SPL06_001_SPI_WRITE); // config
        _spi.write(0);          // 4-wire SPI interface ---- No FIFO No Shift Bits 4 wires
    _cs = 1;                    // Deselect Device nCS active low

    _cs = 0;                    // Select Device nCS active low
        _spi.write(regs::TMP_CFG & spi_mask::SPL06_001_SPI_WRITE); // config
        _spi.write(0x80|0x30);  // Internal Sensor - 0x30 = 128 Measurement per second - Single Sample rate was 0x00
                                // 0x80 SET bit 7 see datasheet section 6.1 compare to section 8.4 case example works bit map is wrong - MRS 11/08/2021
    _cs = 1;                    // Deselect Device nCS active low

    _cs = 0;                    // Select Device nCS active low
        _spi.write(regs::PRS_CFG & spi_mask::SPL06_001_SPI_WRITE); // config
        _spi.write(0x00|0x30);       // Internal Sensor - 0x30 = 128 Measurement per second - Single Sample rate was 0x00
    _cs = 1;                    // Deselect Device nCS active low




    // NOW Poll the ctrl_measure register to ascertain when device is ready!!
   /* cmd[0]=0;                   //Reset contents as using asa condition for following while loop
    while (cmd[0]<0xF0){        // POLL Meas CFG register
        _cs = 0;                // Select Device nCS active low
            _spi.write(regs::MEAS_CFG & spi_mask::SPL06_001_SPI_READ); // ctrl_meas register
            cmd[0]=_spi.write(0);                                      // Receive response
            DEBUG_PRINT("\n MEAS CFG REG = 0x%X\n", cmd[0]);           // display ID in ID Reg at 0x04 content should be 0x10
        _cs = 1;                // Deselect Device nCS active low
        wait_us(1000000);
    }
    */
    wait_us(1000000); // wait 1 second for config removed since Polling see above!!
    return 6; //
}

// Member function will return a float in degrees Celcius
float SPL06_001_SPI::getTemperature()
{
    _cs = 0;
        _spi.write(coeff_regs::SPL06_001_c0_1|spi_mask::SPL06_001_SPI_READ);
        for(int i = 0; i < 3; i++){cmd[i] = _spi.write(0);} //Load the Coefficients into an array
    _cs = 1;

    DEBUG_PRINT("coefs c0 = 0x%02x, 0x%02x, and c1 = 0x%02x, 0x%02x\n", cmd[0],cmd[1],cmd[1],cmd[2]);
    if (cmd[0] >= 0x80){c0=0xfffff000;} else {c0=0x0000;}           // Convert 12 bit signed to 32bit signed
    c0 |= ((cmd[0]<<4) | (cmd[1]&0xf0)>>4);
    if ((cmd[1]&0x0f) >= 0x08){c1=0xfffff000;} else {c1=0x0000;}    // Convert 12 bit signed to 32bit signed
    c1 |= (((cmd[1]&0x0f)<<8) | (cmd[2]<<0));
    DEBUG_PRINT("coefs c0 = 0x%04x; %d, and c1 = 0x%04x; %d\n", c0, c0, c1, c1);

    _cs = 0;
        _spi.write(regs::TMP_B2|spi_mask::SPL06_001_SPI_READ);
        for(int i = 0; i < 3; i++){cmd[i] = _spi.write(0);}         // Load the Temperature Data into an array
    _cs = 1;

    if (cmd[0]>=0x80){temp_raw=0xff000000;} else {temp_raw=0x00000000;} //convert from 24 signed to 32 signed
    temp_raw |= ((cmd[0] << 16) | (cmd[1] << 8) | (cmd[2] << 0));

    DEBUG_PRINT("Raw Temperature is = 0x%02x 0x%02x 0x%02x :: 0x%08x; %d\n", cmd[0], cmd[1], cmd[2], temp_raw, temp_raw);
    temp_sc = (float)temp_raw/kT;               // Convert from RAW temperature to Scaled value using kT factor
    DEBUG_PRINT("Scaled factor Temperature is = %f\n\n", temp_sc);

    tempf = (float)c0*0.5f + (float)c1*temp_sc; // Temperature compensated value in degrees Celcius

    return tempf;
}

// Member function to return the Pressure value in hectopascals hPa (AKA mBar)
float SPL06_001_SPI::getPressure()
{
    _cs = 0;
        _spi.write(coeff_regs::SPL06_001_c00_1|spi_mask::SPL06_001_SPI_READ);
        for(int i = 0; i < 16; i++){cmd[i] = _spi.write(0);}        // Load the coefficients into an array
    _cs = 1;

    if (cmd[0]>=0x80){c00=0xfff00000;} else {c00=0x00000000;}       //convert from 24 signed to 32 signed
    c00 |= cmd[0]<<12 | cmd[1]<<4 | cmd[2]>>4;
    if ((cmd[2]&0xf)>=0x08){c10=0xfff00000;} else {c10=0x00000000;} //convert from 24 signed to 32 signed
    c10 |= (cmd[2]&0xf)<<16 | cmd[3]<<8 | cmd[4];
    if (cmd[5]>=0x80){c01=0xffff0000;} else {c01=0x00000000;}       //convert from 16 signed to 32 signed
    c01 |= cmd[5]<<8 | cmd[6];
    if (cmd[7]>=0x80){c11=0xffff0000;} else {c11=0x00000000;}       //convert from 16 signed to 32 signed
    c11 |= cmd[7]<<8 | cmd[8];
    if (cmd[9]>=0x80){c20=0xffff0000;} else {c20=0x00000000;}       //convert from 16 signed to 32 signed
    c20 |= cmd[9]<<8 | cmd[10];
    if (cmd[11]>=0x80){c21=0xffff0000;} else {c21=0x00000000;}      //convert from 16 signed to 32 signed
    c21 |= cmd[11]<<8 | cmd[12];
    if (cmd[13]>=0x80){c30=0xffff0000;} else {c30=0x00000000;}      //convert from 16 signed to 32 signed
    c30 |= cmd[13]<<8 | cmd[14];
    
    DEBUG_PRINT("Coefs lists\n");
    DEBUG_PRINT("c00 0x%x 0x%x 0x%x = 0x%x: %d\n",cmd[0],cmd[1],cmd[2],c00,c00);
    DEBUG_PRINT("c10 0x%x 0x%x 0x%x = 0x%x: %d\n",cmd[2],cmd[3],cmd[4],c10,c10);
    DEBUG_PRINT("c01 0x%x 0x%x = 0x%x: %d\n",cmd[5],cmd[6],c01,c01);
    DEBUG_PRINT("c11 0x%x 0x%x = 0x%x: %d\n",cmd[7],cmd[8],c11,c11);
    DEBUG_PRINT("c20 0x%x 0x%x = 0x%x: %d\n",cmd[9],cmd[10],c20,c20);
    DEBUG_PRINT("c21 0x%x 0x%x = 0x%x: %d\n",cmd[11],cmd[12],c21,c21);
    DEBUG_PRINT("c30 0x%x 0x%x = 0x%x: %d\n",cmd[13],cmd[14],c30,c30);

    _cs = 0;
        _spi.write(regs::PSR_B2|spi_mask::SPL06_001_SPI_READ); // press_msb
        for(int i = 0; i < 3; i++)
            cmd[i] = _spi.write(spi_mask::SPL06_001_SPI_READ);  // Load the Pressure Data into an array
    _cs = 1;

    if (cmd[0]>=0x80){press_raw=0xff000000;} else {press_raw=0x00000000;}   //convert from 24 signed to 32 signed
    press_raw |= (cmd[0] << 16) | (cmd[1] << 8) | (cmd[2]);
    DEBUG_PRINT("Raw Pressure is = 0x%02x 0x%02x 0x%02x :: 0x%08x \n", cmd[0], cmd[1], cmd[2], press_raw);
    press_sc=(float)press_raw/kP;               // Convert from RAW pressure to Scaled value using kP factor
    DEBUG_PRINT("Scaled factor Pressure is = %f\n", press_sc);

    _cs = 0;
        _spi.write(regs::TMP_B2|spi_mask::SPL06_001_SPI_READ);
        for(int i = 0; i < 3; i++){cmd[i] = _spi.write(0);}  // Load the Temperature Data into an array
    _cs = 1;

    if (cmd[0]>=0x80){temp_raw=0xff000000;} else {temp_raw=0x00000000;} //convert from 24 signed to 32 signed
    temp_raw |= ((cmd[0] << 16) | (cmd[1] << 8) | (cmd[2] << 0));

    DEBUG_PRINT("Raw Temperature is = 0x%02x 0x%02x 0x%02x :: 0x%08x; %d\n", cmd[0], cmd[1], cmd[2], temp_raw, temp_raw);
    temp_sc = (float)temp_raw/kT;               // Convert from RAW temperature to Scaled value using kT factor
    DEBUG_PRINT("Scaled factor Temperature is = %f\n\n", temp_sc);

    // Convert to Compensated Pressure Value using Scaled Pressure and Current Scaled Temperature Values
    pressf = (float)c00 + press_sc*((float)c10 + press_sc*((float)c20 + press_sc*(float)c30)) + temp_sc*(float)c01+temp_sc*press_sc*((float)c11+press_sc*(float)c21);
    DEBUG_PRINT("Pressure compensated = %7.1f\n\n", pressf);    // Compensated Pressure Value in Pascals

    return (pressf/100.0f);     // in Pascals divde by 100 to give hPa hectopascals
}

