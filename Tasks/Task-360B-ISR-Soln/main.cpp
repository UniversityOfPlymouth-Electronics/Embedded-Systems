#include "mbed.h"
#include "SwitchManager.hpp"

#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2
#define BTN1_PIN PG_0
#define BTN2_PIN PG_1

Ticker yellowTick;
DigitalOut  yellow_led(TRAF_YEL1_PIN);

void toggleYellowISR() {
    yellow_led = !yellow_led;    
}
    
int main() {
    
    //Interrupt controlled red led using BTN1
    SwitchManager sm1(BTN1_PIN, TRAF_RED1_PIN);

    //Interrupt controlled green led using BTN2    
    SwitchManager sm2(BTN2_PIN, TRAF_GRN1_PIN);    
    
    //Simple ticker for the yellow LED
    yellowTick.attach(&toggleYellowISR, 500ms);
    
    //Now loop forever
    while(1) { 
        sleep();
        printf("count=%u\n",SwitchManager::getCount());
    };
}
