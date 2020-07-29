#include "uop_msb_1_0_0.h"

// **************
// Onboard LEDs *
// **************
DigitalOut greenLED(LED1);
DigitalOut blueLED(LED2);
DigitalOut redLED(LED3);

// ****************
// Onboard Switch *
// ****************
DigitalIn BlueButton(USER_BUTTON);

// *****************************
// Traffic Lights (individual) *
// *****************************
DigitalOut TRAFFIC1_RED(TRAFFIC1_RED_PIN,0);
DigitalOut TRAFFIC1_YEL(TRAFFIC1_YELL_PIN,0);
DigitalOut TRAFFIC1_GRN(TRAFFIC1_GRN_PIN,0);
DigitalOut TRAFFIC2_RED(TRAFFIC2_RED_PIN,0);
DigitalOut TRAFFIC2_YEL(TRAFFIC2_YELL_PIN,0);
DigitalOut TRAFFIC2_GRN(TRAFFIC2_GRN_PIN,0);
 
// ****************************************
// LED strip and 7-segment (All on PORTE) *
// ****************************************

//All data bits on PORTE 
PortOut LED_PORTE(PortE, LED_MASK);
BusOut ledData(PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9);

//LED Bar
DigitalOut LED_BAR_OE(PE_0,1);      //Off by default
DigitalOut LED_RED_LE(PE_12,0);
DigitalOut LED_GRN_LE(PE_13,0);
DigitalOut LED_BLUE_LE(PE_14,0);

//7 Segment
DigitalOut LED_DIGIT_OE(PE_15,1);   //Off by default
DigitalOut LED_D1_LE(PE_10,0);
DigitalOut LED_D2_LE(PE_11,0);

