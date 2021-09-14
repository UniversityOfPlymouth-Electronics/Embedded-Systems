#include "uop_msb.h"
using namespace uop_msb;

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
