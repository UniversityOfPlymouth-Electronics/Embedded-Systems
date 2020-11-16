#include "mbed.h"
#include "string.h"

DigitalOut greenLED(LED1);
DigitalOut blueLED(LED2);
DigitalOut redLED(LED3);

int main()
{
    while (true) {
        char cmdString[] = "red,blue,wait,green,wait,red,blue,green,wait,blue,green,wait";
        const char delim[]=",";
        char *nextString;

        //Search for next instance of delim    
        nextString = strtok(cmdString, delim);

        while (nextString != NULL) 
        {
            printf("Found %s\n", nextString);
            printf("cmdString is now %s\n", cmdString);

            // TODO: Check which string is next
            //       and switch on the correct LED (or pause)

            nextString = strtok(NULL, delim);
        }
    }

}

