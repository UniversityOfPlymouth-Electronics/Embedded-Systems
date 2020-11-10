[Up - Digital inputs](Digital_Inputs_1.md)

--- 

# Switch-Case Statements (more flow control)
In this task, we look at another flow-control technique, `switch-case`. 

| TASK132 | Switch-case |
| --- | --- |
| 1. | Make Task132 the active program |
| 2. | Build and run the code. Press and hold button A to see what it does. |
| - | Press A and B together. What happens? |
| - | Press A, B and C together. What happens (and why)? |

Note we are using `BusIn` for the 4 switch inputs.

```C++
BusIn buttons(PG_0, PG_1, PG_2, PG_3);
```

This means we can read the 4 switch states as a binary number:

| bit<sub>3</sub> | bit<sub>2</sub> | bit<sub>1</sub> | bit<sub>0</sub> |
| --- | --- | --- | --- | 
|  D  |  C  |  B  |  A  |

So for example, if button A and B are pressed, this will return the value 3.

| TASK132 | Switch-case |
| --- | --- |
| 3. | Debug the code to understand how the code works both with button A pressed and released |
| 4. | Modify the code to do the following: |
| -  | If only A is pressed, the red flashes |
| -  | If only B is pressed, the yellow flashes |
| -  | If only C is pressed, the green flashes |
| -  | For all other combinations, the LEDs are all ON |

Multiple conditions can handled as follows:

```C++
...
case 1:
case 5:
//Code for BOTH case 1 and 2
break;
...
```

Here, the same code runs for both cases 1 and 5.

| TASK132 | Switch-case |
| --- | --- |
| 5. | Modify the code to do the following: |
| -  | If only A is pressed, the red flashes |
| -  | If only B is pressed, the yellow flashes |
| -  | If only C is pressed, the green flashes |
| -  | If D is pressed at all, then all LEDs flash
| -  | For all other combinations, the LEDs are all ON |


Attempt this task. Note that you will need to use multiple conditions for D.

# Quiz

Please attempt the following quiz before proceeding to the next section

[Quiz on switch-case](https://dle.plymouth.ac.uk/mod/quiz/view.php?id=993811)

---

[Up - Digital inputs](Digital_Inputs_1.md)