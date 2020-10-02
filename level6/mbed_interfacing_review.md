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
| 4. Which bits in LEDMASK are set to `1` and why? (see the documentation on `PortOut`) |
| 5. Change `LEDMASK` to `0b0000000001001000`. What effect does this have and why? |
| 6. Now modify the code to also flash the on-board LEDs. The pin labels are `PB_0`, `PB_7` and `PB_14`. _hint_: You will need another instance of `PortOut` | 
| 7. Modify the code to flash the LEDs using the XOR operator `^`. Your while-loop should only need two lines of code within the code block. **<p title="leds = leds ^ LEDMASK; wait_us(500000);">Hover here to see the solution</p>** |
| |

We saw in this exercise that `PortOut` is used to set outputs bits on a particular port. All pins will change simultaneously.

Now we look at another GPIO configuration, _Open Drain_.

### TASK-304 - Open Drain with `DigitalInOut`
The module support board you are using has two set of "Traffic Lights", purposely configured in a slightly different way. Let us first consider Traffic Light Set 1:

<figure>
<img src="../img/circuit/traffic1.png" width="300px">
<figcaption>Traffic Light Set 1. Note the use of the NPN transistor.</figcaption>
</figure>

We can write a truth table for this circuit where `TRAF_RED1` is the input and the LED state is the output.

| `TRAF_RED1` | TRANSISTOR STATE | LED STATE |
| --- | --- | --- |
| LOW | OFF | OFF |
| HIGH | ON | ON |
| FLOATING | ? | ? |
| |

This is your standard "push-pull" configuration. We used this circuit in a previous exercise. Now compare and contrast to Traffic Light Set 2:

<figure>
<img src="../img/circuit/traffic2.png" width="300px">
<figcaption>Traffic Light Set 2. Note the use of a PNP transistor.</figcaption>
</figure>

This circuit is different. Study it carefully, then consider the following question.

> **Question**
>
> For Traffic Light Set 2, try and complete the table. Hover the mouse over the `?` to reveal the answers.
>
> | `TRAF_RED2` | TRANSISTOR STATE | LED STATE |
> | --- | --- | --- |
> | LOW | <p title="ON">?</p> | <p title="ON">?</p> |
> | HIGH | <p title="OFF">?</p> | <p title="OFF">?</p> |
> | FLOATING | <p title="OFF">?</p> | <p title="OFF">?</p> |
> | |
>

To better understand this, it is helpful to look at the electronics for a GPIO pin:

<figure>
<img src="https://os.mbed.com/media/uploads/tbjazic/05outputs.png" width="400px">
<figcaption>Digital outputs of a microcontroller can be configured as standard (typically push-pull) or open-drain outputs. Source: https://os.mbed.com/media/uploads/tbjazic/05outputs.png</figcaption>
</figure>

Note how in the open-drain configuration, there is no "push" transistor (in reality, both transistors would be present with the upper one held off). 

It should be stated that different devices can offer different configurations. You should always check the device documentation. 

> **NOTE**
>
> Some devices also include the option to include internal Pull-Up and Pull-Down Resistors. This can save external circuitry, although we need to be careful about current limits. We will not be using this and not all devices provide this option.

In the sample code below, the output pin is initialised as `OpenDrainNoPull`:

```C++
#define TRAF_GRN2_PIN PC_9
#define TRAF_YEL2_PIN PC_8
#define TRAF_RED2_PIN PC_7

#define TRAF_WHITE_PIN PF_10

//BusInOut Traffic_Lights_2(PC_7,PC_8,PC_9);
DigitalInOut grnLED(TRAF_GRN2_PIN, PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 0);

int main()
{
    //Note the logic
    while (true) {
        grnLED = 1;
        wait_us(1000000);
        grnLED = 0;
        wait_us(1000000);
    }
}
```

Note the following:

The `grnLED` object is initialised with 4 parameters. 
```C++
DigitalInOut grnLED(TRAF_GRN2_PIN, PinDirection::PIN_OUTPUT, PinMode::OpenDrainNoPull, 0);
```

* `TRAF_GRN2_PIN` is the pin label
* `PinDirection::PIN_OUTPUT` specified this is in output mode (you can also configure it for input mode).
* `PinMode::OpenDrainNoPull` sets the output configuration to OPEN DRAIN, with no internal pull-up or pull-down resistors
* The default output state is LOW

| **TASK 304** |
| --- |
| 1. Build and run the code. |
| 2. Now run the code in debug mode and step through each line |
| 3. Determine the state of the leds when the code enters main. Explain. |
| 4. Without using copy and paste, add another open-drain output for `TRAF_GRN2_PIN` and make it flash in the opposite state to the green. 
It is important you type this in yourself (slowly) and note how the autocomplete helps you see all the options available |
| 5. In your source code, right click `PinMode` and select "Go to Definition". This will open the header file with the definition of this type.

Learning to use autocomplete and to explore the Mbed sources is a valuable skill.

## Digital Inputs

### `DigitalIn`

### `PortIn`

### `BusIn`

## Terminal Input and Output

## Timers

## Blocking

## Two Switch Challenge?


---
