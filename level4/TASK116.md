[UP](Digital_Outputs_2.md)

---

# Loops
One of the fundamental abilities of a computer is to repeat a task and make decisions.

> The concept of a loop involves both of these concepts.

We have intrinsically met one type of loop, the **while** loop. It is such an important topic, that this deserves it's own treatment.

## while loops
We use while-loops where some code needs to be repeated if a condition is met.

```C++
while (<condition>)
{
    // CODE BODY
}
```

If the `condition` is `true` (non zero), then the code body will be allowed to run. The loop will then test the `condition` again and repeat if still true.

Consider the example in `TASK-120`

```C++
int main()
{
    int grade=-1, hits=0;

    printf("\n\nPress Return to Start\n\n");

    while (hits < 1) {
        //Clear out the serial port (keyboard)
        flushInputBuffer();
        //Prompt user
        printf("\nEnter grade (0..100)\n");
        //Read response
        hits = scanf("%d", &grade);
    }

    //Write results
    printf("scanf found %d hits\n",hits);
    printf("Grade entered = %d\n", grade);
    greenLED = 1;
    
    //Loop forever
    while (true);
}
```

| TASK-120 | While-loop |
| --- | --- |
| 1. | Make Task-120 the active program |
| 2. | Build the run the code to try it, noting the prompts in the serial terminal. |
| 3. | Reset the code and try entering each of the following values: |
|  | 50 |
| | 50a |
| | 110 |
| | xx |
| | Note the outputs in each case |
| | |

What this code lacks is full "validation". 

* If a valid number is not entered, then the code tries again. This checks the value returned by `scanf` (the number of hits when searching for a decimal)
* If a value that is out of range is added (such as 110), this is allowed to go unchecked!

Now, I am sure you are a capable student but of a score of 110% is not usually possible<sup>1</sup>. We need to add some validation to also check that the value entered is in the range 0..100

<sup>1</sup>This is disputed by some football managers

It is **proposed** that the while-loop could be changed to add some additional criteria. The operator `||` is the conditional **OR**

```C++
...
    while ( (hits < 1) || (grade>=100) || (grade<0) ) {
...
```

| TASK-120 | While-loop |
| --- | --- |
| 4. | Make this modification  |
| 5. | Test the code using the following: |
|    | Invalid characters (e.g. xzy) |
|    | A valid input (e.g. 50) |
|    | Some out of range numerical values |
|    | The **edge cases** (0 and 100)
| 6. | Did you find the error and can you fix it?

This illustrates an important lesson, not just about how to construct a while-loop, but also about testing.

> Always test your code with valid values, invalid values and edge-cases (extremes) where ever possible. 

## do-while loops
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

## for-loops
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
| 6. | Change the loop code to count **down** from 7..0 |
| | |

Let's now look at the code in more detail:


---

[BACK](Digital_Outputs_2.md)

