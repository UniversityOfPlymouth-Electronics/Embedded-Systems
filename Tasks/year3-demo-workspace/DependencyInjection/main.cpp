
#include "Flashy.hpp"
#include <chrono>
#include <cstdint>
#include <ratio>

#include "uop_msb.h"
#include "MbedLight.hpp"
#include "MockedLight.hpp"
#include "MockedTimer.hpp"
#include "MbedTimer.hpp"


DigitalIn blueButton(USER_BUTTON);
ITimer* tmrObj;
ILightNotify* lightObj;

int main()
{
    if (blueButton == 1) {
        tmrObj = new MbedTimer();
        lightObj = new MbedLight(LED1);
    } else {
        tmrObj = new MockedTimer();
        lightObj = new MockedLight("LED");      
    }

    Flashy f(*tmrObj, *lightObj, 250ms);
    
    while (true) {
        f.flashOnce();
        tmrObj->wait_for(1000ms);
    }
}




