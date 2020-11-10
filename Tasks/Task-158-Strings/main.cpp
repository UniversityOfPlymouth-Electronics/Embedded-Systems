#include "../lib/uopmsb/uop_msb_2_0_0.h"
#include <chrono>
#include <cstdint>
using namespace uop_msb_200;
using namespace chrono;

//Output
DigitalOut redLED(TRAF_RED1_PIN);
DigitalOut yellowLED(TRAF_YEL1_PIN);
DigitalOut greenLED(TRAF_GRN1_PIN);

//Analogue Inputs
AnalogIn pot(AN_POT_PIN);

//Outputs
Buzzer buzz;
LCD_16X2_DISPLAY disp;

int main()
{
    //Printing string
    char str1[] = "Welcome\0 to ELEC143";
    printf("%s\n", str1);

    //A string is an array of characters
    for (unsigned int n=0; n<sizeof(str1); n++) {
        printf("Character: %c\tASCII: %u\n", str1[n], str1[n]);
    }

    //It is the ZERO that defines the end of a string for many functions. Insert a \0 into the middle of the string
    for (unsigned int n=0; n<strlen(str1); n++) {
        printf("Character: %c\tASCII: %u\n", str1[n], str1[n]);
    }

    //strcpy
    char str2[16];
    strcpy(str2, "Hello");
    printf("%s\n", str2);
    printf("Size: %d\n", sizeof(str2));
    printf("String length: %d\n", strlen(str2));

    //strcpy and Constant strings
    const char str3[] = "The moon is made of cheese";
    char str4[64];
    strcpy(str4, str3);
    printf("%s\n", str4);
    printf("Size: %d\n", sizeof(str4));
    printf("String length: %d\n", strlen(str4));   
    //strcpy(str3, str4);   //Uncomment this

    //sprintf
    for (unsigned int n=0; n<3; n++) {
        int x = rand() % 10;
        sprintf(str4, "I guess %u", x);
        printf("%s\n", str4);
    }

    //sscanf
    const char str5[] = "Pi equals 3.14";
    char s1[64], s2[64];
    float pi;
    sscanf(str5, "%s %s %f", s1, s2, &pi);

    // Automatic headlamp 
    while (true) {


    }  
}


