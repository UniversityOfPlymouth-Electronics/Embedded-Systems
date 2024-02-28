#include "uop_msb.h"
using namespace uop_msb;

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


int main()
{
    printf("\nTASK-110\n");

    // Integer
    int count = 10; // initialse count to value 10
    printf("count = %d\n", count);

    // Add two to count
    count = count + 2;
    printf("New value of count = %d\n", count); // add 2 to the count

    // Char
    char character;
    character = 'A';
   // character = 65;

   // printf("The character %c has the ASCII code %d\n", character, character);
   // printf(R"(The character %c = %d\n)",character, character); //a wass declere a=65

    //char character;
   // character = 'Z'; //char Z-ASCII code 90
   // printf("The character %c has the ASCII code %d\n", character, character);
    //char character;
   // character = 'a'; //char Z-ASCII code 97
   // printf("The character %c has the ASCII code %d\n", character, character);

        

    // Short
    short shortCount = 32766;
    printf("The value of shortCount is %hd\n", shortCount); // h = half
    shortCount = shortCount + 1; // value of short become negative number plus 2 "overflow start con from - to +"
    printf(R"(add 1 and shortCount is %hd)", shortCount); 

    /* short shortCount = 32766; // pluse 2 
    printf("The value of shortCount is %hd\n", shortCount); // h = half
    shortCount = shortCount + 2; // value of short become negative number plus 2
    printf(R"(add 1 and shortCount is %hd)", shortCount); */



   
     

     // Long long
     long long NN = 0x12345678ABCD0001LL; // Literal in HEX
     printf("A very large number %lld\n", NN);
    // printf("A very large number %d\n", NN);//error
     printf("A very large number in hex %llX\n", NN);


      /*long long NN = 0x12345678ABCD0001LL; // change the place holders from lld to d logical error
     printf("A very large number %d\n", NN); // error format specifies type unsigned int but argument has type lon long
    // printf("A very large number %d\n", NN);//error
     printf("A very large number in hex %X\n", NN); */


  
    // unsigned
    /* unsigned short p = 1; //16 bit and underflow back to maximum value = 65535
    printf("unsigned int p = %u\n", p);
    p = p - 2;
    printf("Subtract 2. Now unsigned int p = %u\n", p); */


   // short p
    short p = 1; //16 bit
    printf("short  int p = %d\n", p); // p = 1
    p = p - 2;
    printf("Subtract 2. Now short int p = %d\n", p); // p = -1

 // float:standard fractional number type

    /*float pi_float = 3.1415926536;
    printf("The value of pi is approximately %f\n", pi_float); */

    /*float pi_float = 3.1415926536;
    printf("The value of pi is approximately %10f\n", pi_float); // change %f to %10f*/


     float pi_float = 3.1415926536;
    printf("The value of pi is approximately %20f\n", pi_float); // change o %10f to 20


    // double:double precision.

    /*double pi_double = 3.1415926536l;
     printf("The value of pi is approximately %lf\n", pi_double);*/


   /* double pi_double = 3.1415926536l;
    printf("The value of pi is approximately %10lf\n", pi_double);  */// change %lf to %.10lf 

 double pi_double = 3.1415926536l;
    printf("The value of pi is approximately %20lf\n", pi_double); // change %.10lf to 20












    // Data type sizes (in bytes)
    printf("Size of a char is %d bytes\n", sizeof(char));
    printf("Size of a short is %d bytes\n", sizeof(short));
    printf("Size of a int is %d bytes\n", sizeof(int));
    printf("Size of a long is %d bytes\n", sizeof(long));
    printf("Size of a long long is %d bytes\n", sizeof(long long));
    printf("Size of a float is %d bytes\n", sizeof(float));
    printf("Size of a double is %d bytes\n", sizeof(double));

    // Stop
    while (true);   
}