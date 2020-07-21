# Embedded Systems in Context - Level 4

## What is new
This content has been migrated from [a previous version](http://blogs.plymouth.ac.uk/embedded-systems/microcontrollers/mbed-os-2/courses/embedded-systems-in-context-level-4/foreward/) based on mbed-os 5.

Changes for 2020:

* Adoption of Mbed Studio v1.0
* Adoption of Mbed-os 6.X
* More content on the fundamentals of C and C++ programming

# Level 4 Course
If you are a student at the University of Plymouth, welcome to the first lab!

## Task101
This is the first application which you will download and build. 

> If you have not already tried this application and watched the videos, see the section in [getting started](../getting_started/software-testing.md#Task101-Blinky!)

You can also browse the code online here:

[Task101 - Blinky](/Tasks/Task-101-Blinky)

Let's take a quick look at the code:

```C++
//This is known as a “header file”. In short, this copies and pastes the text file mbed.h into this code
#include "../uopmsb/uop_msb_1_0_0.h"

// Create a DigitalOut “object” called greenLED. Pass constant LED1 as a “parameter”
DigitalOut greenLED(LED1);

//These are "commented out" and so are not part of the program. You can uncomment them by removing the // characters
//Your task is to make a sequence alternating between Green+Red and just Blue 
//DigitalOut blueLED(LED2);
//DigitalOut redLED(LED3);

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
```
