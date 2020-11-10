[Up - Digital inputs](Digital_Inputs_1.md)

--- 

# First Look at Interrupts
In this task, we we hand flow-control back to the CPU. This might sounds strange, but it is the basis of the computer you are probably reading these notes on.

The mechanism is known as **hardware interrupts**. 

> **PLEASE READ**
>
> Before we go any further, it is IMPORTANT to understand the following:
>
> Interrupts are an advanced technique which should **NEVER** be used unless you know how to use them correctly and **safely**
>
> Interrupts introduce the risk of bugs which are famously difficult to spot, even if you know about them. **Rapid polling should be your default choice in year 1.**
>
> I am showing you interrupts purely for information. In year 2 we will learn how to use them safely.

| TASK138 | Interrupts |
| --- | --- |
| 1. | Make Task138 the active program |
| 2. | Build and run the code. |
| -  | Observe the serial output |
| -  | Press and release switches A and B |
| 3. | Find the code that changes the leds |

Let's look at this code more closely.  First, the main while-loop:

```C++
    while (true) {
        sleep();

        printf("I have been woken %d times\n", ++counter);
    }
```

There is very little code in here. 

* The statement `sleep()` puts the CPU into a low power state.
    * In effect, it stops running any code
* Only a "hardware interrupt" can wake the CPU again

So what is waking the CPU? One of three things:

* pressing button A
* releasing button B
* a hardware timer

All these three operate independently of the CPU. When the CPU sleeps, these devices continue to operate. There is electronics inside the CPU that can detect when specific events occur and can wake the CPU from sleep.

> But there is more...
> 
> It does not just wake up from sleep. It does something else, and that is "branch"


| TASK138 | Interrupts |
| --- | --- |
| 4. | Find the code that toggles the red LED, and put a breakpoint on it |
| 5. | Do the same again, but for the yellow LED |
| 6. | Run the code in debug mode and click the continue button until the green LED flashes |
| 7. | Press button A - what happens? |
| 8. | Click continue - the green LED should flash again |
| 9. | Press and release button B - what happens? |

> **Note** If you try and single step the code, the debugger may lose connection and crash.

Let's look at what is going on here. First, we are not using `DigitalIn` to read the switches. We are also not using `Timer` to read the timer. Instead we are using `InterruptIn` and `Ticker` as follows:

```C++
InterruptIn btnA(BTN1_PIN);
InterruptIn btnB(BTN2_PIN);
Ticker tick;
```

Next, we configure these as follows:

```C++
btnA.rise(&funcA);
```
This instructs the microcontroller to detect a rising edge (transition from 0->1), and to automatically branch to the code at address `&funcA` 

```C++
btnB.fall(&funcB);
```
This instructs the microcontroller to detect a falling edge (transition from 1->0), and to automatically branch to the code at address `&funcB` 

```C++
tick.attach(&funcTmr, 500ms);
```
This instructs the microcontroller to automatically branch to the code at address `&funcTmr` every 500ms 

The code at these addresses is shown below:

```C++
void funcA()
{
    redLED = !redLED;
}

void funcB()
{
    yellowLED = !yellowLED;
}

void funcTmr()
{
    greenLED = !greenLED;
}
```

Like variables, as programmers we don't usually concern ourselves with the actual addresses and use names. When the address is referring to some program code, we call it a **function**.

We will talk a lot more about functions later in the course.

---

[Up - Digital inputs](Digital_Inputs_1.md)




