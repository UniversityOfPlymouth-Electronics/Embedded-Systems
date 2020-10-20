[UP](Digital_Outputs_2.md)

---

# Iteration
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


---

[Next - Iteration: do-while loops](TASK122.md)

