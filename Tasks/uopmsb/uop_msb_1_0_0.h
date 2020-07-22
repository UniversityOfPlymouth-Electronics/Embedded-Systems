// (c) 2020 University of Plymouth

// another edit 16 07 2020

#include "mbed.h"

// *****************************
// Traffic Lights (individual) *
// *****************************
#define TRAFFIC1_GRN_PIN PC_9
#define TRAFFIC1_YELL_PIN PC_8
#define TRAFFIC1_RED_PIN PC_7

#define TRAFFIC2_GRN_PIN PC_2
#define TRAFFIC2_YELL_PIN PC_3
#define TRAFFIC2_RED_PIN PC_6

// ****************************************
// LED strip and 7-segment (All on PORTE) *
// ****************************************
//All lower 16-bits of PORTE pins are outputs
#define LED_MASK 0x0000FFFF
//For initialisation, OE=0, LE=1, DATA=0
#define LED_INIT 0x00007C00 //0b0111 1100 0000 0000
//For OFF condition, OE = 1, LE=0 and DATA=0 
#define LED_OFF 0x00008001


// BUZZER
#define BUZZER PB_13

// THE MATRIX
#define MATRIX_LATCH PB_6
#define MATRIX_OE PB_12

