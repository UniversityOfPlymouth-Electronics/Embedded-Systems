#include "uop_msb.h"
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string.h>

using namespace uop_msb;
using namespace chrono;

//Output
DigitalOut greenLED(LED1);
DigitalOut blueLED(LED2);
DigitalOut redLED(LED3);

//Outputs
LCD_16X2_DISPLAY disp;

int main()
{
    //1. Printing a string
    char str1[] = "Welcome to ELEC143";

    //Displaying a string with printf
    printf("%s\n", str1);

    //Viewing a string as an array of characters
    for (unsigned int n=0; n<sizeof(str1); n++) {
        printf("Character: %c\tASCII: %u\n", str1[n], str1[n]);
    }

    //2. It is the ZERO that defines the end of a string for many functions. 
    //   Insert a \0 into the middle of the string
    //   Note the use of strlen
    char str2[] = "Welcome\0 to ELEC143";
    printf("%s\n", str2);
    for (unsigned int n=0; n<strlen(str2); n++) {
        printf("Character: %c\tASCII: %u\n", str2[n], str2[n]);
    }

    //3. Copying strings with strcpy
    char str3[16];
    strcpy(str3, "Hello");
    printf("%s\n", str3);
    printf("Size: %d\n", sizeof(str3));
    printf("String length: %d\n", strlen(str3));

    //strcpy and Constant strings
    const char str4[] = "The moon is made of cheese";
    char str5[64];
    strcpy(str5, str4);
    printf("%s\n", str5);
    printf("Size: %d\n", sizeof(str5));
    printf("String length: %d\n", strlen(str5));   
    //strcpy(str4, str5);   //Uncomment this


    //4. Marshalling binary data with sprintf
    char str6[8];
    for (unsigned int n=0; n<3; n++) {
        unsigned int x = rand();
        x = x % 65536; //16 bit (2 bytes)
        sprintf(str6, "I guess %X", x);
        printf("%s\n", str6);
    }


    //5. Unmarshalling data with sscanf
    char strList[][8] = {   "1024", 
                            "32768",
                            "1234",
                            "65535"
                            };

    unsigned int val;
    for (unsigned int n=0; n<4; n++) {
        sscanf(strList[n], "%u", &val);
        printf("Found integer: %u\n", val);
    }

    //6. Comparing strings with strcmp
    char inputStr[64];
    while (true) {
        printf("What colour?\n");
        scanf("%s", inputStr);

        if (strcmp(inputStr, "red") == 0) {
            redLED = !redLED;
        }
        else if ( strcmp(inputStr, "green") == 0 ) {
            greenLED = !greenLED;
        }
        else if ( strcmp(inputStr, "blue" ) == 0) {
            blueLED = !blueLED;
        }
        else {
            printf("Please specify red, green or blue\n");
        }
    }

}


