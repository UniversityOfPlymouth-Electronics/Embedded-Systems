[Up - Digital Outputs: Week 1](Digital_Outputs_1.md)

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
| 6 | Verify you can see the text output in the serial monitor (a tab called something such as _NUCLEO-F429ZI) 


There is a lot more going on in this example!

```C++
#include "../lib/uopmsb/uop_msb_1_0_0.h"
using namespace uop_msb_100;

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

    // This is a variable (not an oject as it has no functions) that stores a whole number (integer)
    int counter = 0;

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


## Quiz

---

[BACK - Digital Outputs: Week 1](Digital_Outputs_1.md)