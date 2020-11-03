[Up - Digital inputs](Digital_Inputs_1.md)

--- 

# If Statements (and flow control)

This section discusses one of the most commonly used language features of any programming language: **flow control**. Flow control is the basis of decision making in software - it is what allows computers to make decisions based on the external environment and react accordingly. 

> It is also quite common that some or even all of the "business intelligence" in modern electronic systems lies in the embedded software

We have already met some flow-control in the `while` and `do-while`, but these are focused on repeating blocks of code while certain conditions are met.

A more general construct is the **if statement**

To support the lecture materials, let's look at this through examples as at a fundamental level, they are not difficult to understand.

## Simple if statement
In this task, you have a single if-statement that runs a block of code when switch A is pressed.

| TASK130 | If |
| --- | --- |
| 1. | Make Task130 the active program |
| 2. | Build and run the code. Press and hold button A until it exceeds 99 |
| 3. | What is the problem here? |

Let's talk through this as there are some key points to highlight. 

In the code, there is a while-loop which repeats the same code forever. This is sometimes referred to the _main loop_. We will look at the code inside this main while-loop.

Firstly, there is reading the switch
```C++
        //Read button without blocking
        int btnA = ButtonA;  
```

This is performed each time the main loop repeats. Note that we only read (which is a fast operation) and then store the result in a variable `btnA`.
_We are no longer waiting for the button to be pressed_

> Do you remember the terms _blocking_ and _spinning_?. We are not doing this.

Having read the switch and noted it's state, we can then decide what to do:

```C++
        //Test Button A
        if (btnA == 1) {
            redLED = !redLED;    //Toggle RED led
            count++;            //Increment count
            disp = count;       //Update display
        }
```
Again, _each time_ the main loop repeats, we check if the button has been pressed using an **if-statement**. 

* If it has, then the code block (in curly braces) is allowed to run. 
* If not, the code block is skipped.

> **Equality Operator `==`**
>
> Note the difference between the assignment operator `=` and the test for equality `==`
>
> As you might be able to guess, these two can easily get confused!

| TASK130 | If |
| --- | --- |
| 4. | Use debug mode to confirm the above. Step through the code, once while holding down button A and again without |

## The code block and local scope
Code blocks are code enclosed between and open brace `{` and a matching closing brace `}`. We have seen code blocks before of course.

* while-loops
* do-while loops
* for-loops
* Note also the main function has some
* We also use code-blocks with if-statements.

We can even write them without any of the above, but why would we?

Inside the code block, you can write any valid C or C++ code you wish. There is something important to be aware of however, and this is known as **scope**.

* Any variables you create inside a code block will **only** exist with the block

* They can be "nested". 
    * The outer-most block is the main function
    * Then we have the main while-loop within it
    * Within that, we have the if-statement (the inner-most scope)

* Each block is said to have it's own *local scope*. We sometimes also say *inner-scope*
    * Variables created within a local scope exist within that scope.
    * They are not visible to the outer (enclosing) scope (and may not exist in memory)
    * Variables in an outer (enclosing) scope can be accessed from an inner scope

For example:

* The variable `btnA` is created within the main while-loop. It can be accessed from anything within the while-loop, but not outside.
* The variable `count` is created within the main function. It can be accessed with both the while-loop and the if-statement. 

> You can even write a code block without any flow control or functions. Just enclose some code between `{` and `}` and anything you create within it will have it's own private scope. Handy for forcing variables to be deleted from memory or reusing variable names.

## Add a button
Currently the task counts up while you hold down button A. We also want to use button B to do count down

| TASK130 | If |
| --- | --- |
| 5. | Add some code to check for Button B being pressed. If it is, decrement the count and update the display. |
| - | You can mostly replicate the code that is already there |
| - | Do not nest your if-statements. Do not use any `else` keywords |


## Mutual exclusion with if-else
So far, we are able to control the counter to count up, down or both. Let's add a small refinement.

| TASK130 | If |
| --- | --- |
| 6. | Press both button A and B at the same time. What happens? |


If you followed the instructions in 5., the count should not change. 

* Each if-statement should counter act the other. 
* The red LED will also stop flashing.

If you write one if-statement after the other, then both are tested and both blocks may run:

```C++
if (<conditionA>) {
    //Block A
}

if (<conditionB>) {
    //Block B
}
```

Sometimes, you want **mutual exclusion**, whereby only one block must run. For this, we can use **if-else if**

```C++
if (<conditionA>) {
    //Block A
}

else if (<conditionB>) {
    //Block B
}

...next statement...
```

In this example, `conditionA` is tested first. 
* If it is true, Block A will run and the code will skip to the next statement
* If it is false, then `conditionB` will be tested
    * If it is true, Block B will run.
* **There is no possibility of both Block A and Block B running**
* Block A also has precedence over Block B

One additional `else` keyword makes a significant difference!


| TASK130 | If|
| --- | --- |
| 7. | Change the code so that if both are pressed, the default is to count up. Use else-if and given precedence to button A |
| - | A solution is given in `main.cpp.solution1` |

## Catching all other conditions with `else`
We can extend the concept of `else if` further with what is sometimes called a "catch-all". To explain, consider the pseudo-code below:

```C++
if (<conditionA>) {
    //Block A
}

else if (<conditionB>) {
    //Block B
}

else {
    //Block C
}
```

The difference here is the `else` statement. **Block C will run if none of the conditions above are met**.

Note again the precedence:

Condition A is tested first. If not met, condition B is tested. If that is not met then Block C runs by default

| TASK130 | If|
| --- | --- |
| 8. | Change the code so that if neither button is pressed, the green LED flashes |

It is worth noting that the most common code tends to be of the form:

```C++
if (<conditionA>) {
    //Block A
}
else {
    //Block C
}
```

## Nested If-Statements
There is a logical error (aka bug) in this code that needs addressing:

* The count is able to overflow (above 99) or underflow (below 0). 

| TASK130 | If|
| --- | --- |
| 9. | Add some additional if-statement to prevent count from overflowing or under-flowing |

## Inline conditionals
These are not my favourite syntax, but they exist and can be used appropriately.

The incline conditional is written as follows:

<condition> ? <true expression> : <false expression>

For example, we could write:

```C++
        if (btnA == 1) {
            redLED = !redLED;    //Toggle RED led
            count = count + ( (count<99) ? 1 : 0 );            
            disp = count;       //Update display
        }
```

| TASK130 | If|
| --- | --- |
| 10. | Modify the count down code to use an in-line conditional to prevent underflow |

## Reflection
There is more than can be said about conditional statements. They are very fundamental to adding decisions in out code (and hence the devices we build). 

A common error is to confuse a sequential list of if-statements with `if - else if`. Make sure the concept of mutual exclusion is clear and when to use `else if` and when not to.


## Challenge
The code above uses two switches. 

* Use `BusIn` instead and try to simplify the code
* Change the behaviour such that:
    * Button A increments the count
    * Button B decrements the count
    * Both Buttons A and B reset the count to 0


# Quiz
Please attempt the following quiz before proceeding to the next section
[Quiz on if-else](https://dle.plymouth.ac.uk/mod/quiz/view.php?id=993808)

---

[NEXT - TASK 132 - Switch Statements](TASK132.md)
