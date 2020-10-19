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

# GPIO Outputs with `DigitalOut`
Let's now look at a circuit diagram from the module support board:

<figure>
<img src="../img/circuit/traffic1.png" width="400px">
<figcaption>Microcontroller output controlling an LED via a transistor </figcaption>
</figure>

Here we observe three transistors controlling three LEDs (RED, YELLOW and GREEN). The inputs are labelled as follows:

* TRAF_RED1
* TRAF_YEL1
* TRAF_GRN1

On a circuit diagram (also known as a schematic), we do not draw lines between all points on the diagram. If we did this, it would be very messy and hard to follow! Instead,we use labels to indicate which points are connected together.

| TASK | Details |
| --- | --- |
| 1. | Download [schematics for the module support board](../Hardware/ModuleSupportBoard/msb_schematics.pdf) |
| 2. | Look at the first page. Find the labels listed above |
| 3. | Write down the microcontroller pins they are connected to. Hint. The pin name will begin with a `P` |
| |

[CLICK HERE FOR A HINT](../img/circuit/traffic1_mcu.png)




[ IN PROGRESS ]

---

[Next - Loops ](TASK116.md)