[Back to Contents](README.md)

---

# Multi-Tasking with Rapid-Polling and Interrupts
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

Here, the input is value of the timer which is reset every time more than 250ms passes.

> Note the modern API being used here. We are using the C++ std::chrono library, which overloads the following operators:
> 
> * ""ms 
> * ""us 
> * ""ns 
>
> All these do it scale the prefix value to microseconds (type `long long`)
>
> Note the type of `tm` is `std::chrono::microseconds`
>
> The header file include `using namespace std::chrono;` which saves us from 




