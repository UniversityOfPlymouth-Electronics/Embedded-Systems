#include "mbed.h"

BusOut leds(PC_2, PC_3, PC_6, PB_0, PB_7, PB_14);
// main() runs in its own thread in the OS
int main() {
  while (true) {
    leds = 0b000111;
    wait_us(500000);
    leds = 0b111000;
    wait_us(500000);
    leds = 0b111111;
    wait_us(500000);
  }
}
