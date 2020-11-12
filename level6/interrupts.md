[Back to Contents](README.md)

---

# Multi-Tasking with Interrupts
We saw in the lab on rapid polling how to use a rapid polling loop to monitor inputs and update outputs at high-speed.

One argument against this approach is power-efficiency, and another is responsiveness.

* It is very hard to know what the loop time is, and what delay there will be between an input changing and the response.
* We say such systems are non-deterministic

At the heart of every desktop and portable computer is a CPU running a multi-tasking operating system. At lower levels, we would find the kernel of the operating system. Driving this are **hardware interrupts**.

One of the objectives of modern computers, and especially those which are battery powered, is to save power while maximising throughput. Most moderns CPUs and microcontrollers support at least one **sleep state**. This is a state where execution of code is paused, and selected peripherals are stopped (e.g. by disabling their clock).

> As a general rule, the more time a CPU can remain in a sleep state, so the lower the power consumption.

With this in mind, let's have a refresher of hardware interrupts on our embedded board.

> It should be noted that we are STILL using the **bare-metal** profile of Mbed. This ensures the real-time operating system (RTOS) is disabled.
>
> The reason for this is that the RTOS uses a timer interrupt, and this will keep waking the CPU. 
>
> See the file `mbed_app.json` in each project 

## Task-348 : Interrupts
This tasks reminds us of how to use interrupts to respond to external and internal hardware events. It also shows us how to put the microcontroller into a lower-power sleep state.



| TASK-348 | Interrupts in Mbed |
| --- | --- |
| 1.  | Make Task-348 the Active Program |
| 2.  | Build and run the code. Press button A to see what happens |
| 3.  | Read through the code and comments |
| 4.  | Using the debugger, put a breakpoint on the line that reads: |
| -   | `redLED = !redLED;` |
| 5.  | Allow the code to run such that the green LED is flashing. Press pause and note which line the debugger stops on. Repeat this a few times. How likely is it that the CPU is sleeping? |
| 6.  | Press button A and note where the code stops |
| 6.  | What actually called the function `funcA()` ? |

### `InterruptIn`
Note the data type for `btnA` is `InterruptIn`

```C++
InterruptIn btnA(BTN1_PIN);
```

This is very similar to `DigitalIn`, only that it allows you to attach interrupts to the associated pin.

```C++
btnA.rise(&funcA);
```

Here we request that when `btnA` rises (0->1), the function `funcA` is called automatically.

### `Ticker`
Note the type of `tick.

```C++
Ticker tick;
```

This is a hardware timer with an interrupt attached.

```C++
tick.attach(&funcTmr, 500ms);
```

Every 500ms, the timer will generate an interrupt and branch to the function `funcTmr`

### waking from sleep
The CPU spends most of it's time in the sleep mode. The **ONLY** way the CPU can wake is if a hardware interrupt should occur.

In this example, we see both GPIO and Timer based interrupts wake the CPU.

> It should be noted that although the timer interrupt is to some-extent predictable, the switch driven GPIO is NOT. The CPU has no idea when you will press the switch.
>
> We say that interrupts are **asynchronous** and run code **out of sequence**
>
> Until now, all our code has run **in sequence**, one statement following the other. Interrupts change all this as they are invoked not by our code, but via the on chip NVIC in response to asynchronous hardware events.
>
> This is a very important point which we will now look at in more details.



