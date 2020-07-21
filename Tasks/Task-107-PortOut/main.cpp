#include "../uopmsb/uop_msb_1_0_0.h"

#define LED_MASK 0xFFFFFFFF

PortOut ledport(PortE, LED_MASK);

int main()
{
    while (true) {
        ledport = LED_MASK;
        wait_us(1000000);
        ledport = 0;
        wait_us(1000000); 
    }
}