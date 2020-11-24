[Back to Contents](README.md)

---

# C and C++ Object Orientated Programming
C++ is a large language that takes a long time and practise to master. We will focus on core object orientated concepts. Even if you don't use all of these, you may encounter code that does.

The focus of all the sections below is on C++ classes. This is one of the major differences between the C language and C++. 

The examples are initially kept purposely simple to illustrate the key points. Then something closer to a real-world example is presented. These are arguably more interesting, but at the same time can quickly become complex. So my apologies in advance if some of the examples are somewhat contrived. Be reassured the concepts are the same and we will look at more real-world examples later.

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

> When we derive a class, we gain access to the `protected` members as well as the `private` 
>
> This is a key difference between inheritance and composition

The downside is that inheritance is more complex and arguably harder to write.

That's a lot, but yes, there is more! (yippee I hear you cry). 

_What if one of the parent class behaviours needs to be changed (or as we say, overridden)?_

This is the topic of the next section: function override.

## Function Override
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

## Polymorphism and Virtual Functions

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

## Further topics

### Multiple Inheritance
C++ allows us to  inherit code from more than one class. You can see an example of this in Task-340B

### Pure Virtual Functions
Some other languages have "interfaces", which are similar to classes, but contain no code. The nearest equivalent in C++ is "abstract classes". This is a rather an advanced topic, but an example has been provided in Task-342




---


[Back to Contents](README.md)

---
