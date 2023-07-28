[Back to Contents](README.md)

---

# C and C++ Structures 
In this 2-part lab, we will explore object orientated techniques in C++. We begin with structures, which feature in both C and C++. Then we move to classes, which feature in C++ and are one of the main differentiating features between the two languages.  

C++ is an "Object Orientated Language", whereas C is procedural. You can think of C++ as an extension of the C language, inheriting most of it's attributes and syntax.

In level 4, we will meet custom data types known as "Classes". First however, we need to understand C (and C++) **structures**.

| Lecture | Title |
| - | - |
| 02-01 | [02-01 - Struct Enum Union](https://dle.plymouth.ac.uk/mod/url/view.php?id=1162254) |


## Custom Types
Until now, we have use the built-in "value types", `char, short, int, long, float, double`. We can create custom types using `typedef`

```C++
typedef short int16_t
```

where `short` is an existing type and `int16_t` is the new name. In fact, some of these are already create for you, including:

* `int8_t`
* `uint8_t`
* `int16_t`
* `uint16_t`
* `int32_t`
* `uint32_t`

> If you want to revise this, [see here](../level4/TASK110.md#Platform-independent-types-and-typedef)

We will use `typedef` in combination with structures to create new complex types.

## Structures
C and C++ both have structures. These are extremely useful for packaging data into a single object.

Let's look at an example using a familiar concept: complex numbers.

```C++
typedef struct {
  double real;
  double imag;
} ComplexNumber_C;
```

Here we have created a new data type, `ComplexNumber_C`. It has two attributes `real` and `imag`. Both are type double. 

Like the built in variable types (`int, short, char,...`), we create variables using this type:

```C++
ComplexNumber_C p;
```

We can then set values for each attributes.

To set each element individually, we can use the _dot notation_

```C++
    p.real = 2.0;
    p.imag = 3.0;
```

Alternatively, we can set each element at the point we create the variable. The older style is to specify the values in the same order they are declared:

```C++
    ComplexNumber_C q = {1.0, 2.0};
```

where `p.real` is assigned the value 1.0 and `p.imag` is assigned the value 2.0.

A more explicit and modern approach is to label the attributes:

```C++
    ComplexNumber_C r = {.real = 1.0, .imag = 2.0};
```

To read the values, you simple use the _dot notation_. For example:

```C++
double y = q.real;
```

| **TASK 210** | Structures |
| --- | --- |
| 1. | Set Task-210 as your active project |
| 2. | Read the code and the comments |
| 3. | Create another complex number y |
|    | Calculate the complex sum of p and q and store in y |
|    | Use `printf` to display as a complex number (hint: you need two placeholders). |
|    | Check the answer is correct. |
| |

### Dots, Arrows, Value and Reference Semantics
One of the nice aspects of structures is how they self-document. In the example of the complex number, our code is very descriptive if meaningful attribute names are chosen.

Another useful feature is that it is very easy to copy data from one structure to another. When we use the built-in integer and floating point variable types, we take this for granted:

```C++
int a = 5;
int b = a;
```

We know that `b` will equal 5. Furthermore, we know if we then modify `a`

```C++
a = 6;
```

the value of `b` will be unaffected as they are independent. The statement `b = a` is said to use **value semantics**.

When you assign one variable to another using value semantics

* The values will be logically copied from one variable to another
* Each will remain independent of each other

We see this with structure as well:

```C++
ComplexNumber_C p = {2.0, 3.0};
ComplexNumber_C q;
q = p;
```

What will happen here is that `q` will be created separately from `p`, and each value in `p` will be copied from `p` to `q`

Any changes to `p` will not affect `q`, and equally, any changes to `q` will not affect `p`. This is value semantics. _The downside is the computational cost of the copy_, but modern compilers are very clever with minimising this.

> Note of caution
>
> This is a slightly over-simplistic assertion. If any of the attributes in `p` are reference types (such as pointers), then we get into a whole discussion about _shallow copies_ and _deep copies_.

#### Reference Semantics
Not all data types are value types. The most notable in the C language is the **pointer**. A pointer is just an integer which holds an address of either a variable or a function. On this platform, it is a 32-bit unsigned integer.

Consider this code:

```C++
ComplexNumber_C p = {2.0, 3.0};
ComplexNumber_C* ptrP;   
```

The new variable `ptrP` is not of type  `ComplexNumber_C` but is an address of another variable (of type `ComplexNumber_C`).

We can set the address to the address of another variable as follows:

```C++
ptrP = &p;
```

Now `prtP` holds the address of `p`. We can manipulate `p` via this pointer as follows:

```C++
ptrP->imag = 100.0;
ptrP->real = 200.0;
```

> Note that `p` has now been changed!

Note also the _arrow notation_. This gives us a reminder that `prtP` is a pointer type and not a value type.

You might wonder why anyone would want to do this. There are a number of good reasons, some of which will become apparent in the following sections.

> **Reference Semantics** - when we wrote `ptrP = &p;` we used reference semantics.
>
> * `prtP` and `p` are **not** independent. In fact, they refer to the exact same part of memory.
> * No values were copied (only the address was stored) 

In contrast with the dot notation, the arrow notation is often considered ugly and harder to read. C++ has a cleaner (although more ambiguous) way to implement reference semantics using _reference types_

```C++    
ComplexNumber_C& refQ = q;
```
Note the type as an `&` ampersand suffix and not a `*`. 

Here we create a variable `refQ` that is synonymous with `q`. If we change either, the other is affected. For example, if we now write the following:

```C++
refQ.real = 33.0;
refQ.imag = 66.0;
```

The structure `q` will also be updated with the same values. This is because `refQ` and `q` are really the same object in memory.

One argument against this syntax is that it is not clear from simply reading the code. It puts the responsibility of the developer to use a naming system (note I used the prefix `ref` in the variable name).

Finally, you can convert C-pointers to C++ references:

```C++
ComplexNumber_C p = {2.0, 3.0};
ComplexNumber_C* ptrP = &p;
ComplexNumber_C& nice_ptr = *ptrP;
```

Now the variable `nice_ptr` is synonymous with `p` and you can still use the dot notation.

| **TASK 211** | Value and Reference Semantics |
| --- | --- |
| 1. | Set Task-211 as your active project |
| 2. | Build the code |
| 3. | Now step through the code line by line. However, _you should try and predict the values before they are printed._ |
|    | How many did you get right? |


### Passing by value and reference
One of the great benefits of structures is the ability to package related information together and pass it between different part of your code.

On the most important examples is passing data to functions and returning results.

```C++
double complexMag(const ComplexNumber_C a)
{
    double result;
    result = sqrt(a.real*a.real + a.imag*a.imag);

    return result;
}
```

Equally, you can also return complex types from a function as shown in the following example:

```C++
ComplexNumber_C complexAdd(const ComplexNumber_C a, const ComplexNumber_C b)
{
    ComplexNumber_C result;
    
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;

    return result;
}
```

| **TASK 212** | Passing by value and reference |
| --- | --- |
| 1. | Set Task-212 as your active project |
| 2. | Build and debug through the code to understand what it does |
| 3. | [Watch this video](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=6039be0c-fd29-4590-b76d-ac5600c4404b). Now move your complex data type and associated functions into a separate CPP and header file |
| 4. | Now add the following functions and test |
| -  | complexConjugate |
| -  | complexNegate |
| -  | complexSubtract (reuse the negate and add functions) |
| -  | complexMagnitude (pythagoras!) |
| -  | complexMultiply |
| -  | complexDivide |
| -  | All these should pass by value | 
| |

We can also pass data by reference and perform in-place modification. For example:

```C++
void complexNegateInplace(ComplexNumber_C& u) {
    u.imag = -u.imag;
    u.real = -u.real;
}
```

You can invoke this function and modify a complex number as follows:
```C++
complexNegateInplace(p);
```

This function was able to modify the parameter `p` directly because it is passed a C++ reference type. You could also use C-pointers:

```C++
void complexNegateInplace(ComplexNumber_C* u) {
    u->imag = -u->imag;
    u->real = -u->real;
}
```

To invoke, the syntax must also use pointers:

```C++
complexNegateInplace(&p);
```

| **TASK 212** | Passing by value and reference |
| --- | --- |
| 5. | Now add the following functions and test |
| -  | complexConjugateInplace |
| -  | complexNegateInplace |
| -  | All these should pass by reference | 
| |


## Case Study : Two-Switch Problem as a FSM
Open Task-320 and run the code. This is another solution to the two-switch problem posed in the previous section. Test this application using the two switches.

Now Step through the code carefully. Study this code carefully to understand it.

> Question: What type of finite state machine is this? Mealy or Moore? Justify your answer.

Note how the repetition has been reduced through the use of structures.

### Enumerated Types
Notice how an enumerated type is used for the state of the finite state machine

```C++
typedef enum {
  WAIT_FOR_PRESS,
  WAITING_1,
  WAIT_FOR_REL,
  WAITING_2
} SWITCH_STATE;
```

Any variable of type SWITCH_STATE can be assigned to the literal values listed in the `enum`.

This is not essential, but helps make the code more readable.

## Quiz
Please attempt the following short quiz before moving to the next section.

https://dle.plymouth.ac.uk/mod/quiz/view.php?id=985992

---

NEXT - [Rapid Polling](rapid-poll.md)