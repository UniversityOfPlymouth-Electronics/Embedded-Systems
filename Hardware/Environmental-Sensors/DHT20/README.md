
# DHT20 Educational Driver for [Mbed OS 6.X](https://os.mbed.com/)

Nicholas Outram, [University of Plymouth](https://www.plymouth.ac.uk/schools/school-of-engineering-computing-and-mathematics), 2023

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

> This is intended for educational purposes only. You are free to copy and modify this software.
>
> If you find any errors, please raise an issue or a pull-request. That would be most appreciated. 
>
> This driver was written directly from the datasheet[2], with some clarification obtained from the Arduino driver [3].

This driver has been tested with Mbed OS 6.16 [[4]](https://github.com/ARMmbed/mbed-os) on the following boards:

* [ST Nucleo F401RE](https://os.mbed.com/platforms/ST-Nucleo-F401RE/)
* [ST Nucleo F429ZI](https://os.mbed.com/platforms/ST-Nucleo-F429ZI/)

This code should build with either Mbed Studio [[5]](https://os.mbed.com/studio/) (with the included Arm C6 compiler) or Keil Studio [[6]](https://studio.keil.arm.com/auth/login/).

* Testing was performed using the bare metal profile. It should work with the Mbed RTOS just as well. 

The sensor was from seeed studio - https://wiki.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DH20/, connected via their Grove Arduino Shield https://www.seeedstudio.com/Base-Shield-V2.html using Arduino Pins D14 (SDA) and D15 (SCLK).

## TODO:

1. Implement CRC check

# Examples
All you need to do in include `dht.h` in your source file.

## Example 1
The following example uses the default pins used for the I2C interface and does not log status messages.

```c++
#pragma once
#include "mbed.h"


int main()
{
    //Create instance of DHT20 sensor
    DHT20 sensor;

    //Test
    while (true) {
        DHT20::EnvData e = sensor.readTemperatureAndHumidity();
        printf("Temperature = %8.3f\tHumidity = %8.3f\n\r", e.temperature, e.Humidity);
        wait_us(1000000);
    }
}
```


## Example 2
The following example specifies the pins used for the I2C interface. A lambda function is used to output status information (for debugging). You could equally create a global function with the same signature.

```c++
#pragma once
#include "mbed.h"
#include <functional>


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
```

# References
[1] Product Page - https://wiki.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DH20/

[2] Data Sheet - https://aqicn.org/air/sensor/spec/asair-dht20.pdf

[3] Arduino Driver - https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor

[4] Mbed OS source code - https://github.com/ARMmbed/mbed-os

[5] Mbed Studio - https://os.mbed.com/studio/

[6] Keil Studio - https://studio.keil.arm.com/auth/login/

