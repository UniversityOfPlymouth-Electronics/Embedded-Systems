[Back to Contents](README.md)

---

# Multi-Tasking with Rapid-Polling
If you remember back to the level 5 course, one of the challenges was with managing multiple devices at the same time.

> Blocking has been recognised as a problem for computers for many years. In the absence of an alternative strategy, simply waiting on a device to change state can mean ignoring other device I/O, which can lead to data loss or integrity errors.

Today, when you buy a personal computer, it is likely to contain a CPU with multiple cores. This is a relatively recent innovation and is aimed at increasing throughput. Most embedded processors have just one core, so can only execute one instruction at a time. So how have we managed to handle the large number of devices a CPU has to interface and service? The answer lies in the term **multi-tasking**

> **Multi-tasking** is not new in computing, and _was originally developed to solve the problem of blocking hardware_. Only later was it also used as a way to utilise multiple cores (in modern CPUs) to increase throughput.

For the remainder of this module, we mostly focus on techniques to implement multi-tasking. These include:

* **Rapid Polling** - whereby we take responsibility for servicing all devices. We read input devices and service output devices at high enough speeds to prevent data loss or corruption.
* **Interrupts** - whereby we utilise hardware-interrupts and the "Nested Vectored Interrupt Controller" (NVIC) to react to hardware events (whilst also saving power).
* **Multi Threaded Programming** - using the Mbed Real Time Operating System components (based on CMSIS RTOS) to handle multi-tasking for us, so that we are able to write separate functions (containing sequential code) that "seems" to run in parallel, even on a single core. Using this method, we go full circle and discover we may use simple blocking code once again!

Let's begin with the concept of rapid-polling.

## Rapid Polling Loops
Rapid polling loops are simple in concept, but can be tricky and messy to write. The concept is as follows:

1. Read all inputs and store the results.
2. If the inputs have changed, update the state and maybe some of the (Mealy) outputs
3. Depending on the state, update the (Moore) outputs
4. Repeat the above such that inputs and outputs are serviced at a sufficient speed to prevent data loss or corruption.

This is probably explained with some examples. The first is a simple application which uses two buttons to increment or decrement a counter.

## Task-344 - Rapid Polling
In this task, you will have three input devices controlling two outputs.

**Inputs**
* Button A - Increments the count
* Button B - Decrements the count
* Hardware Timer - Sets the flash rate of the green LED

**Outputs**
* 7-Segment Display - displays a count
* Green LED - flashes twice a second

| TASK-344 | Rapid Polling |
| --- | --- |
| 1. | Make Task-344 the Active Program |
| 2. | Build and run. |
| -  | Press A a few times to increment the count |
| -  | Press B a few times to decrement the count |
| -  | The green LED should flash in the background |
| 3. | Using the debugger, step through the code to try and understand how it works |
| 4. | Modify the code so that the `count` controls the flash rate. |
| -  | Count ranges from 0..99 |
| -  | Flash rate should range from 100 ms to 1000ms |
| -  | Note the type of `tm` is `microseconds` |
| -  | If stuck, you can take a look at `solution.txt` |

> **Note**
>
> The modern API being used here. We are using the C++ `std::chrono` library, which overloads the following operators:
> 
> * ""ms 
> * ""us 
> * ""ns 
>
> What these do is scale the prefix value to microseconds (type `long long`)
>
> Note the type of `tm` is `std::chrono::microseconds`
>
> The header file include `using namespace std::chrono;` which saves us from writing the `std::chrono::` prefix.

Let's look at some key points inside the main while-loop:

**Read inputs without blocking**

The first action is to read the inputs as fast as possible. We see this in the following three lines:
```C++
    btnA_curr = buttonA;
    btnB_curr = buttonB;
    tm = tmr.elapsed_time();
```

**If an input changed, update the internal state and outputs**

### Button A
Considering switch A, the following code does just this:
```C++
// Did button A change?
if (btnA_curr != btnA_prev) {

    //Was it a press?
    if (btnA_curr == 1) {
        //Button A was pressed!
        if (count < 99) {
            count+=1;
        }
    }

    // The previous value is now set to the current
    btnA_prev = btnA_curr;

    //**************
    //Update display
    //**************
    disp = count;      
}
```

Note how we first check to see if the button value has changed. 
```C++
if (btnA_curr != btnA_prev) {
    ...
```
The internal state is comprised of `count` (the count value) and `btnA_prev` (the previous value of the switch). If the button equals 1, this must be a *rising edge* (switch press). In such cases, the internal state is updated:

```C++
if (btnA_curr == 1) {
    //Button A was pressed!
    if (count < 99) {
        count+=1;
    }
}

// The previous value is now set to the current
btnA_prev = btnA_curr;
```

Finally, the output is updated:
```C++
disp = count;
```

### Button B
Button B is almost the same as A, so you can read the source and you should see the same pattern used.

Note: 
* `count` is common to both
* The previous value is unique to the button

### Timer and Flashing LED
For the flashing LED, the input device is the timer. This counts independently of the CPU.

The code is very short:

```C++
    if (tm >= 250ms) {
        greenLED = !greenLED;
        tmr.reset();
    }
```

Here, the input is value of the timer which is reset every time more than `250ms` passes.

### Reflection
Some points to consider.

When no buttons are pressed, the while loop repeats at a high speed so as not to miss any inputs. However, to manage switch bounce, a simple wait is added at the end. This is a bit crude as it blocks for 50ms. We were trying to remove blocking!

This delay noticeably slows the loop time, but luckily not enough to notice. It might mean the green flash rate is not particularly accurate. 

An improvement would be to poll two more timers, one per switch and remove blocking entirely. This is the purpose of the next task. This change is going to add more complexity to our code however.

## Task-346 - Using a State Machine pattern
We will now remote any blocking code from the previous task. So that the code does not become too complex, a state machine is used for each input/output combination. In fact we employ 3 state machines.

> A state machine allows us to keep track of where we are in a sequence. As you will see, this removes the need to record the previous input values and we can avoid blocking entirely.

| Task-346 | Using a State Machine for Rapid Polling |
| --- | --- |
| 1.  | Make Task-346 the active program |
| 2.  | Build and run the code |
| -   | Press A and B to see the count change. Note the flashing green LED is unaffected |
| 3.  | Use the debugger to step through the code to make sure you understand it |

Inspecting the code, it is fairly repetitive. The two state machines used for buttons A and B are almost identical. 

> Each state machine has a switch (`DigitalIn`) and a timer (`Timer`).
>
> The other difference is what happens when a switch is pressed. One increments and the other decrements.

### Challenge
Write a C++ class that encapsulates all the behaviour of the switch-timer state machine. 

> Use composition to encapsulate a `Timer`, `DigitalIn`
> Use this class to simplify and shorten the code

The next task as one possible solution.

## Task-427
This task contains one possible solution to the challenge in the previous task.

| Task-347 | Using a State Machine for Rapid Polling |
| --- | --- |
| 1.  | Make Task-347 the active program |
| 2.  | Build and run the code |
| -   | Press A and B to see the count change. Note the flashing green LED is unaffected |
| 3.  | Use the debugger to step through the code to make sure you understand it |
| 4.  | Now write another class to encapsulate the logic needed for the flashing green LED |
| -  | Write the class |
| -  | Instantiate and test for the Green LED |
| -  | Add instances for the red and yellow LED |
| -  | Make them all flash at different rates |

A solution is provided (Task427B-Solution). Note how the code is easily reused by encapsulating logic in a class.

## Reflection
That is all I want to do with rapid polling. There are a few observations that need to be summarised:

* Rapid polling is a technique that allows us to manage multiple input/output devices without blocking
* The rate at which the inputs are sampled needs to be high enough to avoid missing events. 
* The rate at which the inputs are sampled is determined by the loop time and is variable.
* The technique is not power efficient. The CPU is typically running at full speed even when nothing is being updated.
* The code can easily become verbose and complicated. C++ was used to reduce repetition, but is not easy to write or debug.

Saying all this, rapid polling is a valid technique. In terms of power, this class of microcontroller still uses very little power even when running at full speed. 

* If this was part of a control system where other devices are consuming power in the order of Watts (or kWatts even!), then a few mW of additional power makes little difference.
* However, if this is part of a batter powered device that needs to run on a coin cell for many months, then this is significant.

This technique is also unsuited to sampling and analogue to digital conversion. This is because it is very hard to obtain a fixed sampling rate (loop-time is rarely a known constant).

Next, we loop a more sophisticated solution, **hardware interrupts**.

---

[NEXT - Lab6-Interrupts](interrupts.md)


