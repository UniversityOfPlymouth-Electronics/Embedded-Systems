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

