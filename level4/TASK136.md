[Up - Digital inputs](Digital_Inputs_1.md)

--- 

# Software State Machine
In this task, we continue to look at more complex flow-control, but this time, we adopt what is known as a "design pattern"

> A design pattern is a standard solution to a well known problem
>
> If it good to use design patterns as it prevents you from re-inventing the solution 

We continue with the previous task

| TASK136 | State Machine |
| --- | --- |
| 1. | Make Task136 the active program |
| 2. | Build and run the code. Test button A and B   |
| 3. | Read through the code. Use the debugger to try and understand how it works |
| 4. | How many input devices are there?  |
| -   | <P title="4">Hover here to reveal the answer</P> |

Note how button A and button B each have their own timer, and can operate independently of each other.

Key to this is avoiding any blocking by reading the inputs without waiting:

```C++
    btnA = buttonA;
    btnB = buttonB;
    timeA = tmrA.read_ms();
    timeB = tmrB.read_ms();
```

For each button-timer combination, we then keep track of where we are in the press-wait-release-wait cycle and react accordingly:

```C++
        switch (stateA) {
            case WAITING_FOR_PRESS:
                if (btnA == 1) {
                    stateA = DEBOUNCE_1;
                    tmrA.reset();
                    tmrA.start();
                    if (count < 99) {
                        disp = ++count;
                    }
                }
            break;

            case DEBOUNCE_1:
                if (timeA >= 250) {
                    stateA = WAITING_FOR_RELEASE;
                    tmrA.stop();
                }
            break;

            case WAITING_FOR_RELEASE:
                if (btnA == 0) {
                    stateA = DEBOUNCE_2;
                    tmrA.reset();
                    tmrA.start();
                }
            break;

            case DEBOUNCE_2:
                if (timeA >= 250) {
                    stateA = WAITING_FOR_PRESS;
                    tmrA.stop();
                }
            break;            
        }
```

We keep track of where we are using an integer `stateA`. There are 4 possible "states":

0. Waiting for a switch to be pressed
1. Waiting for the rising-edge switch noise to clear
2. Waiting for a switch to be released
3. Waiting for the falling-edge switch noise to clear

Instead of using a regular integer, it is common place to use an **enumerated type**. In this code, `stateA` is of type `SWITCH_STATE`, which is defined as follows:

```C++
    typedef enum {WAITING_FOR_PRESS, DEBOUNCE_1, WAITING_FOR_RELEASE, DEBOUNCE_2} SWITCH_STATE;
```

By default:

* `WAITING_FOR_PRESS` is equivalent to `0`
* `DEBOUNCE_1` is equivalent to `1`
* `WAITING_FOR_RELEASE` is equivalent to `2`
* `DEBOUNCE_2` is equivalent to `3`

Using an **enumerated type** makes the code more readable and to some extent safer. Underneath, it is just an integer.

> The key point here is that nowhere in this code do we block. The pattern of "read inputs -> update state -> update outputs" is enforced to ensure that all the inputs are read at a speed that ensures nothing is missed.

## Refection
Note again how repetitive the code is. This will be addressed when we learn about **functions**.

How often do we sample the inputs? Very fast is the simple answer, but the exact frequency is hard to control and tends to vary depending on the loop time. This may not matter in this application, but for others, it might.

This coding style is reasonably clear, but what is we want to detect both buttons being pressed? Currently the code for buttons A and B are kept purposely separate. 
This clean separation will begin to diminish if you wish to look at that case (although there are ways to do it).

One of the key issues with this style is that it is very power-inefficient. It keeps the main while-loop running at full speed, often doing nothing. Until someone presses a button, nothing changes, yet the CPU runs flat-out all the time.

In the next section, we learn about an important alternative that is much more power and CPU efficient, and that is **interrupts**

---

[NEXT - TASK 138 - First Look at Interrupts](TASK138.md)