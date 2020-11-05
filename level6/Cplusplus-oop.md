[Back to Contents](README.md)

---

Topics

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
The function `setReal` is overloaded three times:

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

> The line `n3 = n2;` would simply copy the value of `n2` into `n1`.

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
Now we move to an important topic, whereby one class can inherit many of the properties of another

## Function Override

## Polymorphism and Virtual Functions

## Multiple Inheritance

## Pure Virtual Functions

## Rules about constructors

https://docs.microsoft.com/en-us/cpp/cpp/constructors-cpp?view=vs-2019#:~:text=%20Constructors%20%28C%2B%2B%29%20%201%20Member%20initializer%20lists.,section.%20%206%20See%20also.%20%20More%20


## Namespaces

## C++ Structures

## Summary of Key Terms / Jargon

Encapsulation
Composition
Inheritance
Overload
Override

