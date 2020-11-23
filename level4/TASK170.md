[Up -Functions and Analogue Outram](Analogue_Output_1.md)

--- 

# Functions and Scope
One of the most important topics in C and C++ programming is functions. One thing programmers do not like is repetition. Aside from making code repetitive to write, read and long, repetition repeats both code and any bugs present.

> If you fix a code in one place, and that code is replicated elsewhere, you will need to remember to fix it everywhere else as well!

## A little bit of hardware - the LATCH
Adjacent to the LCD display are three sets of 8 LEDs arranged in lines.

If we were to connecting these directly to the microcontroller, this could consume 24 GPIO pins!

As a compromise, each group of 8 shares the same data lines. In the figure before, this is labelled `dataBits`. 

The problem now is how to specify which group to control.

Some digital **latches** have been introduced to solve this problem. Each group of 8 LEDs has it's own 8-bit digital latch circuit.

> We have been using latches all the time! When we use `DigitalOut`, we set a value and then leave it. We say we "set and forget". We do not have to keep setting a pin to 0 or 1. It always remembers the last value is was set to.

Consider the figure below:

<figure>
<img src="../img/latched_leds.png" width="600px">
<figcaption>Latched LED Configuration</figcaption>
</figure>

### Latch Enable (LE)
The latch enable pin (`LE`) is central to the operation of the latch:

* When `LE` is set to 1, the output simply follows the input (`dataBits`)
* When `LE` is then set to 0, the current output value is held, and it ignores subsequent changes in the input.

So, to control the red LEDs: 

* we first ensure all `LE` inputs are 0
    * So all latches ignore the common input signal `dataBits`
* we set `dataBits` to the desired red LED bit pattern
* we set LED_RED_LE to 1 _for a short period of time_ (e.g. 1&mu;s )
* We then pull LED_RED_LE back to 0

We can then repeat the procedure for the green and blue LEDs by simply changing their respective `LE` pins.

> Remember - for any given latch, as long as the `LE` pin is low, any changes to input (`dataBits`) will be ignored.

### Output Enable
The latches in this example are similar to 8-bit variables, or "registers". They store a value internally, which if required, assert the output pins (which in turn drive the LEDs)

You can also turn off the outputs so they all go low, by disabling the **output enable (OE)**.

> Note that OE is what we call **active low**. 
> * When it is zero, the output is enabled
> * When it is one, the output is disabled.

In this circuit, all the `OE` pins are connected together so we can disable / enable all the outputs at the same time. This does not affect the internally latched values

Let's see this in action:

| TASK-170A | Functions |
| --- | --- | 
| 1.  | Make Task-170A the active program |
| 2.  | Build and run the code to see what it does |
| 3.  | Study the code, read the comments and see if it aligned with the description above |
| 4.  | Step through the code with the debugger to help you understand it if necessary |
| 5.  | Do you notice anything repetitive about this code? |

You may notice that the code is somewhat similar for the three groups of LEDs. Let's start to factor this out into separate functions.

Let's start with an example, which initialised all LEDs to the OFF state.

| TASK-170B | Functions |
| --- | --- | 
| 1.  | Make Task-170B the active program |
| 2.  | Build and run the code to see what it does |
| 3.  | Study the code, read the comments |
| 4.  | Step through the code with the debugger. When you get to the line that reads `led_init()`, click the "step in" button (or press F11) |

This demonstrated an example of a parameterless function.

* No data was passed to the function
* It was simple a way to group a sequence of programming statements into a function so it can be reused.

Very often, we pass data to a function in order to customise it's behaviour. For example:

```C++
void dispIntAsHex(int a)
{
    printf("%X\n", a);
}
```

This function accepts a single parameter `a` of type `int`. It displays this value in HEX and then returns. We would invoke this as follows:

```C++
// Literal constant
dispIntAsHex(10);
```

or maybe

```C++
int p = 10;
dispIntAsHex(p);
```

| TASK-170B | Functions |
| --- | --- | 
| 5.  | Modify `led_init()` to take an unsigned integer as a parameter |
| -   | Use this value to set the initial value of all the latches. |
| 6.  | Add a second parameter of type `bool`. When set to `true` the outputs should switch on, otherwise they should remain disabled |
| -   | Test your code with the debugger |
| -   | See solution-1.txt if you are stuck |


There is more code that is repetitive. Consider the code to set the latch value for the red LEDs:

```C++
        //Update the red
        wait_us(1);
        dataBits = 0xFF;    //Set the 8-bit data pattern
        wait_us(1);
        LED_RED_LE  = 1;    //Copy dataBits to red latch outputs
        wait_us(1);         
        LED_RED_LE  = 0;    //Ignore inputs (dataBits)
        wait_us(1);
```

This is very similar to the green and blue LEDs.

| TASK-170B | Functions |
| --- | --- | 
| 6.  | Can you write a function to set the latch value for a given set of LEDs? |
| -   | Hint: |


