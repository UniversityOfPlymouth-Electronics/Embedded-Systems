[Back to Contents](README.md)

---

# Table of Contents

- [C and C++ Object Orientated Programming](#c-and-c-object-orientated-programming)
- [Related Lectures](#related-lectures)
- [Function overloading](#function-overloading)
   - [Overloaded Constructors](#overloaded-constructors)
   - [Overloaded Member Functions](#overloaded-member-functions)
- [Operator Overloading](#operator-overloading)
   - [Unary Operators](#unary-operators)
   - [Binary Operators](#binary-operators-2-parameters)
   - [Type Operators](#type-operators)
   - [Challenge](#challenge)
   - [Reflection](#reflection)
   - [Mbed OS Example](#mbed-example)
   - [Further Reading](#further-reading)
- [Class Inheritance](#class-inheritance)
   - [Inheritance with Mbed](#overriding-with-mbed)
   - [Reflection](#reflection-1)
   - [Function Overrides](#function-overrides)
   - [Inheritance and Overloading the operator =](#inheritance-and-overloading-the-operator)
   - [Overriding with Mbed](#overriding-with-mbed)
   - [Polymorphism and Virtual Functions](#polymorphism-and-virtual-functions)
- [Use-Cases for Inheritance](#use-cases-for-inheritance)
   - [Multiple Inheritance](#multiple-inheritance)
   - [Mocking Hardware with Pure Virtual Classes](#mocking-hardware-with-pure-virtual-classes)
   - [Porting to a specific platform](#porting-to-a-specific-platform)
   - [Arguments for loosely couple classes](#arguments-for-loosely-couple-classes)
- [Advanced Language Features](#advanced-language-features)
   - [Templates](#templates)
   - [Dynamic Memory Allocation](#dynamic-memory-allocation)
   - [The RAII Idiom](#the-raii-idiom)
   - [Smart Pointers](#smart-pointers)
   - [Reference Types](#reference-types)
   - [`const` and references](#const-and-references)
   - [Copy Constructors](#copy-constructors-and-operators)
   - [Move Constructors](#move-constructors-and-operators)
- [Standard Template Library](#the-standard-template-library)
   - [Standard Containers](#standard-containers)
- [References](#references)

---

# C and C++ Object Orientated Programming
C++ is a large language that takes a long time and practise to master. We will focus on core object orientated concepts. Even if you don't use all of these, you may encounter code that does.

The focus of all the sections below is on C++ classes. This is one of the major differences between the C language and C++. 

The examples are initially kept purposely simple to illustrate the key points. Then something closer to a real-world example is presented. These are arguably more interesting, but at the same time can quickly become complex. So my apologies in advance if some of the examples are somewhat contrived. Be reassured the concepts are the same and we will look at more real-world examples later.

## Related Lectures
For Plymouth students, the relevant lecture slides are here:

| Lecture | Title |
| - | - |
| 02-03 | [02-03- Object Orientated Programming in C++](https://dle.plymouth.ac.uk/mod/url/view.php?id=1162257) |
| 02-04 | [02-04- Function Templates and Operators](https://dle.plymouth.ac.uk/mod/url/view.php?id=1162259) |
| |

## Function overloading
The first feature we will look at is functional overloading. The idea is that you can create multiple functions with the same name, as long as the parameters differ.

Let's consider an example. Below is a simple class called `DoubleNumber`. It **encapsulates** a scalar value of type `double` and a number of member functions that operate on it.

```C++
#include "mbed.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>

using namespace std;

class DoubleNumber {
private:

protected:
    double _real;

public:
    //Designated constructor
    DoubleNumber(double r) {
        _real = r;
        cout << "This is the constructor of Base" << endl;
    }

    //Convenience constructor
    DoubleNumber() : DoubleNumber(0.0) { }

    //Magnitude
    double magnitude() {
        return fabs(_real);
    }

    //Three overloaded functions
    void setValue(double u) {
        _real = u;
    }
    void setValue(int u) {
        _real = (double)u;
    }
    void setValue(string strVal) {
        _real = stod(strVal);
    }

    double getValue() {
        return _real;
    }

    string asString() {
        return to_string(_real);
    }
};
```

| TASK 330A | Functional Overload |
| --- | --- |
| 1.  | Make Task-330A the active project |
| 2.  | Build and debug the code. Step through line by line |

### Overloaded Constructors
 
There are two constructors. They only differ by the parameter type. The first takes a single parameter:

```C++
    DoubleNumber(double r) {
        _real = r;
        cout << "This is the constructor of Base" << endl;
    }
```

The second constructor has no parameter, but invokes the first with a default value of 0.0.

```C++
    //Convenience constructor
    DoubleNumber() : DoubleNumber(0.0) { 

    }
```

| TASK 330A | Functional Overload |
| --- | --- |
| 3.  | Using the debugger, find out when these constructors are called |

Which is called depends on the parameters that are passed when creating the object.

### Overloaded Member Functions
The function `setValue` is overloaded three times:

```C++
    void setValue(double u) {
        _real = u;
    }
    void setValue(int u) {
        _real = (double)u;
    }
    void setValue(string strVal) {
        _real = stod(strVal);
    }
```

Note that the name is the same, but the parameters are mutually exclusive. Again, which gets called depends on the type of parameter passed.

| TASK 330A | Functional Overload |
| --- | --- |
| 4.  | Using the debugger, find out when these functions are called |
| 5. | What happens if you try to pass a different type, such as `n0.setValue(n1);` |
| 6. | Write an additional`setValue` function that takes a parameter of type `DoubleNumber` |

Note how the code to set a value becomes very consistent, but the underlying code can be quite different:

```C++
    n1.setValue(10);
    n2.setValue("-3.0");
```

In the second example, a string is passed. This has to be converted to a double value (a fairly non-trivial task).

> **Early Binding.**
>
> A key point to note is that the matching function is decided at build time. The compiler and linker resolve the function call.
>
> Function overloading can be an effective way to make APIs nice and simple. Often we see a trade between the complexity of a class, and it's ease of use.


### Example

| TASK 330B | Functional Overload in Mbed |
| --- | --- |
| 1.  | Make Task-330B the active project |
| 2.  | Read through `main.cpp` and study the class `Flashy` |
| 3. | Run the code and observe the light flashing sequence |
| 4. | Hold down the blue button and observe the change in the light flashing sequence |

In this example the member function `enable` and the constructors are **overloaded** 

| TASK 330B | Functional Overload in Mbed |
| --- | --- |
| 5.  | This class uses both **encapsulation** and **composition** (objects inside objects). There are members of type `DigitalOut` and `Ticker` |
| -   | _How_ and _when_ are these objects are constructed? |
| -   | Use the debugger to find out if you are not sure |

## Operator Overloading
One of the interesting language features of C++ is operator overloading.

> You have already encountered operator overloading with classes such as `DigitalIn`. You probably did not realise it!

We now extend our `Number` class to make it simpler to use.

| TASK 332A | Operator Overload in C++ |
| --- | --- |
| 1.  | Make Task-332A the active project |
| 2.  | Use the debugger to step through the code |

If we look in `main`, you can see how intuitive this class becomes to use:

```C++
    DoubleNumber n0(1.0);
    DoubleNumber n1;
    DoubleNumber n2;
    DoubleNumber n3;

    //setValue function overloading  
    n1 = 10.0;
    n1 += 1.0;
    n2 = "-3.0";
    n3 = n2;

    DoubleNumber sum = (n0 + n1 + n2 + n3);
    cout << sum << endl;
```

This is possible because of **operator overloading**. Operator overloading is quite an advanced topic, but some examples have been provided here to give you an idea of what can be done.

There are unary and binary operators.

### Unary Operators
The unary operators are the simplest. For example:

```C++
    void operator+=(double u) {
        double sum = this->getValue() + u;
        this->setValue(sum);
    }
```

This is invoked with the line `n1 += 1.0;` Another way to write it would be:

```C++
n1.operator+=(1.0);
```

where `operator+=` is the fully qualified function name (both do the exact same thing).

Looking at the function, and changing `operator+=` to `addTo` you could equally write:

```C++
    void addTo(double u) {
        double sum = this->getValue() + u;
        this->setValue(sum);
    }
```

Suddenly it does not seem to strange?

The `=` operator is slightly more complex. We could have written this:

```C++
    void operator=(DoubleNumber& u) {
        this->setValue(u.getValue());
    }
```

This is the exact same principle as above, and indeed would work for simple cases. 

> The line `n3 = n2;` would simply copy the value of `n2` into `n3`.

But what if you wrote the following?

```C++
n3 = n2 = n1;
```

From right to left, `n2` would be updated with the value of `n1`. But then, it returns `void`

`n3 = void` is not valid.

So instead, we return a reference to the result as follows:

```C++
    DoubleNumber& operator=(DoubleNumber& u) {
        this->setValue(u.getValue());
        return *this;
    }
```

Note how the pointer to converted to a reference using `*`

> **DON'T PANIC**
>
> This is a standard technique for chaining operators together. If you don't fully understand it, don't worry... I don't blame you and I won't ask you to do this! It still makes my head spin sometimes.

### Binary Operators (2 parameters)
More difficult to understand are binary operators, but the principle is much the same.

Consider the sum operator `+`. We might invoke with as

```C++
DoubleNumber y;
DoubleNumber p(10.0);
DoubleNumber q(20.0);

y = p + q
```

Looking into the class we see the `+` operator:

```C++
    DoubleNumber operator+(DoubleNumber& u) {
        DoubleNumber result;
        result = *this;
        result += u;
        return result;
    }
```

To reduce cognitive load, let's replace `operator+` with a function name:

```C++
    DoubleNumber add(DoubleNumber& u) {
        DoubleNumber result;
        result = *this;
        result += u;
        return result;
    }
```

Now we would write:

```C++
DoubleNumber y;
DoubleNumber p(10.0);
DoubleNumber q(20.0);

y = p.add(q)
```

So we don't actually modify `p`. The values of `p` and `q` are added, and a new `DoubleNumber` is returned.

Looking back at either the `add` or the `operator+` function (they are the same, just different names):

* We first create a new (local) variable of type `DoubleNumber` on the function stack.
    * Note that this only exists for the duration of the function
*  We copy `*this` (`p`) into this variable
*  We add `u` (`q`)
*  We return a COPY of this data
    * Note the return type is `DoubleNumber`
    * Like structures, objects are value types 

A lot to take in there. 

### Type Operators
If you write the following it would not normally compile, after-all, `DoubleNumber` is very different to `double`.

```C++
DoubleNumber n0(1.0);
double p = n0;
```

However, you can write a type operator to allow this to work.

In the example, the code is as follows:

```C++
    operator double() {
        return _real;
    }
```

This is partly why types such as `DigitalIn` result in such simple code:

```C++
DigitalIn pin(D7);
...
int x = pin;
...
```

### Challenge
The comparison operators `==` has been overloaded. The empty function has been included but the code is not written. Can you complete and test it?

### Reflection
It is a lot easier to consume classes with operator overloading that it is to write one! This is the trade between internal complexity and external simplicity. The Mbed os framework hides a lot of complexity so your code can be simple and expressive. 

> This is known as **abstraction**, or more specifically, **hardware abstraction**
>
> We say you are "abstracted away from the hardware". You rarely need to ever look at the MCU datasheet! 

Abstraction is important for a number of reasons:

* Code is faster to write (time to market and developer costs)
* Code is less error prone to write
* Code is much easier to follow and hence maintain / review
* Code is very portable. Simply change the target (and maybe a few pin assignments), and you can port your code to another Mbed compliant device

There are some downsides as well:

* Going through an abstraction layer is likely to incur some additional overhead
    * Function calls cost time
    * The class libraries may end up performing unnecessary operations
* The final binary size is likely to be greater than if you had written it at low-level (bare metal programming)
* Mbed does not cover all features of all devices. Two examples are DMA and the camera interface
* Bugs in any 3rd party framework (not just Mbed OS) might be present. 
* Regulatory bodies might not have approved your framework for all purposes (e.g. Medical)
* Operator overloading is considered controversial. It can be overused and result in ambiguous code.

You can mix Mbed code and bare-metal code, but you'd need to be very careful.

### Mbed Example
We now look at operator overloading for a simple (contrived) Mbed application:

| TASK 332B | Operator Overloading in Mbed |
| --- | --- |
| 1.  | Make Task-332B the active project |
| 2.  | Run this code to see what it does. It is similar to 330B only some operator overloads have been added |
| 3.  | Use the debugger to step through the code |

If we look at the code in `main`

```C++
    Flashy flashRed(TRAF_RED1_PIN, 125ms);
    Flashy flashYellow(TRAF_YEL1_PIN, 250ms);
    Flashy flashGreen(TRAF_GRN1_PIN);

    while (true) {
        flashRed    << true;
        flashYellow << true;
        flashGreen  << true;
        wait_us(5000000);              //5 seconds
        flashRed    << false;
        flashYellow << false;
        flashGreen  << false;
        wait_us(5000000);              //5 seconds

        if (blueButton == 1) {
            flashGreen = 50ms;
        } else {
            flashGreen = 500ms;
        }
    }
```

There is quite a lot of operator overloading happening here! For example:

```C++
flashRed    << true;
```
Enables the flashing

```C++
flashRed    << false;
```
Disables the flashing

```C++
flashGreen = 50ms;
```

Sets the flash rate to 50ms.

| TASK 332B | Operator Overloading in Mbed |
| --- | --- |
| 4.  | Right-click on `ms` in `50ms` and click "Go To Definition". What do you notice? |
| -   | Yes... another operator! This is how you can write 50ms or 50us and it will scale to the correct value (in uS) |

All clever stuff really, but hard to learn and write. 

> The main thing is you know it can be done, and to recognise it when you see it.

### Further Reading
You can see which operator can be overloaded in the following article:

https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B

## Class Inheritance
Now we move to an important topic in object orientated programming. 

Some of the key properties of inheritance include:

* A child-class can inherit (and hence reuse) many of the properties of a parent class
* A child-class can add additional functionality and state
* A child-class can override behaviours of the parent

We first look at a pure C++ example, whereby we extend our `DoubleNumber` to `ComplexNumber`, retaining all it's properties and augmenting it with new functions.

| TASK 334A | Inheritance |
| --- | --- |
| 1.  | Make Task334A the active program |
| 2.  | Using the debugger, step through the code and observe the output + read the comments. |
| - | Note how the classes have been moved out to separate files to keep main short. |
| 3.  | What has been added to `ComplexNumber` that was not in `DoubleNumber`? |

The code is below:

```C++
#include "DoubleNumber.hpp"

class ComplexNumber : public DoubleNumber {
private:

protected:
    double _imag;

public:
    ComplexNumber(double r, double i) : DoubleNumber(r) {
        _imag = i;
        cout << "This is the constructor of the sub-class" << endl;
    }
    
    ComplexNumber() : ComplexNumber(0.0, 0.0) { }
};
```

From the code, we can say the following about the `ComplexNumber` class:

* It has added a new property `_imag`
* It has a constructor that accepts two parameters
    * It passes the real-part to it's parent class
    * It initialised the imaginary part itself
* It will inherit all the functions from `DoubleNumber`

In main, we see how the constructor is used:

```C++
ComplexNumber c0(1.0, 2.0);
```

| TASK 334A | Inheritance |
| --- | --- |
| 4.  | Use the debugger to step into the constructor. Which constructor gets called first, `DoubleNumber` or `ComplexNumber`? |

Further down in main, we see `asString` being invoked

```C++
cout << c1.asString() << endl;
```

| TASK 334A | Inheritance |
| --- | --- |
| 5.  | Use the debugger to step into this function. Which class does it belong to? |

As you will hopefully see, `ComplexNumber` has all the attributes of `DoubleNumber` and more. However, it is far from complete and some of the behaviours are not suited to complex numbers (unless they are only real values of course).

For example, the public addition operator has been inherited:

```C++
 cout << (c0 + c1 + d0 + d1).asString();
 ```

| TASK 334A | Inheritance |
| --- | --- |
| 6.  | Use the debugger to step into this function. Why is the imaginary part not included? (sorry if this is obvious, but I'm trying to stress a point) |

> I am simply trying to stress _how_ inheritance works. Maybe this was not a great example as very little of the base class functions are useful in this case! In the next example we see how it is more useful.

### Inheritance with Mbed
For a more interesting example, now do the following:

| TASK 334B | Inheritance with Mbed |
| --- | --- |
| 1.  | Make Task334B the active program |
| 2.  | Look in main and find the class declaration for `Flashy`. What class does it **inherit**? |
| 3.  | Run the code to see what it does |
| 4.  | Does this class still use composition? If so, in what regard? |
| 5.  | Change the default flash rate to be 250ms by modifying the `Flashy` class (can you find where it is currently set?) |

Some key points to consider:

* `Flashy` is a new class, but still a `DigitalOut`.
    * Nowhere in the `Flashy` class do I have any code to set up or control the GPIO pins. That is all contained in `DigitalOut`
* `Flashy` adds new functionality to `DigitalOut`. This includes a `Ticker` and associated functions to toggle the output on and off.

### Reflection
This example is a much more meaningful example of inheritance, and hopefully you can see the benefits. 

We essentially take an existing class (and all the effort that went into writing it), inherit it's hard earned behaviours, and extend it for new purposes.

> The ability to inherit and reuse code in this way is one of the key arguments of class inheritance.

We also saw in a previous example that this was possible with **composition**. Both approaches can be made to work, but with composition, you would only have access to the public functions of `DigitalOut`.

> When we derive a class, we gain access to the `protected` members as well as the `public` 
>
> This is a key difference between inheritance and composition

The downside is that inheritance is more complex and arguably harder to write.

That's a lot, but yes, there is more! (yippee I hear you cry). 

_What if one of the parent class behaviours needs to be changed (or as we say, overridden)?_

This is the topic of the next section: function override.

### Function Overrides
As we saw in Task 334A, the `ComplexNumber` class inherits all the functionality of `DoubleNumber` and adds a new property, `_imag`. 

However, most of the functions written in `DoubleNumber`  perform operations on a single scalar value. `ComplexNumber` is 2-dimensional, and has two values (known as real and imaginary), so the same functions need to be adapted in many cases.

> Function override allows us to change the behaviour of an inherited function, will still maintain access to the version in the parent class
>
> If you are not an engineering student, think of complex numbers as coordinates on a graph with some quirky maths


| TASK 336A | Function Override |
| --- | --- |
| 1.  | Make Task336A the active program |
| 2.  | Using the debugger, step through the code and see which functions are in the parent class and which are in the child |
| 3.  | The overridden `operator+` is not finished. Complete this and test |

Note how the `toString` function uses the version that matches the type.

| TASK 336A | Function Override |
| --- | --- |
| 4.  | ADVANCED: Consider the following line: |
| -   | `cout << c1.asDoubleNumber().asString() << endl;` |
| -   | Can you explain how this works? Good luck :) |

As you might have picked up, this can get really complicated. In fact, to write a good complex number class probably means throwing this all away and taking a more sophisticated approach.

### Inheritance and Overloading the operator =
Just as you thought, hmm, this is clever...a word of caution here. Remember before we even looked at operator overloading, you could use `=` to copy one class to the other? **This behaviour is the default and has not gone away**.

Consider the code below:

```C++
class A {
    double p;
    public:
    A(double u) { p = u;}
}
...
A u1(2.0);
A u2(0.0);
u2 = u1;
```

Note the default `=` operator does a member-by-member copy (just like structures)?

_By default, unless you write your own, the compiler creates an `operator=` for you. The `ComplexNumber` class therefore has it's own overridden `+`.

### Overriding with Mbed
Again, a less contrived example is provided in Task 336B. Again, we continue with overriding `DigitalOut`, but now we are making it look and feel more like the original `DigitalOut`

| Operation | DigitalOut | Flashy |
| --- | --- | --- |
| Equate to 1 or 0 | Static ON or OFF | Flashing ON/OFF or OFF |
| Set duration | Not implemented | Define flash rate |


| TASK 336B | Function Override with Mbed |
| --- | --- |
| 1.  | Make Task336B the active program. Build and run. |

Let's look at the main code:

```C++
    Flashy flashRed(TRAF_RED1_PIN, 125ms);
    Flashy flashYellow(TRAF_YEL1_PIN, 250ms);
    Flashy flashGreen(TRAF_GRN1_PIN);

    while (true) {
        flashRed    = 1;
        flashYellow = 1;
        flashGreen  = 1;
        wait_us(5000000);              //5 seconds
        flashRed    = 0;
        flashYellow = 0;
        flashGreen  = 0;
        wait_us(5000000);              //5 seconds

        if (blueButton == 1) {
            flashGreen << 50ms;
        } else {
            flashGreen << 500ms;
        }
    }
```

In many ways, it now looks like `DigitalOut`. 

* Equate to a `1` and it flashes; 
* Equate to a `0` and the light is out.

We can also set a time with the operator `<<` to set the duration.

So to **use** this new class is just as simple as `DigitalOut`.

Looking into the `Flashy` class we note the following two functions:

```C++
    Flashy& operator=(int u) {
        this->write(u);
        return *this;
    }

    //Override write
    void write(int value)
    {
        if (value == 0) {
            this->enable(false);
        } else {
            this->enable(true);
        }
        //Don't call the baseclass version!
    }
```

Both the `=` operator and the `write` functions exist in the `DigitalOut` class. They have been overridden to change the behaviour.

> Setting to a `1` with `=` only turns on the `Ticker`. It does not set the Pin state at all!

So how does the pin state ever change? That is found in the Ticker interrupt service routine

```C++
    void timerISR()  {
        //Call the baseclass version to toggle the GPIO
        DigitalOut::write(1-this->read());
    }
```

Note how we use the scope operator `::` to explicitly call the version of `write` from the **parent class** (`DigitalOut`).

In other words, we can choose which version to use.

> You always have access to the parent class functions even if you override it.

### Polymorphism and Virtual Functions

| TASK 338B | Virtual Functions |
| --- | --- |
| 1.  | Make Task338B the active program. Build and run. |
| 2.  | Pay particular attention to the timing of the red LED | 
| 3.  | Now step through the code with the debugger to ensure you follow it |
| 4. | Now uncomment the line that reads `//#define EXP1` |
| 5. | Rebuild the code and run. Again, observe the behaviour of the red LED. Now press the black reset button WHILE holding down the blue button. Note the behaviour. 
 |
 | - | Use the debugger to help you follow what has happened here |
 
In the last example, we used **dynamic memory allocation** to create an object:

```C++
    Flashy* pFlashRed;
    if (blueButton == 1) {
        pFlashRed = new Flickery(TRAF_RED1_PIN, 125ms);
    } else {
        pFlashRed = new Flashy(TRAF_RED1_PIN, 125ms);
    }
```

When the button is pressed, you will see an instance of the child-class `Flickery` has been created instead of `Flashy`. 

> This uses the C++ operator `new`, which does the following:
>
> * it allocates memory for a new object
> * It creates the object, which in turn calls its constructor
> * It returns an address of that object so it can be saved in a pointer.
>
> If we wish to deallocate and destroy this object, we would use `delete`

A key point to note is this:

* The pointer `pFlashRed` is of type `Flashy*` and NOT `Flickery*`
* Flickery subclasses `Flashy`, and **overrides the ticker interrupt service routine (ISR)** in order to change its behaviour.

When the code **runs**, we observe the following:

* If button is now pressed, it is a new `Flashy` that is created. 
* If button is pressed, it is a new `Flickery` that is created. 

Clearly the compiler has no idea which one will be created, so how does it know which ISR to use?

Let's look at `Flashy` and we see the ISR has been slightly modified. The `Ticker` ISR now reads as follows:

```C++
    virtual void timerISR()  {
        //Call the baseclass version to toggle the GPIO
        DigitalOut::write(1-this->read());
    }
```

**The keyword `virtual` has been added.** 

> This tells the compiler to add code to "look up" what **type** is really being used, and find the appropriate function, starting at the bottom and working up.
>
> Under the hood, it uses something known as a v-table to do this.

| TASK 338B | Virtual Functions |
| --- | --- |
| 6. | Set a break point inside BOTH ISRs (in the parent and child class) |
| 7. | Use the debugger to discover which one is when the blue button is held down |
| 8. | Remove the `virtual` keyword and rebuild the code. Repeat the above experiment |


## Use-Cases for Inheritance

### Multiple Inheritance
C++ allows us to  inherit code from more than one class. You can see an example of this in Task-340B. We will not look at this any further at this stage, but it is well documented elsewhere.

### Mocking Hardware with Pure Virtual Classes
Some other languages have "interfaces", which are similar to classes, but contain no code. The nearest equivalent in C++ is "pure virtual classes" (or abstract classes). This is a somewhat advanced topic, but an example has been provided in Task-344.

This task also introduces the idea of mocking hardware. Mocking hardware is when you write abstractions to mimic real hardware. This is useful for a number of reasons, including:

* Cross platform porting
* Testing without access to physical hardware
* Unit Testing code logic (abstracting out the hardware specifics)

We also want to make it easy to switch between real hardware and mocked. A key concept is this: *any object that has at least one parent class, in effect, has more than one type. Therefore, objects that share the same parent can be considered to be of the same type*.

Let's look at a real example:

| TASK 344 | Mocking Hardware with Pure Virtual Classes |
| --- | --- |
| 1 | Make Task 344 your active program |
| 2 | Build and run. You should see an LED pulse on and off every second |
| 3 | Inspect the `main` function |

We see the following code:

```C++
int main()
{
    Flashy f(tmrObj, lightObj, 250ms);
    
    while (true) {
        f.flashOnce();
        tmrObj.wait_for(1000ms);
    }
}
```

You need to initially focus on the `Flashy` class, as this has been written with a specific criteria - **to be platform independent**. However, it is clearly running on Mbed. 

| TASK 344 | continued |
| --- | --- |
| 4 | Comment out the line in `main.cpp` that reads `#define USE_REAL_HW` |
| 5 | Rebuild and observe the terminal output. You should also notice that your board LED stops flashing |

With this one simple change, we have switched from real platform-specific hardware to pure C++ (and C++ standard library) text output.

Let's now look at one of the more surprising claims: 

> The class `Flashy` is platform independent.

There are two folders in this project: `Concrete Objects` and `Flashy` (the folders are purely a means of grouping related files). In `Flashy`, we see three classes:

* `Flashy` - pure C++
* `ITimer` - pure virtual class that contains only function prototypes  relating to starting and stopping a timer. There is no concrete code in this class. In other languages, this would be called an *Interface*
* `ILightNotify` - another pure virtual class, only with function prototypes relating to switching a light on and off

All the above are pure C++ (and the standard library). In theory, these should compile on any platform. However, we need to do more work for them to actually compile.

Let's look at `Flashy` (code is shown below). Note the protected properties `_tmr` and `_light`. These are of type `ITimer&` and `ILightNotify&`. They are also **references** (to existing objects), and provided (a.k.a.injected) via constructor parameters.

> The actual concrete objects for `_light` and `_tmr` are not instantiated inside this class, but are instead created elsewhere (platform specific code), and passed by reference from outside.
>
> The actual objects can be **any** subclass of `ITimer` and `ILightNotify`. The `Flashy` class does **not** need to know the concrete class type. 
>
> This is sometimes known as *Dependency Injection* (DI)

```C++
class Flashy {
    protected:
    ITimer& _tmr;           //Reference to an object type ITimer
    ILightNotify& _light;   //Reference to an object type ILightNotify
    milliseconds _rate;
    public:
    Flashy(ITimer& tmr, ILightNotify& light, milliseconds rate) : _tmr(tmr), _light(light), _rate(rate) {
        _light.lightOff();
        _tmr.stop();
    }
    void flashOnce() {
        _light.lightOn();
        _tmr.start();
        _tmr.wait_for(_rate);
         _light.lightOff();
        _tmr.wait_for(_rate);       
        _tmr.stop();
    }
};
```

So what are `ITimer` and `ILightNotify`? Taking a look at the sources, we see they are *pure virtual classes* (known as Interfaces in other languages).

**`ITimer`** lists some APIs for generic timer behaviour. Note these are *pure virtual functions*, so **must** be overridden in any subclass (or the compiler will generate an error). Therefore, we can safely assume these functions will always be implemented at run-time by any subclass of `ITimer`.

```C++
class ITimer {

    public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual milliseconds getTime_ms() = 0;
    virtual void wait_for(milliseconds t) = 0;
    protected:
    virtual void initialise() = 0;
};
```

**`ILightNotify`** similarly lists some APIs for generic "Light" behaviour. Again, these are all *pure virtual functions*, so **must** be overridden in any subclass.

```C++
class ILightNotify {
    public:
    virtual void lightOn() = 0;
    virtual void lightOff() = 0;
    virtual bool lightStatus() = 0;
};
```

**KEY POINT** - all of the three classes discussed so far are pure C++ and C++ standard library. There is nothing in this code that is platform dependent. These three files would be packaged together.

### Porting to a specific platform
Now we have the three virtual classes, but none of them can be instantiated. The developer reusing these classes must now implement the platform specific code. This is achieved through subclassing and injecting (via parameters).

| TASK 344 | continued |
| --- | --- |
| 6 | Examine the code in the `ConcreteObjects` folder. |
| - | Contrast the `MbedLight` and `MockedLight` classes |
| - | What do they have in common? |
| - | What is different? |
| 7 | In `MbedLight`, comment out one of the functions and try to re-compile |
| - | What error do you get and why? |

Let's now look at the sources (see below). `MbedLight` is a concrete class that compiles. It is designed to work with Mbed, making use of `DigitalOut` and related classes. The key point is that **it is a subclass of ILightNotify**, so **must** override all the APIs in the parent class in order to compile.

* We can say that an instance of `MbedLight` is also of type `ILightNotify`
* All the base class functions are overridden with concrete (platform dependent) implementations.
* All the inherited APIs are virtual, so will be resolved correctly at run-time (polymorphism - using late binding)

```C++
class MbedLight : public ILightNotify {
    private:
    DigitalInOut _gpio;

    public:
    MbedLight(PinName pin, PinDirection direction=PinDirection::PIN_OUTPUT, PinMode mode=PushPullNoPull, int value=0) : _gpio(pin, direction, mode, value) {
        _gpio.output();
        _gpio.mode(mode);
        _gpio.write(value);
    }

    virtual void lightOn() { 
        _gpio.write(1); 
    };
    virtual void lightOff() { 
        _gpio.write(0); 
    };
    virtual bool lightStatus() { 
        return (_gpio.read() == 1) ? true : false; 
    };
};
```

Now we can contrast this with `MockedLight`. This has has no dependency on Mbed at all. In fact, it only uses standard C++ and the standard C++ library. All output is written to the the `stdout` stream (terminal output). However, it also is a subclass of `ILightNotify` so again, **must** override all the virtual functions in order to be compiled. 

* Like it's sibling `MbedLight`, we can say it is also of type `ILightNotify`.

```C++
class MockedLight : public ILightNotify {
    private:
    bool state = false;
    string ID;

    public:
    MockedLight(string ID, bool initialState = false) : ID(ID) {
        cout << "Mocked Light initialised" << endl;
        state = initialState;
    }

    virtual void lightOn() { 
        cout << "LIGHT " << ID << "ON" << endl; 
        state = true; 
    };
    virtual void lightOff() { 
        cout << "LIGHT " << ID << "OFF" << endl; 
        state = false; 
    };
    virtual bool lightStatus() { 
        return state; 
    };
};
```

So we have a pure virtual base class type (`ILightNotify`), and a choice of two concrete subclasses. All that remains is for another actor to inject one of these concrete objects into the `Flash` class. We see this code in `main.cpp`.

If we are building for Mbed, we would use the following:

```C++
MbedLight redLed(LED1);                 //Concrete class
ILightNotify& lightObj = redLed;        //Alias - to look tidy
Flashy f(tmrObj, lightObj, 250ms);
```

If we are testing on another platform (e.g. Windows console app), we could use the following:

```C++
MockedLight redLedMocked("RED LED");
ILightNotify& lightObj = redLedMocked;
Flashy f(tmrObj, lightObj, 250ms);
```

**Note** how the last line of each version is identical. `Flashy` does not need to know what concrete type is being used as the parameter type is `ILightNotify`. All it cares about is that it can safely invoke a set of member functions at run-time, as declared in `ILightNotify`. The addresses will be resolved at run-time (see virtual functions).

Note how the concrete object is passed by parameter. This is the Dependency Injection (DI) part. We've chosen to use parameters in the constructor, but you could equally use setters for the properties.

We can also make another claim - `Flashy` is not strongly coupled to any particular concrete class type. We say it is *loosely coupled*.

| TASK 344 | continued |
| --- | --- |
| 8 | Examine the code in `ITimer` and the concrete subclasses in the `ConcreteObjects` folder. |
| - | Confirm that the exact same principle is applied |
| 9 | Can you build a Windows console application (in C++) to test `Flashy` using the Mocked version of the class? |

### Arguments for loosely couple classes
There are many arguments for loose coupling, some of which we have witnessed here. 

One of the downsides of *composition* is the tight coupling it creates. By making our properties pure virtual class types (Interfaces), we break such dependencies.

One of the major benefits of this approach is mocking. Writing classes to mimic real hardware can help make testing more rigorous. Mocked classes can include additional tests and data logging. It should be made easy to switch back to platform code. This also supports methodologies such as Test Driven Development (TDD).

Another benefit is portability. We could equally have written concrete subclasses for another platform, such as Arduino.

The cost for this is greater complexity in the application. The *plumbing and wiring* of objects can be confusing, especially if it is not your own code.

## Advanced Language Features
You may have noticed some key differences between C and C++

* Easier to reuse
   * Inheritance
   * Polymorphism
* Code can be more expressive
   * Function and operator overloading can make our code look clean and simpler to understand
* Safer
   * Constructors and destructors automatically allocate, initialise and free resources

In this section, we will look at some language features that take this further, and help us write compact, robust and reusable code.

### Templates

Function and Class templates are widely used C++ language features that can significantly reduce repeated code as well as make code more reusable. In this section we will take a short look at some key concepts (there are many good books and websites describing C++ templates in greater detail). 

#### Function Templates

In C and C++, we are familiar with functions:

`<return type> function_name(<type> parameter, <type> parameter ...)`

Note that the function parameters and returned data **must** all have an explicit data type. **This is done for safety**. For example, if we tried to build and run the following code:

```C++
#include <iostream>

bool isGreater_int(int a, int b) {
    if (a > b) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    bool y = isGreater_int(3,2);
    if (y == true) {
        std::cout << "3>2\n\r";
    }
    bool t = isGreater_int(0.3, 0.2);
    if (t == true) {
        std::cout << "0.3 > 0.2\n\r";
    }
}
```

The simple function `isGreater` performs a greater-than operation `>` on two integers. This always works until we pass arguments with the wrong type, such as:

```C++ 
bool t = isGreater_int(0.3, 0.2);
```

where the output is the opposite to what we intended. The arguments `0.3` and `0.2` are both literal constants, of type `double`. However, `isGreater` has integer parameter types. Therefore, `0.3` and `0.2` are `implicitly` converted to `int` and are both rounded down to `0`, making them equal.

> If you try and build this code, there is very likely to be a compiler warning. On the system the author used, the warnings read: `warning: implicit conversion from 'double' to 'int' changes value from 0.2 to 0` and `warning: implicit conversion from 'double' to 'int' changes value from 0.3 to 0`
>
> Do not ignore warnings!

So, we might write another function to compare two variables of type `double`:

```C++
bool isGreater_double(double a, double b) {
    if (a > b) {
        return true;
    } else {
        return false;
    }
}
```

However, look at the function bodies of both versions. **The code is identical. They only differ in data-type**. As you may know, replicating code is not encouraged. It makes the code longer, and if you need to change one, you have to remember to change the other.

This is where function templates come it. Where two functions only differ in data type, you can write a *function template* and let the compiler write the functions for you. The code for the function template is as follows:

```C++
template<class T>
bool isGreater(T a, T b) {
    if (a > b) {
        return true;
    } else {
        return false;
    }
}
```

The type-parameter `T` is not specified at this stage. It is when the compiler encounters invokation of the function, that it creates functions for you with the appropriate types:

```C++
int main()
{
    bool y = isGreater(3,2);
    if (y == true) {
        std::cout << "3>2\n\r";
    }
    bool t = isGreater(0.3, 0.2);
    if (t == true) {
        std::cout << "0.3 > 0.2\n\r";
    }
}
```

Behind the scenes, two versions of `isGreater` will be created. One will use type `int` and the other will use type `double`. Let's now look at an example in Mbed.

| TASK 350 | Function Template |
| --- | --- |
| 1. | Make Task 350 your active program. Build and run |
| 2. | Turn the potentiometer quickly in the clock wise direction, and observe the LEDs |
| - |  Repeat, but anti clockwise |
| 3. | Now experiment with turning the dials slowly so that the lights do not change |

In this code, we read the ADC and represent it using two data formats (for comparison):

```C++
uint16_t uPot = pot.read_u16() >> 4;    //12-bit Integer 0..4095
float    fPot = (float)uPot / 4095.0f;  //Scaled 0.0-1.0  
```

| TASK 350 | Continued ... |
| --- | --- |
| 4. | Try editing the line that reads `hasIncreasedBy<float>` to `hasIncreasedBy<int>`. Intellisense may detect this immediately and underline some code! Try building the code. <a title="Type conversion error as before">What warning do you get?</a> |
| 5. | In this code, we've used explicit types `<float>` and `<uint16_t>` to direct the compiler. Remove these and rebuild. <a title="No. The compiler uses type-inference to work out the type"> Does this have any impact?</a> |
| 6. | Now remove the `f` from `0.1f`. <a title="The literal 0.1 is of type double, but the first parameter is type float. The template expects the two arguments to be the same type `T`"> What happens and why?</a>> |
| - | Hover your mouse to see the answers |

Now consider the following line:

```C++
cout << "Mean: " << addToBuffer<uint16_t, double, 4>(uPot) << endl;
```

This invokes the function `addToBuffer<uint16_t, double, 4>` and outputs a running arithmetic mean. Let's look at this function in more detail:

```C++
//Function to add a sample to the a circular buffer and return the sum
template<class T, class R, int N>
R addToBuffer(T nextSample)
{
    //Again that static local trick 
    static T buffer[N];
    static T sum = (T)0;
    static int index = 0;

    // Sum is updated - add new sample, subtract oldest
    sum = sum + nextSample - buffer[index];
    buffer[index] = nextSample;     //Overwrite oldest sample
    index = (index + 1) % N;        //Update position of oldest sample
    return (R)sum/(R)N;             //Return the mean, using the precision of type R
}
```

This time there are three template parameters.

* `T` is a type-parameter, and specifies the type of data in the internal buffer
* `R` is a type-parameter, and specifies the return type (different to the type of the data)
* `N` is a non-type parameter, which in this case is an integer constant that sets the size of the internal array **at compile time**

> Observe the following:
>
> * Function parameters are determined at run-time
> * Template parameters are determined at compile-time


The non-type parameter is particularly useful in embedded-systems as it allows us to create different size arrays that a defined at compile time, and avoids dynamic memory allocation (slower and comes with risks).

| TASK 350 | Continued ... |
| --- | --- |
| 7. | Modify the code to calculate an average over 20 samples  |
| 8. | In the line that reads `return (R)sum/(R)N;` <a title="This is a type-cast. It converts the data (integer) to type R (double) to maintain precision when performing the division"> what is the purpose of `(R)`?</a>

So far, we have considered the case where template functions always contain the exact same code, but use different types. You might wonder what happens if for some types, code cannot be equal? In that case, you can use template specialization. See [1] for more details.

#### Class Templates

Everything we've seen in function templates can also be applied to a class. In fact, the example above is a good candidate for a class as we can make our code even more readable.

| TASK 351 | Class Templates |
| --- | --- |
| 1. | Make Task 351 your active program. Build and run |
| 2. | Adjust the potentiometer. Note how the output changes. There may be some perceivable lag |

If we look at the main code, we see the following:

```C++
#include "uop_msb.h"
#include "RunningMean.hpp"

#include <iostream>
using namespace std;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
AnalogIn pot(AN_POT_PIN);

//Defines an object with a fixed-size internal buffer
RunningMean<uint16_t, double, 4> buf4;

int main()
{
    printf("\n\rStart\n\r");

    while (true) {
        //Read the ADC     
        uint16_t uPot = pot.read_u16() >> 4;    //12-bit Integer 0..4095
        float    fPot = (float)uPot / 4095.0f;  //Scaled 0.0-1.0      
 
        //Add sample to buffer.
        buf4 << (uint16_t)uPot;

        //Output running mean
        cout << "Mean: " << buf4 << endl;
        wait_us(500000);
    }
}
```
The object that buffers data and calculates the mean is defined as follows:

```C++
RunningMean<uint16_t, double, 4> buf4;
```

The data input type is a 16-bit unsigned, the output (mean) is type `double`, and the internal buffer holds 4 samples. We add data using the `<<` operator as follows:

```C++
buf += uPot;
```

And finally, we obtain the mean result by simply referring to the object `buf` as if it was a variable of type `double`:

```C++
cout << "Mean: " << buf << endl;
```

Note how operator overloading is used to try and make the code more easy to read. At least, that was the intention!

> There is a view that operator overloading makes code ambiguous. For example, why did I use `+=`, why not `<<`, and would the casual observer know what these do?

Now let's examine the class. Again, we see the type parameters `template<class T, class R, int N>` as before.

```C++
#pragma once
#include <iostream>

/*
T is the data type of the data
R is the data type of the mean (and sum)
N is the buffer size
*/
template<class T, class R, int N>
class RunningMean {
private:
    T buffer[N];
    R sum;
    int index;

    // Computing a running sum (Optimised for speed - no checks for overflows!!!)
    void addAndUpdate(T nextSample) {
        // Sum is updated - add new sample, subtract oldest
        sum = sum + nextSample - buffer[index];
        buffer[index] = nextSample;     //Overwrite oldest sample
        index = (index + 1) % N;        //Update position of oldest sample
    }

public:
    //Constructor
    RunningMean(T initValue = (T)0) {
        //Initialise data to known state
        sum = (T)0;
        index = 0;
        for (unsigned int n=0; n<N; n++) buffer[n] = (T)0;
    }   

    //Used to add a sample to the buffer
    void operator += (T sample) {
        this->addAndUpdate(sample);
    }

    //Used to read the mean
    operator R() {
        return sum/(R)N;             //Return the mean, using the precision of type R
    }
};
```

| TASK 351 | Continued... |
| --- | --- |
| 3. | This class has a constructor. <a title="All internal data is always initialised to a known state. In the function template example, it was assumed the buffer would initially contain zeros.">What is the advantage this brings over the simple function template version?</a> |
| 4. | Now **add** a second instance of this class, but this time make the buffer 64 samples deep. You code your add data to both buffers and output the mean from each.  <a title="The 64 sample version will lag much more, but the mean will have less variance">How do they compare?</a> |

**Key Points**

Consider the following two lines:

```C++
RunningMean<uint16_t, double, 4> buf4;
RunningMean<uint16_t, double, 64> buf64;
```

It should be stressed that the compiler generates **two versions** of the class `RunningMean`. Both have internal **fixed** size arrays. The only difference between the two classes is that these arrays are of different sizes.

**Because the array sizes are defined at build time, this allows the linker to ensure there is enough memory to run the code**

It would be tedious (and error prone) to duplicate the class twice, just to modify the array sizes. C++ templates gets the compiler to create them for you!

### Dynamic Memory Allocation


| TASK 352 | Dynamic Memory Allocation |
| --- | --- |
| 1. | Make Task 352 your active program. Build and run |
| 2. | Look at the constructor for the `RunningMean` class. |
| - | <a title="Using the `new` command">From reading the code, how is the array `buffer` created?</a> |
| 3. | Look inside the class destructor |
| -  | <a title="Using the `delete []` command">How is the memory freed (so it can be reused)?</a> |

Let's look at this class more closely:

In internally, there is a **pointer** (32-bit integer variable that stores an address) `buffer`. The data it points to is expected to be type `T` (template argument).

```C++
template<class T, class R>
class RunningMean {
private:
    uint32_t N;
    T *buffer;
    ...
```

This pointer is initialised in the class constructor as follows:

```C++
RunningMean(uint32_t N_, T initValue = (T)0) : N(N_) {
    //Initialise data to known state
    sum = (T)0;
    index = 0;
    buffer = new T[N];  //Allocate memory on the heap
    for (unsigned int n=0; n<N; n++) buffer[n] = (T)0;
} 
```

The C++ `new` keyword is used to request a block of memory (via some low-level library functions in the standard C++ library). The following line requests a block of memory to store `N` variables of type `T`. 

```C++
buffer = new T[N];
```

*If successful*, `new` will return the start address of this memory, and this is saved in `buffer`. The variable `buffer` is known as a raw pointer [3]. The actual reserved memory will be in the **heap** memory area. You can now use `buffer` as an array.

> `N` was passed as a constructor parameter, but could equally have been obtained from a network, or via user input. As the size of the array (`N` copies of type `T`) is decided at *run time*, we call this **dynamic memory allocation**.

When the data is no longer needed, the memory should be *deallocated*. This is found in the destructor (which is called then the object is destroyed):

```C++
~RunningMean() {
    //Give back the memory
    //This is critical unless you want a memory leak!
    delete [] buffer;
}
```

The keyword `delete []` is used to free the memory so it can be allocated for other uses.

#### New and Delete

In this example, we look at two ways to use `new` and `delete`.

| TASK 353 | New and Delete |
| --- | --- |
| 1. | Make Task 353 your active program. Build and run |
| - | Study the code and note the console output |
| 2. | Look at the output for Task 1. <a title="When an object is allocated with `new`, the constructor runs. When destroyed with `delete`, the destructor runs">At what point does the constructor and destructor run for class `DataObject`?</a> |
| 3. | Look at the output for Task 2. <a title="When the array `buffer` is instantiated with `new`, all the contained object constructors are called (in turn). When the array `buffer` is deleted with `delete []`, all the destructors are called">What causes the constructor and destructor run for class `DataObject`?</a> | 
| 4. | Change the line that reads `delete [] buffer;` to `delete buffer;`. Ignoring the warnings, build and run again. |
| 5. | <a title="The objects in the array are not being deleted">Why are the destructors not being called?</a> |
| - | <a title="152-64=88 bytes">How much memory is being leaked?</a> |

In Test 1, we saw a single object allocated and deleted:

```C++
DataObject *pObj = new DataObject(1.0f, 2.0f);
pObj->display();
delete pObj;
```

Note how the array operators `[]` are not used for `new` or `delete` in this case as we are not creating an array.

In Test 2, we created an array of objects:

```C++
DataObject *buffer = new DataObject[N];
```

When this occurs, you see the constructor for each instance of `DataObject` being run.

> Note that there is no way to pass values into the constructor here.

We see all the destructors when when the array is destroyed:

```C++
delete [] buffer;
```

Things can get more complicated than this, and memory leaks can be hard to spot.

> A common cause of a memory leak is an early return from a function, before the `delete` statement
>
> ```C++
> void myFunction()
> {
>   MyClass obj = new MyClass();
>   ...
>   if (condition_to_exit == true) return; //Early return
>   ...
>   delete obj;
> }
> ```

**TASK** - Watch the following two videos to summarise this section

[VIDEO - New and Delete for a single object](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=5c254629-f767-4b4c-bf20-af1700d51bb0)

[VIDEO - New and Delete for an array of objects](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=61578609-b38e-4d11-ad89-af1700d69636)

For more information on `delete`, see [2].

### The RAII Idiom

You sometimes hear the statement that *you should not use dynamic memory allocation in an embedded system*. There are a number of reasons why this might be:

1. It is hard to know in advance if you have *enough* memory
2. Over time, memory can be fragmented and allocation can fail
3. Accessing dangling pointers (a pointer that holds the address of some prebviously allocated memory, but where that memory has been released with `delete` or `free`) can cause unpredicatable results.
4. It is expensive in CPU time to allocate and deallocate memory
5. Memory leaks can occur, and can be hard to both detect and spot (when reading source code).

   
For point 1, the developer is responsible to ensure there is always enough memory. It is considered good practise to add run-time checks (as was shown in the previous task), such as checking an allocation succeeded and handling the error condition appropriately.

For point 2, memory fragmentation occurs if memory is allocated and deallocated in a random order. If you de-allocate in the exact reverse order that you allocate, then it is possible to avoid fragmentation. If you have code that runs out-of-sequence (e.g. multi-threaded code), then you need to be extra careful.

For point 3, accessing *dangling pointer* can be avoided if you remember to set all unused pointers to `nullptr`. 

The last two points are more challenging to address. Memory leaks even apply to devices with less memory pressure, such as the application processor used on the Raspberry Pi. A small memory leak over time will ultimately result in all the memory being used up. Memory leaks are such a problem, that there have been language changes to help address them. We will discuss two strategies now.

The **Resource Acquisition Is Initialization** (RAII) idiom ensures that 

> "resource acquisition occurs at the same time that the object is initialized, so that all resources for the object are created and made ready in one line of code. In practical terms, the main principle of RAII is to give ownership of any heap-allocated resource—for example, dynamically-allocated memory or system object handles—to a stack-allocated object whose destructor contains the code to delete or free the resource and also any associated cleanup code" [5].

Consider the following function:

```C++
void someFunction() {
    //Allocate
    uint16_t* pData = new uint16_t[64];

    ...
    
    if (someCondition) {
        //Early return
        return;
    }

    ...

    //Free up the memory
    delete [] pData;
}
```

This code has the potential to leak memory. If `someCondition` is `true`, it will exit *before* the memory pointed to by `pdata` is released. As `pData` goes out of scope, we have no way to recover from this.

One way to address this is to add an additional `delete []`

```C++
void someFunction() {
    //Allocate
    uint16_t* pData = new uint16_t[64];

    ...
    
    if (someCondition) {
        //Early return
        delete [] pData;
        return;
    }

    ...

    //Free up the memory
    delete [] pData;
}
```

However, it is all too easy to forget to do this! From task 352, we saw a class where an array is allocated in a constructor, and deallocated in the destructor. An extract is shown below:

```C++
template<class T, class R>
class RunningMean {
private:
    uint32_t N;
    T *buffer;
    R sum;
    int index;

public:
    //Constructor
    RunningMean(uint32_t N_, T initValue = (T)0) : N(N_) {
        sum = (T)0;
        index = 0;
        buffer = new T[N];  //Allocate memory on the heap
        for (unsigned int n=0; n<N; n++) buffer[n] = (T)0;
    }   
    //Destructor
    ~RunningMean() {
        //Free the memory
        delete [] buffer;
    }

    ...

};
```

If we create object of type `RunningMean` on the local stack, then heap allocation and deallocation is automatic:

```C++
void someFunction() {
    //Pointer obj is locally declared and defined on the function stack
    RunningMean<uint16_t, double> obj(64);

    ...
    
    if (someCondition) {
        //Early return - obj will go out of scope
        return;
    }

    ...

    //obj will now go out of scope
}
```

Note this function still has an *early return*, but there is no memory leak. This works because of the the following:

* The pointer variable `obj` is a local variable (therefore stack based)
   * it automatically goes out of scope as soon as the function `someFunction` exits.
* When `obj` goes out of scope, the destructor for `RunningMean` is called automatically and releases the memory.

Another example of this is found in the [`CriticalSectionLock` class](https://os.mbed.com/docs/mbed-os/v6.15/apis/criticalsectionlock.html)

### Smart Pointers

While embracing the idea of RAII, and with the help of C++ templates, we can make our code even safer with the use of C++ smart pointers, which are now part of the C++ standard library. 

There are three types of smart pointer:

* **Unique** - where **only one** pointer can reference a specific resource on the heap. When that pointer goes out of scope or gives up ownership, the resource is automatically deallocated. 
* **Shared** - where multiple pointers can reference a specific resource on the heap. The resource will remain on the heap while there is **at least one** shared pointer in scope. Once all shared pointers go out of scope or give up ownership, the resource is automatically deallocated.
* **Weak** - A special type that is used in combination with a unique or shared smart pointer to avoid a specific condition known as a `retain cycle` (special case).

For this discussion, we will only focus on the Unique pointer (`unique_ptr`) as the use-cases for the others is somewhat more complex. There can also be issues with C++ language confirmity.

| TASK 354 | Smart Pointers |
| - | - | 
| 1. | Read the code in Task 354, then then Build and run.  |
|    | Enter 1000 for the sampling rate |
|    | Enter 1000 for the number of samples |
|    | Enter 200 for the frequence |
| 2. | If you have a phone app that can play a tone, set the frequency to 200Hz and hold it over the microphone |
|    | Compare the magnitude with and without the tone playing. Compare with different frequencies |
| 3. | <a title="No. The heap memory is all resored">Reading the output in the terminal, is there a memory leak?</a> |
| 4. | <a title="In dft.hpp, line 18 - timeSeries = std::unique_ptr<T[]>(new T[Nsamp]);"> The object type `DFT<T>` stores `N` samples in it's internal buffer. Where is the memory for this buffer allocated? |
| 5.  | <a title="The the function magnitudeAtFrequency() exits, the object dft goes out of scope. This causes the the smart pointer timeseries to go out of scope, which free the memory automatically">How and when is the memory deallocated?</a>
| 6. | Re run the code, but specify the number of samples as 1000000 |
| -  | <a title="Insufficient memory on the heap">Why is there an error?</a>

There is a lot more that could be said about smart pointers. The adoption of them seems to be somewhat specific to the compiler. It is probably more important at this stage that you know they exist, and how to recognise one when you see it. For your own code, it is often advised that you use the standard template library objects `vector` and `array`. These will be discussed later in the [standard template library](#the-standard-template-library) 

See [this page](https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170#kinds-of-smart-pointers) for more details on smart pointers.

### Reference Types

The C and C++ languages claim to be fast and efficient. This can be at the expense of readability. C code can become quite hard to read.

C++ has features that try to make code clearer, easier to read and  maintainable, while remaining performant. It can be quite challenging to write C++ that achieves both, and without any errors.

One of the features is the *reference type*. You can recognise a reference by the `&` suffix. For example, consider the following extract from a class type `DataContainer`:

```C++
template <class T, int N>
class DataContainer
{
    private:
    //Array of data - potentially large!
    T data[N];
    uint32_t index = 0;

    public:
    DataContainer() : index(0) {
        for (uint32_t n=0; n<N; n++) {
            data[n] = (T)0;
        }
    }
    //Member functions
    void addSample(T nextSample);
    double calcMean();
    T operator[](int x);    //Access a sample
};
```

You can see the this object encapsulates an array which could potentially be quite large. If you now pass such types as arguments to a function, these will be copied, and the overheads could be significant:

```C++
template <class T, int N>
bool compareMeans(DataContainer<T,N> dat1, DataContainer<T,N> dat2)
{
    double m1 = dat1.calcMean();
    double m2 = dat2.calcMean();
    T y = dat1[0];
    ...
}
```

We could use pointers, but this is at the expense of readability:

```C++
template <class T, int N>
bool compareMeans(DataContainer<T,N> dat1, DataContainer<T,N> dat2)
{
    double m1 = dat1->calcMean();
    double m2 = dat2->calcMean();
    T y = dat1->operator[](0);
    ...
}
```

Instead, we can use C++ *references*:

```C++
template <class T, int N>
bool compareMeans(DataContainer<T,N>& dat1, DataContainer<T,N>& dat2)
{
    double m1 = dat1.calcMean();
    double m2 = dat2.calcMean();
    T y = dat1[0];
    ...
}
```

The code body reads as if copies had been passed, resulting in easy to read code. However, under the hood, only pointers were passed (this is hidden). 

> You cannot directly perform pointer arithmetic on a reference. If you want to do this, you need to use the `&` prefix to extract the pure pointer. For example:
>
> `DataContainer<T,N>* p = &dat1;`
>
> Similarly, you can create a reference from a pointer:
>
> `DataContainer<T,N> *p = new DataContainer<T,N>();`
> `DataContainer<T,N>& refP = *p;`
>
> It is not common to do this.

### Const and References

When arguments are passed by value, a copy is made, so there is no danger of changing the original data. Like pointers, a risk with using references is that the data might be changed by invoking member functions.

The `const` keyword can be used to prevent this. For example, the member function `calcMean` might be written as follows:

```C++
double calcMean() const {
    double y = 0.0;
    for (uint32_t n=0; n<N; n++) {
        y = y + (double)data[n];
    }
    return (y/N);
}
```

The `const` in the function declaration tells the compiler that this function does not change any of the class members. 

* `index` is not changed
* the array `data` is not modified

We say this function does not mutate the object, so is a `const` function. For reference type parameters, we also see `const` used. For example:

```C++
template <class T, int N>
bool compareMeans( const DataContainer<T,N>& dat1, const DataContainer<T,N>& dat2)
{
    double m1 = dat1.calcMean();
    double m2 = dat2.calcMean();

    double margin = 0.05*m1;                            //5% margin
    return ( (m2>=(m1-margin)) && (m2<=(m1+margin)) );  //True if they are within +-5%
}
```

The `const` in the parameters means that the objects `dat1` and `dat2` will not be mutated by the function `compareMeans`. For this to be guaranteed, the function `calcMean` must also not also not mutate the data. Therefore, `calcMean` *must* be a constant function (as discussed above) otherwise there will be a compiler error. 

Two things have been achieved here:

* The code is a lot safer. The compiler will spot if something directly or indirectly modifies data when is not expected.
* The code is efficient as only references to data are passed.

### Copy Constructors and Operators

We have met class constructors already. There is a special type of constructor known as a *copy constructor*. This allows you to instantiate and initialise one object using another (existing) object. 

> As we will discover, both stored and temporary objects can be copied. 

An example of a copy-constructor is shown in the code extract below:

```C++
template<class T, int N>
class Record
{
    private:
    T* samples = nullptr;       
    uint32_t index;             
    
    ...
    
    public:
    Record() {
        samples = new T[N];                     
        index = 0;                              
    }

    ...

    // COPY CONSTRUCTOR
    Record( const Record& other) : Record() {
        *this = other; //Call the copy assignment
    }   

    // COPY BY ASSIGNMENT  
    Record& operator=(const Record& rhs) {
        for (uint32_t n=0; n<N; n++) {
            samples[n] = rhs.samples[n];
        }
        index = rhs.index;
        return *this;   //Dereference from pointer to value
    } 
    ...

```

Note the form of the copy constuctor: *a single reference parameter of the same type*. This invokes the copy-assignment below it (to avoid code replication)

Like the copy constructor, the assignment operator has a single reference parameter of the same type.

Let's look at this code using a debugger. For these exercises, we will use Visual Studio Code and a C++ compiler as it is easier to debug (you can also use g++ on Linux or Mac OS). [See here for details](../getting_started/software-tools.md#windows-c-compiler). 


[Click Here to Watch a video op how to compile C++ on Windows.](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=d61f5039-b4d9-4622-9dba-af1e00aaa813)

Now try the following tasks:

| Task 355 | Copy Constructors and Operators |
| - | - |
| 1. | Build the code in Visual Studio Code. Create `tasks.json` to use g++ to build the code. |
| 2. | Using the debugger, find out which *constructor(s)* is/are used for the following lines: |
| - | <a title="Parameterless constructor `Record()`">Record<int, 4> A;</a> |
| - | <a title="First the parameterless constructor `Record()`, then the copy constructor `Record(const Record& other)`">Record<int, 4> C(A);</a> |
| - | <a title="That is where memory is allocated for the new Record">Why is it essential that `Record()` is always called?</a> |
| - | For the line that reads `B = A;`|
| - | <a title="All the array data in A is copied into the array of B. The index of the next sample is also copied so that the order is the same">describe the actions performed</a> |
| - | <a title="B would be unaffected as they are entirely independent copies of each other">If the data in `A` was to be subsequently changed, would this impact on `B` (and why)?</a> |
| 3. | For the statement `Y = A + B;` |
| - | <a title="The sum of A and B is written into a temporary Record `sum`. This is then copied into `Y`">How many times is data copied from one array to another, and when?</a> |
| - | <a title="Instead of writing the sum into a temporary Record, write the result directly into Y">In what way do you think this could be more efficient?</a> |
| 4. | Combine the two statements `Record<int,4> Y; Y = A + B;` into `Record<int,4> Y = A+B;` |
| - | <a title="Yes - the optimiser has somehow removed the additional copy by moving the result directly into Y">Has anything changed?</a> |

Now watch [this summary video](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=86986f21-464a-4d7f-b997-af1e00f3f43e)

**Key Points**

* In this example, we saw how one object can be allocated, and its internal data is copied from another object, thus making each independent. This is known as a *deep copy*. We used a copy-constructor to do this.

 * A copy operator `=` was also created for copying data from one object into another (already allocated) object.

 * The mechanism by which data is returned from a function depends on the compiler's ability to optimise the operations. 
    * We saw an example where a temporary object was created, only to then be copied into another and destroyed. 
    * By changing the style of the code, the compiler was able to find a way to avoid the copy.

The last point is an example of *Return Value Optimisation* (RVO). 

The following first creates `Y`, then (temporarily) creates `A+B`, so one is copied into the other.

```C++
    Record<int,4> Y;
    Y = A + B;
```

Whereas the following can avoid creating two objects by combining the operations. Logically speaking, the temporary object *becomes* `Y`. We also refer to this as a *move*.

```C++
    Record<int,4> Y = A + B;
```

This last example might seem confusing and hard to predict, so the next section might help. 

### Move Constructors and Operators

In C++ 11, *move semantics* were added to the C++ language. This enables the developer more ability to control when a copy is performed and when it can be "moved" (although copy operations may still be optimised out).

A move constructor is shown below:

```C++
// Declare a MOVE CONSTRUCTOR - used only for R-Values
Record( Record&& other) : samples(nullptr), index(0)
{   
    // Perform "move"
    this->samples = other.samples;
    this->index = other.index;
    
    //Invalidate other
    other.samples = nullptr;
    other.index = 0;  
}  
```

Note the constructor has the type `Record&&`. The `&&` signifies this is a reference to an **rvalue**.

> An **rvalue** is typically a value that cannot accessed elsewhere, such as a tempory object.
>
> Only by passing rvalues will the move consructor be invoked.

We can now see what is meant by a move. The `samples` pointer is pointed at the memory in `other`. The `samples` pointer in other is set to `nullptr` so that it cannot deallocate the memory when it (soon) goes out of scope.

> In effect, when one object is *moved* into another, ownship of and responsibility for the data is transferred. This invalidates the original object, so only makes sense for temporary objects.

The move assignment is shown below:

```C++
Record& operator=(Record&& rhs) {
    //Prevent moving to oneself!
    if (this != &rhs)
    {
        //Free existing resources (or no nothing in the case of a nullptr)
        delete [] samples;

        //Move (take ownership of the memory)
        samples = rhs.samples;
        index = rhs.index;
        rhs.samples = nullptr;
        rhs.index = 0;
    }

    return *this;   //Dereference from pointer to value
} 
```

Again, this has a parameter with the `&&` suffix. With a move, we might be overwriting existing data, so the memory is first deallocated. Then ownership is transferred.


| Task 356 | Move Constructors and Operators |
| - | - |
| 1. | Build the code in Visual Studio Code. Create `tasks.json` to use g++ to build the code. |
| 2. | Step into the line `Record<int, 4> C(A);` <a title="As persists beyond this line and can be accessed elsewhere in the code. We say A is an lvalue. A move would delete A">Why is the copy constructor used instead of the move?</a> |
| 3. | Step into the line `B = A;` <a title="The copy assignment">Which assignment operator `=` does it use? (copy or move)?</a> |
| - | <a title="As above, A is an lvalue. It cannot be moved (and hence deleted)">Why is this version used?</a> |
| 4. | Step into the line `Y = A + B;` <a title="The move assingment as A+B is a temporary result, and hence an rvalue">Which assignment operator is used and why?</a> |

Now watch [this summary video](https://plymouth.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=d79d2a77-b03d-478a-b60e-af1e00f8403e)

## Perspective

Writing copy constructors and assignment operators is much more common than move. In many cases, returning large objects from functions will be optimised into a move, but only where possible and guaranteed safe by the compiler. For many applications, many people simply trust the compiler.

In embedded systems, we have resource limited devices. If you are writing something that needs to be carefully optimised (for speed, storage or both), such as manipulating large matrices of data, then following the pattern of move constructors and assignment will allow you to predict how data is handled with more certainty.  

Sometimes there is a trade between code that is efficient and code that is easy to read.

> Being able to write `Y = A+B;` for complex objects looks like the mathematical operation it performs. It is clearly easy to read.
> 
> Through the use of move semantics, *we are able to create readable code while still being efficient*.
>
> It is the hard work and complexity behind the scenes that makes something look so easy! 

Furthermore, you should not write move operations without the equivalent copy operations also being implemented.

Copy and move operations are probably one of those tasks you need to look up to ensure you are implementing them correctly. Some commentators make the point that C++ is quite old, and over time, has become unweildy and hard to learn. However, in the embedded space, nothing has been adopted as a replacement, and even if it was, there will still be a vast quantity of legacy code. So like it or not, we are probably better knowing how to read and write modern C++ at this point in time.

## The Standard Template Library

As a general rule, we try and avoid dynamic memory allocation in embedded systems, especially those with tight resource constraints. However, on more powerful platforms (such as a Raspberry Pi or equivalent) this is more commonplace given the higher performance and larger memory.

Over the year, two standards have developed side by side:

* The C++ language
* The Standard Template Library (STL)

The STL is a collection of useful classes and functions for common tasks. These have been heavily scrutinised and tested by millions of users, and therefore usually come recommended. Many of these are available in deeply embedded systems, such as Mbed OS. It is important to be aware of their properties however.

### Standard Containers

Containers are a type of object that contain data. This includes arrays, vectors, sets and dictionaries (also known as a hash-table), as well as others.

* std::array - a C++ template class that encapsulates functionality to manage a **fixed** size array. Unusually for the STL, this uses static memory allocation, so is a direct replacement for a C++ array. It has relatively low overheads, so is a good choice for embedded systems.
 * std::vector - a C++ template class that encapsulates functionality to manage a **variable** size array. This comes with certain overheads and like most of the STL containers, used **dynamic memory allocation**. This makes it slow to acquire memory and vulnerable to memory fragmentation. 
 * std::map - a C++ template class that encapsulates key-value storage. As there is no direct equivalent built into C++, it is useful to look at this. Again, uses dynamic memory allocation, so would need to be used with great caution.

| Task 358 | Standard Template Library |
| - | - |
| 1. | Make Task-358 the active project. Build the code. |
| - | For STM32 boards, if using Mbed Studio Desktop, it might be an idea to use GCC so you can single-step this code |
| 2. | Read the comments in main and follow the instructions, uncommenting each example in turn |
| - | Use GCC and the debugger to step into each function to better understand it |
| 3. | <A title="It was possible to assign one array to another to make a full deep copy.">std::array is a value-type, whereas a C-Array is not. In practical terms, how was this demonstrated in `sort4Bytes()`?</A> |
| - | <A title="It is of variable length and uses dynamic memory allocation">How does std::vector fundamentally differ from std::array?</A> |
| - | <A title="It is sorted by key, lowest to highest">A map is an order key-value pair. If you iterate over the data, how is the data ordered by default?</A> |

This task is only a demo, and only considers the very basics of what the STL can do. Other features of the STL include:

* Algorithms - many common algorithms are included. We already saw the `sort` function being used
* File I/O - there are comprehensive libraries to help with file input/output. This uses a modern C++ interface instead of the more procedural standard C library functions.

More information about the STL can be found in [6].

## References

[1] [Microsoft, Templates (C++), C++ Language Reference](https://docs.microsoft.com/en-us/cpp/cpp/templates-cpp?view=msvc-170)

[2] [Microsoft, delete Operator (C++)](https://docs.microsoft.com/en-us/cpp/cpp/delete-operator-cpp?view=msvc-170)

[3] [Microsoft, Raw Pointers (C++)](https://learn.microsoft.com/en-us/cpp/cpp/raw-pointers?view=msvc-170)

[4] [Microsoft, Object lifetime and resource management (RAII)](https://learn.microsoft.com/en-us/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170)

[5] [Microsoft, Smart pointers (Modern C++)](https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170)

[6] [Standard Template Library](https://cplusplus.com/reference/stl/)

---

[NEXT - Lab3-Threads and Thread Synchronisation](threads1.md)

---
