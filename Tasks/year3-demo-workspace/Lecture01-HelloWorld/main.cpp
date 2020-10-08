#include "../../lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

LCD_16X2_DISPLAY display;  

// main() runs in its own thread in the OS
int main()
{
    printf("Hello Console\n");
    display.printf("Hello LCD");
    while (true);
}

