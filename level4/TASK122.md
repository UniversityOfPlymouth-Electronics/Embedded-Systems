
[UP](Digital_Outputs_2.md)

---

# Iteration: do-while loops
Consider the code in Task-120, and the first time it runs. It is not the best example of using a `while-loop`. 

To get the code to even attempt to read the keyboard, an invalid condition was forced by initialising the following two variables as follows:

```C++
int grade=-1, hits=0;
```

In case where we need a loop to run the code **at least once**, then we should use a `do-while` loop.

| TASK-122 | Do-While-loop |
| --- | --- |
| 1. | Make Task-122 the active program |
| 2. | Build the run the code to try it, noting the changes to the code. |
| 3. | Perform the same set of tests in the previous task to confirm if this code works |

Let's now look at the code:

```C++
...
    int grade, hits;

    printf("\n\nPress Return to Start\n\n");

    do {
        //Clear out the serial port (keyboard)
        flushInputBuffer();
        //Prompt user
        printf("\nEnter grade (0..100)\n");
        //Read response
        hits = scanf("%d", &grade);
    } while ( (hits < 1) || (grade < 0) || (grade > 100) );

    //Write results
    printf("scanf found %d hits\n",hits);
    printf("Grade entered = %d\n", grade);
    greenLED = 1;
    ...
```

Note how now tests are performed the first time this code runs. 

> For a do-while, the while-statement comes at the end of the loop. This tests the condition to re-enter the loop and **NOT** the condition to leave.

Note also how the variables `grade` and `hits` were not initialised.

| TASK-122 | Do-While-loop |
| --- | --- |
| 4. | Why did we not need to initialise `grade` and `hits`? |

## Quiz
Please attempt all questions. You may need to research some of the answers.

https://dle.plymouth.ac.uk/mod/quiz/view.php?id=982847

---

[NEXT - Iteration: for-loops](TASK124.md)