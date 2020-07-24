# Task101 Blinky
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

| **TASK 101-1**
| --- |
| Read all the comments in the code. Try and understand what you can, but don't worry if it does not all mean much. |
| 1. Check you can **build** the Task 101-Blinky project. [Watch this video](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=1cdd2263-5644-4322-841d-abfe0101c82a) if you are unsure. |
| 2. Check you can **debug** the code, running line by line [as shown in this video](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=e151c5c8-980d-42d6-ab32-abfe010d3a67) | 
| 3. Uncomment the following two lines (lines 9 and 10 in the software)| 
| `//DigitalOut blueLED(LED2);`
| `//DigitalOut redLED(LED3);` |
| *Challenge*  -Your task is to make a sequence alternating between Green+Red and just Blue. [See this video as a demonstration](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=5b0ac1b2-56eb-4108-ae83-abff00ff02ae) |


##  A Little bit of Electronics
So what is going on here? Hopefully you can see the connection between the lines of code and the effect, but what you might now be aware of is the electronics.

In electronics, we mostly work with one (or both) of the following signal types :

* Analogue - where voltages and currents can take any value, typically between and upper and lower limit
* Digital - where signal voltages can only be one of two possible values

For this section, the signals are all going to be digital. Let’s start with a simple circuit diagram, or schematic as it’s also known, as shown below:

<img src="../img/SimpleLEDCircuit.png" width="300">

Consider the following circuit diagram (also known as a **schematic**):

1. **Constant Voltage Source**. Think of this as the “perfect battery”. What ever the current `I` flowing in the circuit, the voltage across this device is ALWAYS V<sub>out</sub>. In our circuit, this will be typically be 3.3 Volts
1. **Resistor**. This is used to limit the current `I` that flows through the LED (to avoid damaging it and to save power). Resistors have a resistance property measured in Ohms (symbol &Omega; ).
1. **Light Emitting Diode (LED)** - A non-linear device that emits photons of light when an electrical current passes through it. Current can only flow in one direction. Different LEDs have different characteristics.

| **TASK 101-2** |
| --- |
| Read more about the LED [here](/glossary/led.md) |
| Now calculate a suitable current limiting resistor value for the RED and AMBER LEDs in your kit. The data is below || Enter your answers in the form |

| Colour | current (approx.)	| Voltage |
| --- | --- | --- |
| RED |	2mA	| 1.7V |
| AMBER | 2mA | 1.85V |


## Controlling an LED


https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=2cba4d8a-123a-4fd0-bf4f-ac0200f2b66b

