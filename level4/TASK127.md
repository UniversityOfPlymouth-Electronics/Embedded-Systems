[Up - Digital inputs](Digital_Inputs_1.md)

--- 

# Digital Inputs - `BusIn`
In this section, we group individual input pins into whole binary numbers. We can consider these numbers as binary, decimal or any other base we choose of course. Decimal is the simplest.

## Using `BusIn`
We will start with a solution to the last task in the previous section.

| TASK127 | BusIn |
| --- | --- |
| 1. | Make Task127 the active program |
| 2. | Build and run the code |
| 3. | Read through the comments. If you are unsure how this works, try using the debugger to step through the code (or ask!) |
| | Note the long conditional statements in the while-loops |

Instead of having 4 separate input pins using 4 instances of `DigitalIn`, consider using a single instance of `BusIn`

| TASK127 | BusIn |
| --- | --- |
| 4. | Remove the `DigitalIn` objects and replace them with the following line |
| - | `BusIn bus(PG_0, PG_1, PG_2, PG_3);` |
| 5. | At the start of main, configure `PG_2` and `PG_3` to have internal pull-down resistors using the following code |
| - | `bus[2].mode(PinMode::PullDown);` |
| - | `bus[3].mode(PinMode::PullDown);` |

The code should now begin as follows:

```C++
#include "mbed.h"

BusIn bus(PG_0, PG_1, PG_2, PG_3);
int swVal;

DigitalOut redLED(PC_2); //Red Traffic 1

// main() runs in its own thread in the OS
int main()
{
    // Turn OFF the red LED
    redLED = 0;

    bus[2].mode(PinMode::PullDown);
    bus[3].mode(PinMode::PullDown);
    
    while (true) {
    ...
```

(where `...` indicated more code follows)

| TASK127 | BusIn |
| --- | --- |
| 6. | Modify the remaining code such that when all buttons are pressed and released, the red LED toggles state |
| - | A solution is found in main.cpp.solution |

As with `BusOut`, we treat `BusIn` as a **scalar** value and not a single bit.

## Reflection
Whether you use `DigitalIn` or `BusIn` really depends on the application.

Under the hood, `BusIn` is actually just a list of `DigitalIn` objects.

One option is to use `BusIn`, but still read individual inputs if needed. From the example above, bus[0] would only read `PG_0`, bus[1] just `PG_1` etc. This give you the best of both worlds.

On the other hand, where individual bits have specific meanings, then it might be more *expressive* / clear to use `DigitalIn` and give each a meaningful name. This makes for code that is easier to read and maintain.

Something you may have noticed and we have glossed over is the inclusion of the `wait_us` after each switch event. This is discussed next.

--- 

[NEXT - TASK 128 - Switch Debounce](TASK128.md)