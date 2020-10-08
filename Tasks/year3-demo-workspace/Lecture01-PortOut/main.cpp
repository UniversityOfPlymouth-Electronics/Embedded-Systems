#include "mbed.h"

//BusOut leds(PC_2, PC_3, PC_6, PB_0, PB_7, PB_14);
PortOut portc(PortC, 0b0000000001001100);
PortOut portb(PortB, 0b0100000010000001);

int main() {
  while (true) {
    portb = 0;
    portc = 0xFFFF;
    wait_us(500000);
    portb = 0xFFFF;
    portc = 0;
    wait_us(500000);
  }
}
