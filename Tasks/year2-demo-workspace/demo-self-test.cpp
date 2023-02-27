#include "demo-self-test.hpp"

void POST()
{
    puts("LEDs ON");
    red_led    = 1;
    yellow_led = 1;
    green_led  = 1;
    onboardLED = 1;
    wait(0.5);
    puts("LEDs OFF");
    red_led    = 0;
    yellow_led = 0;
    green_led  = 0;
    onboardLED = 0;
    wait(0.5);
    puts("Polling Switches");
    printf("sw1: %d\r\n", (sw1 == 1));
    printf("sw2: %d\r\n", (sw2 == 1));
    printf("Blue Button: %d\r\n", (button == 1));
}