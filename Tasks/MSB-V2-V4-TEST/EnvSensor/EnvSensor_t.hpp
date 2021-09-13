#ifndef ENV_SENSOR_H
#define ENV_SENSOR_H

#include "mbed.h"

//#define _DEBUG
#ifdef _DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
//now can use DEBUG_PRINT("Battle of Hastings was in %d\n",1066);
#else
#define DEBUG_PRINT(...)
#endif



class EnvSensor_t {

    public:
    typedef enum {NOTSUPPORTED, BMP280, SPL06_001} MEMS_TYPE_t;

    protected:
    /** Type of sensor used
     *
     *  Access via accessor
     *
     */
    MEMS_TYPE_t sensorType = NOTSUPPORTED;


    protected:
    /** Read-accesor sensor type being
     *
     *  Access via accessor
     *
     */
    MEMS_TYPE_t getSensorType() {
        return sensorType;
    }

    public:

    /** Read the current temperature value (degree Celsius) from the sensor
     *
     * @return Temperature value (degree Celsius)
     */
    virtual float getTemperature(void);

    /** Read the current pressure value (hectopascal) from the sensor
     *
     * @return Pressure value (hectopascal)
     */
    virtual float getPressure(void);

    /** Read the current humidity value (percentage saturation) from the sensor
     *
     * @return Percentage humidity
     */
    virtual float getHumidity(void)
    {
        DEBUG_PRINT("HUMIDITY NOT IMPLEMENTED YET");
        return 0.0f;
    }

    /** Returns is a particular sensor type is present on the hardware
     *
     * @return boolean. true if connected
     */   
    virtual bool isPresent()
    {
        return false;
    }
 
};

#endif // EnvSensor_h