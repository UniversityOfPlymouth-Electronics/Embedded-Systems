[Back to Contents](README.md)

---

# Multi-Tasking with Multi-Threaded Programming
In the previous sections, we met two techniques for managing multiple hardware devices:

* Rapid Polling
    * Whereby hardware is polled without blocking
    * Internal state has to be managed to keep track of changes
    * This has the disadvantage of being wasteful of CPU cycles and power, as well as becoming unwieldy as the task scales.
    * This has the benefit of being safe - there are no risks of race conditions with this approach.
* Interrupts
    * Whereby the hardware forces the CPU to branch in response to a change in the hardware.
    * This has the advantage of allowing the CPU to sleep in lower power states, only to wake when a hardware event occurs.
    * This has several disadvantages. Race conditions can easily occur and remain undetected; not many functions are interrupt safe (re-entrant).
    * Code involves out of sequence programming which can be hard to write and interpret

Both these techniques are valid and have their place. 

> Remember that this discussion started with **Blocking** (by spinning / busy-wait loop), which is arguably the simplest way to interact with hardware. 
>
> However, blocking is considered an _anti-pattern_ and is not permitted in either of these two approaches.  


There is another technique that allows use to interact with multiple devices and still use simple coding styles such as blocking whilst remaining power-efficient. 

> That technique is known as **multi-threaded programming**.

**multi-threaded programming** is a technique that allows the developer to write and execute _functions_ **concurrently**, that is, seeming to execute in parallel. 

> A **thread** is simply a function that is scheduled to run in parallel with other thread functions

This idea is not new and has been around for a long time. It was always designed to work on a single-core CPU (as we typically have in our embedded devices). This is achieved by rapid **task switching**.

> Under the hood, **task switching** is quite involved. The good news is that the responsibility for task switching is taken away from the developer so they can concentrate on writing their code. Task switching is performed by an operating system with a real-time scheduler. Mbed os is such an operating system.

* Note that automatic task switching which comes with overheads, including larger code size, memory consumption and CPU overheads.
* For complex tasks, such as networking, an RTOS is usually the best (and sometimes only) way to keep code complexity down to a manageable level.
* Hardware support for **threads** is much wider than interrupts
* Thread switching is still based on a Timer interrupt, so suffers the same risk of race conditions

## Why Mbed OS?
Mbed os is what we call a **Real Time Operating System (RTOS)**. It is C++ wrapper around the established [CMSIS-RTOS](https://www.keil.com/pack/doc/CMSIS/RTOS2/html/index.html).

The scheduler is also suited to real-time tasks, the sort we often encounter in embedded systems.

> There is nothing unusual about Mbed OS except that it allows for very rapid development. The _concepts_ you will learn are the same for other (more complex) systems. In education,we call this a _transferable skill_.

It might also be worth noting that an undergraduate student should not spend more than 20-30Hrs on a single assignment. This is less than a working week for most graduate engineers!

With that in mind, let's look at how we create some threads in Mbed OS!

## Template Code (Important)
Until this point, every project has had a small file `mbed_app.json` with the following contents:

```JSON
{
    "requires": ["bare-metal"],
    "target_overrides": {
        "*": {
            "target.printf_lib": "std"
        }
    }
}
```

This forces Mbed os to use the "bare metal" profile. This has the following implications:

* A shorter build time
* A smaller binary file
* No operating system scheduler, and hence all timer interrupts are turned off.

From this point, for each application that is multi-threaded, we will use the following profile:

```JSON
{
    "target_overrides": {
        "NUCLEO_F429ZI": {
            "target.printf_lib": "std",
            "target.components_add": ["SD"]
        }
    }
}
```

> You will find this in the project `TemplateApp-300`.
>
> If you wish to use shared mbed-os libraries, make sure you share with this project

This is no longer a bare-metal project, thus enables the scheduler. We also add support for the SD card filing system.

* Projects will take significantly longer to build (on the first occasion) and deploy to your board.
* Do not use the `sleep()` function - allow the RTOS to manage this for you

## The two-switch task
The purpose of this task is compare and contrast some of the merits of the following techniques:

* Rapid Polling
* Interrupts
* Threads


