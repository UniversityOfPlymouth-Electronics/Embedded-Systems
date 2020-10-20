
[UP](Digital_Outputs_2.md)

---

# Iteration: for-loops
In previous exercises we have seen code such as this:

```C++
        int count = 0;
        while (count <= 7) 
        {
            printf("count = %d\n", count);
            lights = count;
            wait_us(1000000);

            count = count + 1;
        }
```

This counted from 0..7, printing out the value in the terminal and displaying the binary value on the LEDs.

This is such a common programming pattern, it has a dedicated keyword, `for`

The equivalent to this code in shown in Task-124

| TASK-124 | For-loop |
| --- | --- |
| 1. | Make Task-124 the active program |
| 2. | Build and run the task to see what it does. Note the serial monitor output |
| 3. | Using the debugger, step through the code line-by-line |
| 4. | Now watch the following video |
|    | [CLICK HERE](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=bd2f576c-0a79-42eb-8aa8-ac5901172f24) |
| 5. | Change the code to declare `n` inside the loop. Replicate what you saw in the video |
| 6. | Change the loop code to count **down** from 7..0. Use the debugger to test |
| 7. | Change the loop code to count from 1..7, in steps of 2. The value of `n` should always be odd (1,3,5,7). Use the debugger to test |

## Challenge
Write some code to do the following:

* The user asked to enter a value for `pattern` - this should be a value between 0 and 7
* The user is then asked to enter a `count` - this is a value between 5 and 20
* Finally, the user should enter a value for `delay` - this is a value between 50 and 2000
* All the above should be validated (use a do-while loop)

When this is done, the program should do the following:

* The LEDs flash `count` times, alternating between 0 and `pattern` (use a for-loop for this). The delay between flashes is `delay` ms.

* The code then repeats (outer while-loop)

## Quiz
Please attempt all question. You may need to research the answers:

https://dle.plymouth.ac.uk/mod/quiz/view.php?id=982850


---

[Back](Digital_Outputs_2.md)