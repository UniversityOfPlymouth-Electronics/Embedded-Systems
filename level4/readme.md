# Embedded Systems in Context - Level 4

## What is new
This content has been migrated from [a previous version](http://blogs.plymouth.ac.uk/embedded-systems/microcontrollers/mbed-os-2/courses/embedded-systems-in-context-level-4/foreward/) based on mbed-os 5.

Changes for 2020:

* Adoption of Mbed Studio v1.0
* Adoption of Mbed-os 6.X
* More content on the fundamentals of C and C++ programming
* The [existing glossary](http://blogs.plymouth.ac.uk/embedded-systems/glossary-2/) is being migrated to a [new version](/glossary/README.md) 

# Level 4 Course
If you are a student at the University of Plymouth, welcome to the first lab!

As a guide, each section should take approximately 2 lab sessions (4-6 Hrs / section). There are additional tasks for those that finish early or want to do further self study. You may need to spend time at home completing the tasks.

| Wk | Section | Title |
| --- | --- | --- |
| 1-2 | 1 | Digital Outputs |
| 3   | 2 | Potential Dividers |
| 3-5 | 3 | Digital Inputs and Multiple Outputs |
| 6-7 | 4 | Analogue Input |
| 8-9 | 5 | Analogue Output |
| 9-13 | - | Coursework and Assessment |

_Provisional Time Plan for Practicals_

Section 2 is different to the other tasks. This is a research based task which you are advised to tackle as a group. Do not ignore this task - all content in this document may be examined in an end of module test.

## Using the Glossary
Some crucial information is contained in the [glossary](/glossary/README.md).

This is so that the document is not cluttered with every detail. Do not ignore the glossary. You should read every entry referenced in each lab. In many cases, you may see a hyperlined word (jargon typically). Some of these are links to glossary items. If you select them you can jump to the glossary items.

## Setting Expectation
Remember that each student on the course has a different background. Some may have done some electronics or programming before. Others may have done neither. It is difficult to design a course that works for everyone. 

This module is designed on the assumption that you have no electronics or software experience. However, we equally want it to be challenging and interesting for those with prior experience. Therefore you will find each section has some compulsory tasks, and some which are optional.

> Do not feel bad if you don’t have time for the extra tasks. You will meet some of these challenges later in the programme.
>
> Equally, if you have done some software before, beware of complacency and seek opportunities to push yourself, explore new areas and ask questions.

As a final remark, this is a fairly intensive course. You cannot learn to play the piano in 13 weeks - the human brain simply does not work like that, so don’t expect to master programming at the end. This is the beginning of your education - we hope it’s an enjoyable one.


## Your Kits
You are provided with a Kit that enables you to work both in the lab and at home. The contents will vary from year to year (the image is only indicative). 

<img src="../img/Stage-1-kits-2018.png" width="600">

You may also be loaned other equipment, such as a "Picoscope". Further instructions will be given on how to use it.


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

| **TASK 101-1**
| --- |
| Read all the comments in the code. Try and understand what you can, but don't worry if it does not all mean much. |
| 1. Check you can **build** the Task 101-Blinky project. [Watch this video](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=1cdd2263-5644-4322-841d-abfe0101c82a) if you are unsure. |
| 2. Check you can **debug** the code, running line by line [as shown in this video](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=e151c5c8-980d-42d6-ab32-abfe010d3a67) | 
| 3. Uncomment the following two lines (lines 9 and 10 in the software)| 
| `//DigitalOut blueLED(LED2);`
| `//DigitalOut redLED(LED3);` |
| *Challenge*  -Your task is to make a sequence alternating between Green+Red and just Blue. [See this video as a demonstration](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=5b0ac1b2-56eb-4108-ae83-abff00ff02ae) |



