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

One we do this, the timer will count on it's own.

We can then read the timer value at any point. A `wait` is performed by blocking on the timer

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
> The literal value `2s` is converted into `long long` automatically using a clever C++ feature known as operator overloading.
>
> Don't worry about what this means. For now, it is enough to follow the general idea.




You should notice the LCD backlight brightness change. This is performed using digital outputs.

## PwmOut

## Using PWM to deliver variable power

