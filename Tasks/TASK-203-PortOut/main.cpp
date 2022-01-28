#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2
#define LEDMASK 0b0000000001001100
// Objects
//BusOut leds(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);
PortOut leds(PortC, LEDMASK);

int main()
{
    while (true) {
        leds = 0;   //Binary 000
        wait_us(500000);
        leds = 0xFF;   //Binary 11111111
        wait_us(500000);    
    }
}




