[Up -Functions and Analogue Outram](Analogue_Output_1.md)

--- 

# Pulse Width Modulation
In previous exercises, we have used digital outputs in Mbed to drive LED circuits, or even make them flash. 

## Delays and the Timer Class
One of the most important tasks in an embedded system is to implement accurate delays. We have already used functions such as `wait_us`, but how do they work?

Build into the microcontroller are a number of **hardware timers**. These are counters which can be configured to run independently.

Let's look at the basic use of Timers to replicate the `wait_us` function:

| TASK-176 | Timers |
| --- | --- |
| 1. | Make Task-176 the active program |
| -  | Build and run. Watch the LCD screen |
| 2. | Adjust the blue potentiometer to see what it does |

## Implementing a wait using `Timer`
At the start of the code, we see the `Timer` being created and stated:

```C++
Timer tmr;
tmr.start();
```

Once we do this, the timer will count on it's own, even if the CPU enters a sleep state.

We can then read the timer value at any point. A `wait` is performed by blocking on the timer:

```C++
while (tmr.elapsed_time() < 2s);
```

This loop will spin until the timer value equals or exceeds `2s`. We say it is **BLOCKING**.

> **A note about C++ and Time**
> 
> Although nice to read, you might be wondering how this works.
>
> `tmr.elapsed_time()` returns a value of type `std::chrono::microseconds`, which turns out to be just a `long long` integer.
>
> The literal value `2s` is converted into `long long` automatically and scaled using a clever C++ feature known as operator overloading.
>
> Don't worry about what this means. For now, it is enough to follow examples and understand the general idea.

## Rapid Polling and Timers
Timers are devices, and in effect, mostly considered input devices. We do not have to block on a timer to read it's value.

A useful design pattern is rapid polling, and although was covered in a previous exercise, is something worth repeating.

The concept of rapid polling is as follows:

* Read the 'state' of all input devices WITHOUT blocking
* Update internal state and outputs
* Repeat at high enough speed to avoid missing any deadlines

What do we mean by state? In essence, where we are following a sequence, it's a number which indicates what point we have reached in the sequence.

We see this concept being used for the LCD backlight. The signal driving the LCD back-light is depicted below.

* The signal is ON for a proportion of the time Ton/Tp
* The rate of switching is too fast for the human eye to notice (Tp is equal to 1ms or less)

<figure>
<img src="../img/fsm-pwm.png" width="600px">
<figcaption>Pulse width modulation signal for controlling the LCD backlight (upper); Finite state diagram for the code (lower)</figcaption>
</figure>

The diagram below is the _finite state diagram_. 

<figure>
<img src="../img/fsm-pwm-states.png" width="600px">
<figcaption>Pulse width modulation signal for controlling the LCD backlight (upper); Finite state diagram for the code (lower)</figcaption>
</figure>


> The _state_ is just a variable that is equal to 0 (OFF) or 1 (ON)

* When in state ON


```C++
typedef enum {OFF, ON} LCD_STATE;
LCD_STATE state = ON;
```

```C++
while(true) {
    
    switch (state)
    {
        case ON:
            if (tmr.elapsed_time() > (Ton*1ms)) {
                state = OFF;
                dispBackLight = 0;
            }
            break;

        case OFF:
            if (tmr.elapsed_time()>=1ms) {
                state = ON;
                dispBackLight = 1;
                Ton = pot;
                tmr.reset();
            }
            break;
    }

}
```

You should notice the LCD backlight brightness change. This is performed using digital outputs.

## PwmOut

## Using PWM to deliver variable power

