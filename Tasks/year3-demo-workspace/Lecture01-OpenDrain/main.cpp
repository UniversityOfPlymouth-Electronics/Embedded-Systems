#include "mbed.h"

#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

#define TRAF_GRN2_PIN PC_9
#define TRAF_YEL2_PIN PC_8
#define TRAF_RED2_PIN PC_7

#define TRAF_WHITE_PIN PF_10

BusOut traffic1(TRAF_GRN1_PIN, TRAF_YEL1_PIN, TRAF_RED1_PIN);
BusInOut traffic2(TRAF_GRN2_PIN, TRAF_YEL2_PIN, TRAF_RED2_PIN);

int main() {
    traffic1 = 0b111;
    traffic2.output();
    traffic2.mode(PinMode::OpenDrainNoPull);

    while (true) {
        traffic2 = 0;
        wait_us(500000);
        traffic2 = 0b111;
        wait_us(500000);
    }
}
