[Up - Digital Outputs: Week 2](Digital_Outputs_1.md)

--- 

# Task 103 - Hello World
So far we have seen two types of output, light (GPIO connected to an LED) and sound (GPIO connected to a buzzer). There are times when we wish to output human readable text. There are a few ways to do this, and we will look at two options now:

* Serial Terminal
* LCD Display

| TASK | Details |
| --- | --- |
| 1 | Set `TASK-103-HelloWorld` as the active project |
| 2 | Build the project |
| 3 | In Mbed Studio, click the View menu and select `Serial Monitor` |
| 4 | Run the code |
| 5 | Verify you can read the text on the LCD screen |
| 6 | Verify you can see the text output in the serial monitor (usually a tab called _NUCLEO-F429ZI) |
| 7 | Now watch the following video: |

https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=e32836bc-ecdf-40f4-9ed3-ac37011155fb

There is a lot more going on in this example. To try and see what you've understood, attempt the following tasks:

| TASK | | DETAILS | Answer |
| --- | --- | --- | --- |
| 7 | - | Using the debugging mode, step through the code line by line and try to work out the following: | - |
| | a. | Note what the statement `printf("Hello World\n");` does. On which computer does the output appear? | <p title="The serial monitor on the host PC">Answer</p> |
| | b. | Same for `lcd.printf("Hello World");`. On which computer does the output appear? | <p title="The target board (Nucleo)">Answer</p> |
| | c. | Describe the function/purpose of the statement `ledBlue = !ledBlue;` | <p title="This flips (toggles) the state of the LED">Answer</p> |
| | d. | Describe the function/purpose of the statement `counter = counter + 1;` **Tip**: Hover your mouse over `counter` in Mbed Studio to watch it's value before and after. | <p title="It increments the value of counter by 1">Answer</p> |
| | e. | The following outputs some text: `printf("Count: %d\n", counter);`. Is this the same text every time? | <p title="No. It includes a variable quantity derived from counter">Answer</p> |
| 8 | | Modify the code inside the while-loop to flash all the LEDs (hint: you only need to add two lines) | - |


> The answers to the questions can be revealed by hovering your mouse over the word `Answer`.

That's quite a lot, and don't feel bad if you're not sure. For reference, the code for this exercise is shown below:

```C++
#include "../lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

#define WAIT_TIME_MS 2000

//Initialise the DigitalOut objects with a default value of 1
DigitalOut ledGreen(LED1,1);
DigitalOut ledBlue(LED2,1);
DigitalOut ledRed(LED3,1);

LCD_16X2_DISPLAY lcd;

int main()
{
    // Write to serial terminal on host PC
    printf("Hello World\n");

    // Clear the LCD screen
    lcd.cls();

    //Small pause for 1s
    wait_us(1000 * WAIT_TIME_MS);

    //Turn off all the LEDs
    ledRed = 0;
    ledGreen = 0;
    ledBlue = 0;

    // Write to LCD using the LCD_16X2_DISPLAY driver class
    lcd.printf("Hello World");
    lcd.locate(1, 0);   //Row 1, Col 0
    lcd.printf("ELEC143");

    // This is a variable (not an oject as it has no functions) that stores a whole number (integer) in memory
    // (I used the keyword volatile to force it to use memory... long story and one for later)
    volatile int counter = 0;

    while (true)
    {
        //Toggle the LED
        ledBlue = !ledBlue;

        //Add 1 to the counter "variable"
        counter = counter + 1;

        //Display in the terminal
        printf("Count: %d\n", counter);

        //Wait
        wait_us(WAIT_TIME_MS * 1000);
    }
}
```

## More on while-loops
In the example above, the LEDs flash forever. The microcontroller will keep doing this as long as power is provided. To explore this a little deeper, let's make a simple change to the code. 

| TASK | | DETAILS |
| --- | --- | --- |
| 9 | - | Replace the while-loop with the code shown below: |


```C++
    while (counter < 10)
    {
        //Toggle the LED
        ledBlue = !ledBlue;

        //Display in the terminal
        printf("Count: %d\n", counter);

        //Wait
        wait_us(WAIT_TIME_MS * 1000);

        //Add 1 to the counter "variable"
        counter = counter + 1;        
    }

    ledRed = 1;
    ledGreen = 1;
    ledBlue = 1;

    wait_us(osWaitForever);
```

| TASK |  | DETAILS | Answer |
| --- | --- | --- | --- |
| 10  | a. | Use the debugger to step through this code to ensure you fully understand it. Pay particular attention on the value of `counter` and the behaviour of the `while` statement | - |
|  | b. | How many times does the value of `counter` get written to the serial console? | <p title="10 times"> Answer </p> |
|   | c. | What are the first and last values of `counter` that are displayed? | <p title="0 and 9"> Answer </p> |
|   | d. | Use the debugger to find out the final value of `counter` (not necessarily the same as the last displayed value) | <p title="10"> Answer </p> |


> Checking your answers:
> 
> Hover your mouse over the word "Answer" in the table above to see if you are correct.

| TASK | DETAILS |
| --- | --- | 
| 11 | Modify the code to count from 0 to 4, then stop. You only need to modify one thing to achieve this |
| 12 | Modify the code to count from 10 to 15, then stop. <p title="Change the initial value of counter">Hover the mouse here for a hint</p> |


## Quiz
Before you complete this section, please ensure you complete the quiz.

https://dle.plymouth.ac.uk/mod/quiz/view.php?id=1161833

---

[NEXT - Task 104 - Traffic Lights](TASK104.md)