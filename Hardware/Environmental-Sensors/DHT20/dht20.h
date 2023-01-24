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
//

/*
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "mbed.h"
#include <functional>

/*
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
*/

class DHT20 {
public:
  typedef struct {
      double temperature;
      double Humidity;
  } EnvData;
  typedef function<void(const char*)> CALLBACK_t;

private:
  I2C _sensor;
  DigitalOut _led;
  int _status;
  const char statusCommand = 0x71;
  const char resetCommand = 0xBA;
  const int SHA_I2C_ADDR = 0b01110000;
  char byteArray[7];
  double _humidity;
  double _temperature;
  CALLBACK_t _msg; //Call back

private:
  void critErr() {
      while (true) {
          _msg("Critical Error");
          _led = !_led;
          wait_us(125000);
      }
  }
  void checkStatus() {
      if (_status > 0) {
        error("NACK: Code = %X\n\r", _status);
        critErr();
      }    
  }


public:
  DHT20(PinName SDA = ARDUINO_UNO_D14, PinName SCL = ARDUINO_UNO_D15, CALLBACK_t msg = [](const char*){}) : _sensor(SDA, SCL), _led(LED1), _msg(msg)
  {
    _status = 0;

    // Give sensor 100ms to start up
    _msg("Waiting 100ms");
    wait_us(100000);
    // Setting Clock Frequency
    _msg("Setting clock frequency");
    _sensor.frequency(100000); // 100kHz
    // Give sensor 500ms to start up
    _msg("Waiting 500ms");
    wait_us(500000);

    //Soft reset
    _msg("Soft Reset");
    _status = _sensor.write(SHA_I2C_ADDR, &resetCommand, 1);
    checkStatus();
    _msg("Waiting 500ms");
    wait_us(500000);

    // Startup Routine
    _msg("Checking Status Command");
    _status = _sensor.write(SHA_I2C_ADDR, &statusCommand, 1);
    checkStatus();

    // Read Status
    _msg("Read Back Status");
    _status = _sensor.read(SHA_I2C_ADDR, byteArray, 1);
    checkStatus();
    if (byteArray[0] != 0x18) {
      _msg("Sensor does not return 0x18 - recalibrate?");
    } else {
      _msg("Sensor looks good! Received 0x18");  
    }

    // 10ms wait
    _msg("Delay 10ms");
    wait_us(10000);
  }

  EnvData readTemperatureAndHumidity() {
    // ***Read Sensor Data***
    _msg("Start Measurement Command");
    const char readCmd[] = {0xAC, 0x33, 0x00};
    _status = _sensor.write(SHA_I2C_ADDR, readCmd, 3);
    checkStatus();

    // Check if ready
    do {
      _msg("Checking...");
      wait_us(80000); // 80ms wait (for sensors to be ready)
      _status = _sensor.read(SHA_I2C_ADDR, byteArray, 1);
      checkStatus();
    } while ((byteArray[0] & 0b01000000) != 0);

    // Grab 6 bytes of data (6 data, 1 CRC)
    _msg("Reading 6 bytes of data + 1 byte CRC");
    _status = _sensor.read(SHA_I2C_ADDR, byteArray, 7);
    checkStatus();

    // Extract Temp and Humidity
    uint32_t h;
    h = byteArray[1];
    h = (h << 8) | byteArray[2];
    h = (h << 4) | (byteArray[3] >> 4);

    uint32_t t;
    t = byteArray[3] & 0x0F;
    t = (t << 8) | byteArray[4];
    t = (t << 8) | byteArray[5];

    _humidity = 100.0 * (double)h / (double)(1 << 20);
    _temperature = (200.0 * (double)t / (double)(1 << 20)) - 50.0;

    EnvData res = {.temperature = _temperature, .Humidity = _humidity};
    return res;
  }

  double getTemperature() {
      return _temperature;
  }

  double getHumidity() {
      return _humidity;
  }

};
