#include "../../lib/uopmsb/uop_msb.h"

extern PortOut LED_PORTE;

extern DigitalOut LED_BAR_OE;      //Off by default
extern DigitalOut LED_DIGIT_OE;   //Off by default

extern DigitalOut LED_D1_LE;
extern DigitalOut LED_D2_LE;
extern DigitalOut LED_RED_LE;
extern DigitalOut LED_GRN_LE;
extern DigitalOut LED_BLUE_LE;

extern DigitalIn BlueButton;
extern BusOut ledData;

extern void setup_hardware();
void EnableRedLEDs();
void EnableGreenLEDs();
void EnableBlueLEDs();