#include "../lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

Buzzer buzz;

PortOut LED_PORTE(PortE, LED_MASK);

DigitalOut LED_BAR_OE(LED_BAR_OE_PIN,1);      //Off by default
DigitalOut LED_DIGIT_OE(LED_DIGIT_OE_PIN,1);   //Off by default

DigitalOut LED_D1_LE(LED_D1_LE_PIN,0);
DigitalOut LED_D2_LE(LED_D2_LE_PIN,0);
DigitalOut LED_RED_LE(LED_RED_LE_PIN,0);
DigitalOut LED_GRN_LE(LED_GRN_LE_PIN,0);
DigitalOut LED_BLUE_LE(LED_BLUE_LE_PIN,0);

DigitalIn BlueButton(USER_BUTTON);

BusOut ledData(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN);

//This is a constant
const int NN = 10;

int main()
{
    // Integer
    int count = 0;
    printf("count = %d\n", count);

    // Add one to count
    count = count + 1;
    printf("New value of count = %d\n", count);

    // Char
    char character;
    character = 'A';
    printf("The character %c has the ASCII code %d\n", character, character);

    // float 
    float pi_float = 3.14159265358979323846;
    printf("The wonderful value of pi is approximately %f\n", pi_float);

    // double
    double pi_double = 3.14159265358979323846l;
    printf("The wonderful value of pi is approximately %lf\n", pi_double);

    // long double
    long double accurate_pi = 3.14159265358979323846L;
    printf("For a truely spectacular pi, try this: %Lf", accurate_pi);




    // Stop
    while (true);   
}