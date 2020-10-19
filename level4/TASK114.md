[UP](Digital_Outputs_2.md)

---

# Digital Outputs
This is a first look at digital outputs with Mbed OS. Before we start, you are advised to download a copy of the module support board schematics (circuit diagram) for future reference.

[A direct link to the schematics is here](../Hardware/ModuleSupportBoard/msb_schematics.pdf)

> **TIP:** To open this link in a separate window, hold down CTRL and click. 
>
> Alternatively, the PDF file is located in the folder `Hardware\ModuleSupportBoard`

**You may be directed to the schematics**. You are encouraged to try and related what we do in software to the circuit diagrams.

## General Purpose Input Output (GPIO)
One of the most commonly used interfaces is the General Purpose Input-Output (GPIO). These are pins on the microcontroller which can be in one of the following states:

* ON (3.3V)
* OFF (0.0V)
* Not connected (_floating_)

In this section, we will be configuring pins as digital outputs. There is where the microcontroller sets the pin to one of these states. At this stage, we will only consider the output to be ON or OFF.

Consider the figure below:

* When the microcontroller pin is set HIGH, the transistor Q1 switches ON, and current can flow through it. The LED then switches on.
* When the microcontroller pin is set LOW, the transistor Q1 switches OFF, and no current can flow through it. The LED then switches off.

> When you switch a transistor fully ON, it is a bit like closing a mechanical push switch. Instead of a finger press, you use a small electrical current.
>
> A key point is that the current needed to switch the transistor ON and OFF is _much_ less than the current in the LED. This means our microcontroller is able to control many more LEDs in this way. 

<figure>
<img src="../img/circuit/micro_driving_bipolar.jpg" width="400px">
<figcaption>Microcontroller output controlling an LED via a transistor </figcaption>
</figure>

## GPIO Outputs with `DigitalOut`
We will now formally look at the type `DigitalOut`.

Let's first look at a circuit diagram from the module support board:

<figure>
<img src="../img/circuit/traffic1.png" width="400px">
<figcaption>Microcontroller output controlling an LED via a transistor </figcaption>
</figure>

Here we observe three transistors controlling three LEDs (RED, YELLOW and GREEN). The inputs are labelled as follows:

* TRAF_RED1
* TRAF_YEL1
* TRAF_GRN1

On a circuit diagram (also known as a schematic), we do not draw lines between all points on the diagram. If we did this, it would be very messy and hard to follow! Instead,we use labels to indicate which points are connected together.

| TASK-114 | Details |
| --- | --- |
| 1. | Download [schematics for the module support board](../Hardware/ModuleSupportBoard/msb_schematics.pdf) |
| 2. | Look at the first page. Find the labels listed above |
| 3. | Write down the microcontroller pins they are connected to. Hint. The pin name will begin with a `P` |
| |

[CLICK HERE FOR A HINT](../img/circuit/traffic1_mcu.png)

Hover your mouse to reveal the answers:

| LED | Pin | 
| --- | --- |
| RED | <p title="PC2">?</p> |
| YELLOW | <p title="PC3">?</p> |
| GREEN | <p title="PC6">?</p> |

As we saw in an earlier task, you can use the `DigitalOut` type to control each of the outputs. For example:

```C++
DigitalOut redLED(PC_2);
```

This will configure pin PC2 as a digital output, that is, a pin that can be asserted as OFF (0.0V) or ON (3.3V).

> Note the naming convention used in Mbed OS. We actually write `PC_2` and not `PC2`

To set this output HIGH, we simply write the following:

```C++
redLED = 1;
```
To set the output LOW, we simply assign it to 0:

```C++
redLED=0;
```

If we wished to flash the led on and off four times, we could use a while loop (as shown in the lecture):

```C++
int count = 0;
while (count < 4) {
    redLED = 1;
    wait_us(250000);
    redLED = 0;
    wait_us(250000);
    count = count + 1;
}
```

With the above, now attempt the following task.

| TASK-114 | Details |
| --- | --- |
| 4. | Watch the following video on how to create your own Mbed-OS project |
| - | https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=cecdcb02-1840-4e0f-bae6-ac5900c4d5eb |
| 5. | Create a project named TASK-114 |
| 5. | In `main.cpp`, write a program to generate the standard traffic light sequence |
| - | RED, RED+YELLOW, GREEN, FLASHING YELLOW (one and off 4 times), repeat.. |
| - | Each phase should last 2 seconds |
| - | Try and use a while-loop to implement the flashing |
|  | A solution is provided |
| |

### Initial Values
Sometimes you want the output to be in a particular state when the code starts. By default, the output will be LOW.

If you want the pin to be HIGH at start-up, then specify this as a second parameter:

```C++
DigitalOut redLED(PC_2,1);
```

| TASK-114 | Details |
| --- | --- |
| 6. | Update your solution so that ALL LEDs are on at the start (as a power-on test)  |

See Task-114-Solution to see the tutor's version.

## Multiple Outputs with `BusOut`
Having control of individual pins is central to many applications, but sometimes we want to control whole groups of pins at once.

> If you did one of the earlier stretch tasks, you might have seen  `BusOut` already. Please do this task anyway.

We will stick with the same traffic light LEDs for now to minimise any confusion and cognitive load.

| TASK-116 | Details |
| --- | --- |
| 1. | Make Task-116 your active program |
| 2. | Build the code and run in debug mode. Step through line by line |
| 3. | Using the debugger to assist you, complete the table below |
| |

| count | GREEN | YELLOW | RED |
| --- | --- | --- | --- |
| 0 | OFF | OFF | OFF |
| 1 | <p title="OFF">?</p> | <p title="OFF">?</p> | <p title="ON">?</p> |
| 2 | <p title="OFF">?</p> | <p title="ON">?</p> | <p title="OFF">?</p> |
| 3 | <p title="OFF">?</p> | <p title="ON">?</p> | <p title="ON">?</p> |
| 4 | <p title="ON">?</p> | <p title="OFF">?</p> | <p title="OFF">?</p> |
| 5 | <p title="ON">?</p> | <p title="OFF">?</p> | <p title="ON">?</p> |
| 6 | <p title="ON">?</p> | <p title="ON">?</p> | <p title="OFF">?</p> |
| 7 | <p title="ON">?</p> | <p title="ON">?</p> | <p title="ON">?</p> |

Now complete the following table. Fill in the binary equivalent of the decimal value. Some are done for you.

| Decimal | bit<sub>2</sub> | bit<sub>1</sub> | bit<sub>0</sub> |
| --- | --- | --- | --- |
| 0 | 0 | 0 | 0 |
| 1 | <p title="0">?</p> | <p title="0">?</p> | <p title="1">?</p> |
| 2 | <p title="0">?</p> | <p title="1">?</p> | <p title="0">?</p> |
| 3 | 0 | 1 | 1 |
| 4 | <p title="1">?</p> | <p title="0">?</p> | <p title="0">?</p> |
| 5 | <p title="1">?</p> | <p title="0">?</p> | <p title="1">?</p> |
| 6 | 1 | 1 | 0 |
| 7 | <p title="1">?</p> | <p title="1">?</p> | <p title="1">?</p> |
| |

Compare the two tables.

Let's look back at `BusOut`.
```C++
BusOut lights(PC_2, PC_3, PC_6);
```

When we assign a decimal value to `lights`, we see it represented in binary on the pins `PC_2` (red), `PC_3` (yellow) and `PC_6` (green).

Where we declare `lights`, three parameters (PinNames) are provided

* The first parameter is the _least significant bit_. In a weighted number system, that is the column with the lowest weighting 1 (2<sup>0</sup>). 
* The second parameter has a column weighting of 2 (2<sup>1</sup>)
* The third parameter has a column weighting of 4 (2<sup>2</sup>)

You can have up to 16 parameters with `BusOut`. You can combine **any** pins that are capable of being configured as a `DigitalOut`.

| TASK-116 | Details |
| --- | --- |
| 4. | Modify this code to count **down** from 7 (binary 111) to 0 |
| - | Hint |
|   | You will need to change the condition in the while loop and one other line |
| 5. | Now add some more outputs
| - | `BusOut lights(PC_2, PC_3, PC_6, PB_0, PB_7, PB_14);` |
| 6. | `lights` is now a 6-bit value. What is the highest decimal value of a 6-bit number? (convert 111111 to decimal) |
| 7. | Count down from the highest value to 0. Reduce the delay to 0.25s to make this quicker | 
| |

> As we are strictly using C++, you could specify the highest decimal value by writing `0b111111`. This is not possible in the C language.

## Ports and `PortOut`
The digital outputs of the microcontroller are organised into "ports". In the example above, all the pins were from `PORTB` and `PORTC`. There are a number of ports on this device, each with up to 16 pins (PORTA, PORTB, etc...)

Under the hood, `BusOut` is just a collection of `DigitalOut` types. When you assign a value, each bit is set in turn. Strictly speaking, they do not all change at once. We say the outputs are _skewed_ as they all change at slightly different times. It's very fast, so you don't notice. You would need to see an electronic instrument to observe the skew. However, it is there and for some applications this could become a problem. This is the cost of flexibility.

All pins from the same port share some circuitry and it is possible to  turn them ON and OFF at precisely the same time. For this, we can use `PortOut`.

| TASK-118 | | Details |
| --- | --- | --- |
| 1. | |Make Task-118 the active program |
| 2. | |Build the code and run to see what it does |
| 3. | |Use the debugger to step line by line to see which lines lights which LED |

Let's now look at the code in Task-118:

```C++
PortOut lights(PortC, 0b0000000001001100);

int main()
{
    //All OFF
    lights = 0;

    while (true)
    {
        lights = 0b0000000000000100;
        wait_us(1000000);
        lights = 0b0000000000001000;
        wait_us(1000000);
        lights = 0b0000000001000000;
        wait_us(1000000);                
    }
}
```

As it probably apparent, this code is less easy to read and interpret. First we create the instance of `PortOut`

```C++
PortOut lights(PortC, 0b0000000001001100);
```

* The first parameter is the port. 
* The second parameter is the "mask" - where there is a binary `1`, this signifies this pin to be an output

Therefore, as we have a `1` bit positions 2, 3 and 6, we are setting `PC_2`, `PC_3` and `PC_6` as outputs (as we did in the previous section).

To set the pins, we must also write a `1` in the correct binary position. So, to set just `PC_2` to a `1`, we must write a `1` in bit-position 2 as follows:

```C++
lights = 0b0000000000000100;
```

Note again the `0b` prefix on these numeric literal values is only valid for C++ and not C. If you use an older C compiler, you could write:

```C++
lights = 4;
```

Now complete the task

| TASK-118 | | Details |
| --- | --- | --- |
| 4. | | Modify the code to perform the following sequence |
|  | a | RED+YELLOW |
|  | b | YELLOW+GREEN |
|  | c | RED + GREEN |
| | | |


`PortOut` is not something we will use that often. It is only needed when we want switch outputs very fast and with no timing skew. For now, just be aware that both `PortOut` and `BusOut` exist.

## There is more to know... but not now
There are more ways to configure digital outputs, but these will be covered later in the course.

If you are curious, you might want to read about the following

* `DigitalInOut`
* `BusInOut`
* `PortInOut`

These type allow more advanced configurations, such as "OpenDrain", "Pull-up and Pull-down resistors" and "Bidirectional" communication.

## Quiz

[TO BE DONE]

---

[Next - Loops ](TASK116.md)