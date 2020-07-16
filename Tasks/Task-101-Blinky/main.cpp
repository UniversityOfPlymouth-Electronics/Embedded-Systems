//This is known as a “header file”. In short, this copies and pastes the text file mbed.h into this code
#include "mbed.h"

// Create a DigitalOut “object” called greenLED. Pass constant LED1 as a “parameter”
DigitalOut greenLED(LED1);

//The main function - all executable C / C++ applications have a main function. This is our entry point in the software
int main() 
{
    //Write a welcome message to the terminal
    puts("Welcome to the University of Plymouth");

    // ALL the repeating code is contained in a  “while loop”
    while(true) 
    {
        //The code between the { curly braces } is the code that is repeated forever

        // Turn onboard LED ON  
        greenLED = 1; 

        // Wait 1 second (1 million microseconds)
        wait_us(1000000); 

        // Turn LED OFF
        greenLED = 0; 

        // Wait 1 second
        wait_us(1000000); 
    }
}