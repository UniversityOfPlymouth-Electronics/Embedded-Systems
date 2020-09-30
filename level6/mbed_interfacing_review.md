[UP - README](readme.md)

---

# Review of Interfacing in Mbed

Before we start, you should download a copy of the module support board schematics.

[A direct link to the schematics is here](../Hardware/ModuleSupportBoard/msb_schematics.pdf)

> **TIP:** To open this link in a separate window, hold down CTRL and click. 
>
> Alternatively, the PDF file is located in the folder `Hardware\ModuleSupportBoard`

**You will need to make frequent reference to the schematics**. At this level, we are encouraging the students to read the schematics and workout for themselves how to write software to control it.

## GPIO
The most familiar of interfaces is probably the General Purpose Input-Output (GPIO). 

### Task 301 - Push Pull
For a push-pull output, we use the `DigitalOut` **class**. What is a class? We will discuss this fairly soon. For now, let's look at an example using the "traffic lights".

The code in Task-301 is shown below

```C++
#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

// Objects
DigitalOut grn(TRAF_GRN1_PIN);
DigitalOut yel(TRAF_YEL1_PIN);
DigitalOut red(TRAF_RED1_PIN,1);

int main()
{
    while (true) {
        red = 0;
        yel = 1;
        grn = 1;
        wait_us(500000);
        red = 1;
        yel = 0;
        grn = 0;  
        wait_us(500000);    
    }
}
```

| **TASK 301** |
| --- |
| Read all the comments in the code. |
| 1. Build and run Task 301. |
| 2. Now run the code in debug mode |
| 3. What is the state of the red LED when the code enters main? |
| 4. Modify the code so that all the LEDs are on at the start of main |
| 5. Find the traffic lights in the schematics. Confirm these are compatible with PUSH-PULL outputs |
| |

In the example above, pins `PC_2`, `PC_3` and `PC_6` were configured as push-pull outputs.

> **Questions**
>
> If we wished to drive some 5V logic, would PUSH-PULL be a the best choice? Why?
>
> From what you observe, is the `main` function the first code that executes? Evidence your answer.
>
> Do all the LEDs change at the same time? Why?

### TASK-302-`BusOut`
In the previous example, we drive three LEDs using push-pull GPIOs. For the purpose of this task, this technique was fine. However, each LED state had to be controlled independently. Another option is to control a group of LEDs using the `BusOut` class.

The code in Task-302 is shown below:

```C++
#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

// Objects
// DigitalOut grn(TRAF_GRN1_PIN);
// DigitalOut yel(TRAF_YEL1_PIN);
// DigitalOut red(TRAF_RED1_PIN,1);
BusOut leds(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);

int main()
{
    while (true) {
        leds = 0;   //Binary 000
        wait_us(500000);
        leds = 7;   //Binary 111
        wait_us(500000);    
    }
}
```

| **TASK 302** |
| --- |
| 1. Build and run the code. |
| 2. Now run the code in debug mode and step through each line |
| 3. Determine the state of the leds when the code enters main? |
| 4. Try setting `leds` to different values | 
| 5. Write a for-loop to count from 0..7. Set the LEDs to the binary equivalent of the count. i.e. The sequence is 000, 001, 010, 011, ... , 111
| 6. Now add three more pins. The labels are `PB_0`, `PB_7` and `PB_14`. Modify the code to flash all the pins on and off.
| |

Note how the *object* `leds` was declared:

```C++
BusOut leds(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);
```

`BusOut` is the type (a class). Note the order of the parameters when initialising this object.

We can set `leds` to a decimal value, 
> **Questions**
>
> We can set the value of `leds` to an integer. Which LED represents the least significant bit of this integer?
>
> When we declare `leds`, a number of parameters are provided. These are pin names. Are the parameters specified least significant bit first, or most significant bit first? Why do you think this might be?
>
> Read the [documentation for `BusOut`](https://os.mbed.com/docs/mbed-os/v6.3/apis/busout.html). You may need to change the version to match the code. How many pins can you control at once?
>
> In step 6 above we added some additional pins. Are all the pins on the same port? Explain.

With `BusOut` you can control up to 16 pins from _any_ port. It is intended to be flexible. Under the hood, `BusOut` simply maintains an array of `DigitalOut` objects. The code iterates through the array, changing each output in turn. This means the output pins _cannot_ change simultaneously. There will therefore be a small amount of _timing skew_ between them. This is the trade-off for convenience.

### TASK-303-`PortOut`
Unlike `BusOut`, the `PortOut` class can only control pins from the same port. The reason you might want to do this is performance (especially if timing-skew is an issue).

```C++
#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2
#define LEDMASK 0b0000000001001100
// Objects
//BusOut leds(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);
PortOut leds(PortC, LEDMASK);

int main()
{
    while (true) {
        leds = 0;   //Binary 000
        wait_us(500000);
        leds = 0xFF;   //Binary 1111111111111111
        wait_us(500000);    
    }
}
```

| **TASK 303** |
| --- |
| 1. Build and run the code. |
| 2. Now run the code in debug mode and step through each line |
| 3. Determine the state of the leds when the code enters main? |
| 4. Which bits in LEDMASK are set to `1` 

Now we look at another GPIO configuration, _Open Drain_.

### Open Drain - `DigitalInOut`

## Digital Inputs

### `DigitalIn`

### `PortIn`

### `BusIn`

## Terminal Input and Output

## Timers

## Blocking

## Two Switch Challenge?


---
