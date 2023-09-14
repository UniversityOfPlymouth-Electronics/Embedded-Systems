#include "mbed.h"

#define LED1_Pin GPIO_PIN_0      //Used for PB_0 which is wired to the green LED
#define LED2_Pin GPIO_PIN_7      //Used for PB_7 which is wired to the blue LED
#define LED3_Pin GPIO_PIN_14     //Used for PB_14 which is wired to the red LED

// Create a DigitalOut “objects”

// In Mbed, we did this to set up the GPIOs
//
// DigitalOut greenLED(LED1);
// DigitalOut blueLED(LED2);
// DigitalOut redLED(LED3);

// This function sets up all three on-board LEDs. In Mbed, this task is performed in the DigitalOut constructor
// (If you trace inside DigitalOut, you will see it is a very thin shim around a simple C API)
void setupGPIO()
{
    // C Structure used to setup GPIO for LEDs
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Step 1: Enable the clock for port B
    __HAL_RCC_GPIOB_CLK_ENABLE();   //Enable the clock for PORTB

    // Step 2: Set output data register to zero for each (one liner!)
    HAL_GPIO_WritePin(GPIOB, LED1_Pin|LED3_Pin|LED2_Pin, GPIO_PIN_RESET);  //Set pins LOW

    // Step 3: Configure pin modes. Note the use of C structures to make this more portable and readable
    GPIO_InitStruct.Pin = LED1_Pin|LED3_Pin|LED2_Pin;   //Set respective pins to be configures (only bits set HIGH are configured) 
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;         //Set mode to Push Pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;                 //No pull-up resistor
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;        //Low speed
    GPIO_InitStruct.Alternate = GPIO_AF_NONE;           //No alternative function (plan old GPIO :)
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);             //Configure!
}

//The main function - all executable C / C++ applications have a main function. This is our entry point in the software
int main() 
{
    setupGPIO();

    // ALL the repeating code is contained in a  “while loop”
    while(true) 
    { 
        // In Mbed, you turn the onboard LEDs ON using the overloaded = operator  
        //greenLED = 1;
        //blueLED = 1;
        //redLED = 1;        
        // With the HAL libraries, the equivalent is as follows:
        HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PinState::GPIO_PIN_SET);  //STM32 platform specific code
        HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PinState::GPIO_PIN_SET);  //STM32 platform specific code
        HAL_GPIO_WritePin(GPIOB, LED3_Pin, GPIO_PinState::GPIO_PIN_SET);  //STM32 platform specific code

        // Note, as they are all on the same port, you can also set them in one line with guaranteed zero skew (similar to Mbed PortOut)
        // HAL_GPIO_WritePin(GPIOB, LED1_Pin|LED3_Pin|LED2_Pin, GPIO_PIN_SET);  //Set pins HIGH

        // Wait 0.2 second (1 second = 1 million microseconds)
        wait_us(200000); 

        // Similarly, in Mbed we turn LEDs OFF again using the overloaded = operator
        //greenLED = 0;
        //blueLED = 0;
        //redLED = 0;

        // Using the HAL libraries
        HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PinState::GPIO_PIN_RESET);    //STM32 platform specific code
        HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PinState::GPIO_PIN_RESET);  //STM32 platform specific code
        HAL_GPIO_WritePin(GPIOB, LED3_Pin, GPIO_PinState::GPIO_PIN_RESET);  //STM32 platform specific code

        // Wait 0.2 second
        wait_us(200000); 
    }
}