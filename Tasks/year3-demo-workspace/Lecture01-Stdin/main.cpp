#include "mbed.h"

#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

#define TRAF_GRN2_PIN PC_9
#define TRAF_YEL2_PIN PC_8
#define TRAF_RED2_PIN PC_7

#define TRAF_WHITE_PIN PF_10

BusOut traffic1(TRAF_GRN1_PIN, TRAF_YEL1_PIN, TRAF_RED1_PIN);

int main()
{
    int u;
    while (true) {
        printf("Enter an integer\n");
        scanf("%d", &u);
        printf("You entered %d\n", u);
        traffic1 = u;
    }
}

