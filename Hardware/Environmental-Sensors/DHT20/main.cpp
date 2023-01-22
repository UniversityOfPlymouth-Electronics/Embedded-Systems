/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PinNames.h"
#include "mbed.h"
#include "I2C.h"
#include <iostream>
using namespace std;

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

//I2C interface
I2C dht20(ARDUINO_UNO_D14, ARDUINO_UNO_D15);   //SDA,SCL : I2C1 on the Arduino interface
const int SHA_I2C_ADDR = 0b01110000;

int main()
{
    int status = 0;
    auto checkStatus = [&](){
        if (status == 0) {
            cout << "ACK" << endl;
        } else {
            printf("NACK: Code = %X\n\r", status);
        }
    };

    I2C dht20(ARDUINO_UNO_D14, ARDUINO_UNO_D15);   //SDA,SCL : I2C1 on the Arduino interface  
    //Give sensor 100ms to start up
    wait_us(100000);  
    cout << "Setting Clock Frequency" << endl;
    dht20.frequency(100000); //100kHz
    //Give sensor 100ms to start up
    wait_us(100000);

    cout << "Startup Routine" << endl;
    const char statusCommand = 0x71;
    status = dht20.write(SHA_I2C_ADDR, &statusCommand, 1);
    checkStatus();

    //Generic array of bytes
    char byteArray[7];
    
    //Read Status
    status = dht20.read(SHA_I2C_ADDR, byteArray, 1);
    checkStatus();
    printf("Startup Status: %X\n\r", byteArray[0]);
    if (byteArray[0] != 0x18) {
        printf("Please recalibrate\n\r");
    } else {
        printf("Device calibration OK\n\r");
    }

    //10ms wait
    wait_us(10000);

    // ***Read Sensor Data***
    printf("Attempting to read env data\n\r");
    const char readCmd[] = {0xAC, 0x33, 0x00};
    status = dht20.write(SHA_I2C_ADDR, readCmd, 3);
    checkStatus();
     
    //Check if ready
    do {
        printf("Ready?\n\r");
        wait_us(80000); //80ms wait (for sensors to be ready) 
        status = dht20.read(SHA_I2C_ADDR, byteArray, 1);
        checkStatus();
    } while ((byteArray[0] & 0b01000000) != 0);
    
    //Grab 6 bytes of data (6 data, 1 CRC)
    printf("Reading 6 bytes of data + 1 byte CRC\n\r");
    status = dht20.read(SHA_I2C_ADDR, byteArray, 7);
    checkStatus();

    //Extract Temp and Humidity
    for (unsigned int n=0; n<7; n++) {
        printf("X[%u] = %X\n\r",n,byteArray[n]);
    }
    uint32_t h;
    h  = ((uint32_t)byteArray[1] << 12);
    h |= ((uint32_t)byteArray[2] << 4);
    h |= ((uint32_t)byteArray[3] >> 4);
    
    uint32_t t;
    t  = ((uint32_t)byteArray[3]) & 0x0F; t <<= 16;
    t |= ((uint32_t)byteArray[4] << 8);
    t |= (uint32_t)byteArray[5];

    double humidity = 100.0*(double)h / (double)(1<<20);
    double temp = (200.0 * (double)t / (double)(1<<20)) - 50.0;

    //Done
    printf("temp = %f\n\rhumid=%f\n\r",temp, humidity); 
    while (true)
    {
        led1 = !led1;
        thread_sleep_for(WAIT_TIME_MS);
    }
}
