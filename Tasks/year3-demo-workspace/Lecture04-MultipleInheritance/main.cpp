#include "mbed.h"
#include "TrafficLight.h"

TrafficLight lights;
DigitalIn sw(USER_BUTTON);

TrafficLight::LIGHT_STATE s;

int main()
{
    while (true) {

        //Wait for switch press
        while (sw==0);

        //Update lights
        s = lights.nextState();
 
        //Debounce switch
        wait_us(300000);

        //Wait for switch release
        while (sw==1);

        //Switch debounce
        wait_us(300000);
        
    }
}

