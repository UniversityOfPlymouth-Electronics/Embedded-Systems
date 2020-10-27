#include "mbed.h"
#include "myutils.hpp"

DigitalOut redLED(PC_2,0);
DigitalOut yellowLED(PC_3,0);
DigitalOut greenLED(PC_6,0);


int main()
{
    int grade, hits;

    printf("\n\nPress Return to Start\n\n");

    do {
        //Clear out the serial port (keyboard)
        flushInputBuffer();

        //Prompt user
        printf("\nEnter grade (0..100)\n");
        
        //Read response
        hits = scanf("%d", &grade);
    } while ( (hits < 1) || (grade < 0) || (grade > 100) );

    //Write results
    printf("scanf found %d hits\n",hits);
    printf("Grade entered = %d\n", grade);
    greenLED = 1;
    
    //Loop forever
    while (true);
}
