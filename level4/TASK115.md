[UP](Digital_Outputs_2.md)

---

# Digital Outputs - `BusOut`
This is a first look at digital outputs with Mbed OS. Before we start, you are advised to download a copy of the module support board schematics (circuit diagram) for future reference.

[Refer to the schematics here](../getting_started/hardware.md#Schematics)

> **TIP:** To open this link in a separate window, hold down CTRL and click. 
>
> Alternatively, the PDF file is located in the folder `Hardware\ModuleSupportBoard`

**You may be directed to the schematics**. You are encouraged to try and related what we do in software to the circuit diagrams.

## Multiple Outputs with `BusOut`
Having control of individual pins is central to many applications, but sometimes we want to control whole groups of pins at once.

> If you did one of the earlier stretch tasks, you might have seen  `BusOut` already. Please do this task anyway.

We will stick with the same traffic light LEDs for now to minimise any confusion and cognitive load.

| TASK-115 | Details |
| --- | --- |
| 1. | Make Task-115 your active program |
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

| TASK-115 | Details |
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




## Quiz
Please click the link and attempt all question. You may need to research some of the answers.

https://dle.plymouth.ac.uk/mod/quiz/view.php?id=982852

---

[Next - GPIO Outputs: `PortOut`](TASK116.md)