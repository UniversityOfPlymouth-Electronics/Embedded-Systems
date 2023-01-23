// DHT20 Educational Driver for Mbed OS 6.X
// Nicholas Outram, University of Plymouth,2023
//
// This is intended for educational purposes only and is provided AS-IS. Use at your own risk.
// The author and the University of Plymouth accept no liability for any consequence of using this software
// You are free to copy and modify this software.
// If you find any errors, please raise an issue or a pull-request. That would be most appreciated. 
// This driver was written directly from the datasheet[2], with some clarification obtained from the Arduino driver [3].
// 
// References
// [1] Product Page - https://wiki.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DH20/
// [2] Data Sheet - https://aqicn.org/air/sensor/spec/asair-dht20.pdf
// [3] Arduino Driver - https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor


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
