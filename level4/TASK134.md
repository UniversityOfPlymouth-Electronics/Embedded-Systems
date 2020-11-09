[Up - Digital inputs](Digital_Inputs_1.md)

--- 

# Multiple Input Devices
In this task, we look at more complex flow-control. In this example, we have to monitor two switches.

* Press button A to count up
* Press button B count down
* Press button A and B to reset to zero

What you cannot do is simply block on one and ignore the other.

This task introduces the notion of a "rapid polling loop" and "state". We also introduce the concept of a hardware timer.

## Task-134 - The problem with blocking

| TASK134 | Multi-Inputs |
| --- | --- |
| 1. | Make Task134 the active program |
| 2. | Build and run the code.   |
| 3.  | Test the code - does it work as intended? |
| 4.  | Can you fix this code? |
| -   | Note that Task-135 starts with a partial solution |

Central to the problems with Task-135 is that the code blocks on both buttons A and B.

* While waiting for button A to be pressed, button B is being ignored
* While waiting for button B to be pressed, button A is being ignored

There are scenarios when this approach is suitable, but as soon as you need to monitor more than one device, this scheme fails.

## Task-135 - Rapid Polling without Blocking
Now we look at an alternative. This uses something known as rapid polling. The concept is as follows:

* Read all input devices without blocking (in other words, don't wait for a particular value)
* Examine the inputs 
    * If anything has changed, update the system accordingly
* Repeat at a high-enough speed so as not to miss any input changes

| TASK135 | Rapid Polling |
| --- | --- |
| 1. | Make Task135 the active program |
| 2. | Build and run the code.   |
| 3.  | Test the code - does it work as intended? |
| 4.  | Press A and B together. Note that the reset functionality is missing. Can you add it to this solution? |
| 5.  | Hint - Add another if-statement |

A few points about this code:

* it is that it is somewhat repetitive. The code for checking button A is very similar to that of button B
* it is not that easy to read due to the nested if-statements
* The switch-bounce wait is always used even when no button has been pressed


Technically, we are still blocking using this line:

```C++
wait_us(250000);  
```

This uses a **hardware timer**. The equivalent code could be written as follows:

```C++
    Timer tmr;
    ...
        tmr.reset();
        tmr.start();
        while (tmr.elapsed_time() < 250ms);
        tmr.stop();
```

As we can see here, we are blocking on a timer, waiting for it to reach a specific value. The next task shows you how to treat the timer as yet another input device (which it is!).

---

1. [NEXT - TASK 136 - Software State Machine](TASK136.md)