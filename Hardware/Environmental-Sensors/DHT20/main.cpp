/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include <iostream>
#include "dht20.h"
using namespace std;

int main()
{
    //Call back to write status messages in the terminal
    auto logger = [](const char* m) {
        cout << m << endl;
    };
    //Create instance of DHT20 sensor
    DHT20 sensor(ARDUINO_UNO_D14, ARDUINO_UNO_D15, logger);

    //Test
    while (true) {
        DHT20::EnvData e = sensor.readTemperatureAndHumidity();
        printf("Temperature = %8.3f\tHumidity = %8.3f\n\r", e.temperature, e.Humidity);
        wait_us(1000000);
    }
}
