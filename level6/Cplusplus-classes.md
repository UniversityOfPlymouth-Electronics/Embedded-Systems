
[Back to Contents](README.md)

---

# C++ Classes
One of the main differentiators between C and C++ is the existence of a Class. A class can be thought of as as custom data type. 

To really understand classes, we will first write some C using structures to encapsulate data and write an API.

We then look at the C++ equivalent and hopefully see how classes make out code safer and cleaner.


## Related Lectures
For Plymouth students, the relevant lecture slides are here:

| Lecture | Title |
| - | - |
| 02-02 | [02-02- Classes](https://dle.plymouth.ac.uk/mod/url/view.php?id=1162257) |
| |

## Creating a Simple Class
To see how a class is built in C++, we will work through an example

| **TASK 321** | Complex |
| --- | --- |
| 1. | Set Task 321 as the active program. Build and run to see the output |
| 2. | In debug mode, step **over** each line in Main.cpp to see the output |
| | |

Let's look at each part in turn:

```C++
    ComplexNumber c1(2.0,3.0);
    ComplexNumber c2(1.0,-1.0);
```

These create two complex number objects, `c1` and `c2`. The real and imaginary values are passed by parameter.

Like structures, by default we can copy an object using `=`. Like structures, this uses _value semantics_.

```C++
    ComplexNumber c1_copy = c1;
```

The next line performs an _in-place_ modification of `c1`

```C++
c1.add(c2); 
```

Mathematically this would like writing `c1 = c1 + c2`.  

> **It is the object `c1` that has been modified by the `add` function.**

Notice that unlike structures, we can also use the _dot notation_ to invoke functions. These functions perform operations on the object. 
>
> These are known as **member functions** and you may recognise this from using Mbed-os objects such as `DigitalOut`.

We can verify that `c1` has been modified by the next line:

```C++
c1.display();
```

Again, there is the dot notation being used with a member function. It is the contents of `c1` that are being displayed.

The next line illustrates the value semantics:

```C++
c1_copy.display();
```

We can see that `c1_copy` has not been affected by the add operation. It is an independent copy. 

Another copy operation can be see in the next three lines:

```C++
    ComplexNumber c3 = c1.addedTo(c2);
    c3.conjugate();
    c3.display();
```

To give you some insight, as we will see later, a new complex number is created and is equal to the complex sum of `c1` and `c2` to. This is then copied into `c3` using the default `=` operator.

We then perform a conjugation on `c3` (negate the imaginary part) and display it.

Finally, we demonstrate what happens when an object is discarded.

```C++
    {
        ComplexNumber test(1.0);
        test.display();
    }
```

The code between the curly-braces `{ }` contains a local variable `test`, type `ComplexNumber`. Once we go past the closing brace, `test` goes out of scope and is destroyed. however, "by'ee" is written to the terminal before it is destroyed.


## So where is the code?
For all of the above, you may be wondering where the code is! The easy way to discover this is using the debugger.

| **TASK 321** | Complex |
| --- | --- |
| 3. | Start the task in debug mode |
| 4. | Step **into** the following line |

```C++
ComplexNumber c1(2.0,3.0);
```

This will take you into the `ComplexNumber` class, and specifically into the **constructor** function

```C++
    ComplexNumber(const double r, const double i=0.0) {
        this->real = r;
        this->imag = i;
    }
```

Look at the class and familiarise yourself with the code.

> A constructor is a very important function. It is the function that runs *automatically* when you create an object.

Note the following:

* It must have the same name as the class
* It has no return type
* There can be more than one constructor, as long as their parameters are unique
* It must be in the **public** section of the class

You can see in this example it sets the `real` and `imaginary` properties of `c1` to the values passed by parameter.

Constructors are often used to initialise an object. They run automatically, so you can't forget!

| **TASK 321** | Complex |
| --- | --- |
| 5. | Once back in Main, step **into** the following line |
| |

```C++
ComplexNumber c1_copy = c1;
```

This is an interesting one. We are creating `c1_copy`, and it may to need a constructor. In this case, it is a special constructor known as a _copy constructor_:

```C++
    ComplexNumber(const ComplexNumber& c) {
        this->imag = c.imag;
        this->real = c.real;
    }
```

* It provided, this will be called so you can perform all the necessary custom initialisation. It is up to you what happens. 
* If not provided, a default copy will occur (as with structures).

| **TASK 321** | Complex |
| --- | --- |
| 6. | Comment out the copy-constructor and test. Are the results any different in this case? |
|     | Now uncomment the code. We may wish to use it later |
| 7. | Now step upto the following line |
|    | `ComplexNumber c3 = c1.addedTo(c2);` |
|    | Note the values of `c1` and `c2` |
| 8. | Now step **in** to the `addedTo` function |
|    | Once inside the `addedTo` function, hover the mouse over parameter `c` and `this`. Which one is which? |

Let's look at the code:

```C++
    ComplexNumber c3 = c1.addedTo(c2);

    ... which invoked the following function ...

    ComplexNumber addedTo(const ComplexNumber& c) {
        return ComplexNumber(this->real+c.real, this->imag+c.imag);
    }
```

* The `addedTo` function applies to the object `c1`. 
   * Once inside the function, `this` is a pointer to `c1`
   * The type of `this` is `ComplexNumber*`
   * It is as if we can passed the pointer as a parameter (more on this later)
* The function parameter `c2` is _passed by reference_. 
   * We see the data type is `ComplexNumber&`
   * This is similar to a pointer in that it is a reference type, but we still use the dot-notation and cannot do (dangerous) pointer arithmetic on it.
   * C++ references are sometimes consider _safe pointers_

| **TASK 321** | Complex |
| --- | --- |
| 9. | Step to the line `c3.conjugate();` and note the values in `c3` by hovering the mouse over it |
|    | Step into this line |
|    | Note the value of `this` |
|    | Step over the line `this->imag *= -1.0;` |
|    | Back in main, see what has changes in `c3` |

Finally, there is one more experiment to do:

There is another special function, the _destructor_

```C++
    ~ComplexNumber() {
        cout << "Bye'ee" << endl;
    } |
```

| **TASK 321** | Complex |
| --- | --- |
| 10. | In `ComplexNumber.hpp`, find the destructor function and add a breakpoint to it's  single line of code |
|     | Step over each line of main until the code stops on the break-point |
|     | What prompted this function to run? |
|     |


## Understanding _this_
You might be confused about what the _this_ keyword represents or where it comes from. We can explain this by comparing with a C program that uses structures. This is the same example used in the lecture.

| **TASK 322** | BMI C API |
| --- | --- |
| 1. | Make Task322 the active project |
| 2. | Build and run to see the output |
| 3. | Find the declaration of the `Human` data type (hint: right-click the work `Human` in the code and select Go to Definition) |
| 4. | Find the declaration of `initHuman`. What does it do and what data type does it return? |
| 5. | For the line `Human person = initHuman(45, 97, 1.9);` is this using reference or value semantics? |
| |

Let's look at the main code:

```C++
#include "mbed.h"
#include "Human.h"

int main(int argc, const char * argv[]) {
   
    //Designated initialiser
    Human person = initHuman(45, 97, 1.9);
    displayHuman(&person);
    
    //After a major lifestyle change
    updateWeight(&person, 75.0);
    displayHuman(&person);

    return 0;
}
```

First of all, we note the this is using the C language, albeit with a C++ compiler.

The following line uses value semantics (copy) to create an initiaised structure:

```C++
    Human person = initHuman(45, 97, 1.9);
```

| **TASK 322** | BMI C API |
| --- | --- |
| 6. | Step **into** this line with the debugger to see the code inside the function `initHuman` |
||

This function is used to create a new _instance_ of `Human`. It also initialises it.

```C++
Human initHuman(unsigned a, float wt, float ht) {
    Human hh = {.age = a, .weight = wt, .height = ht};
    calculateHumanBMI(&hh);
    return hh;
}
```

As you can see, when calling this function all critical parameters must be passed and the BMI is automatically calculated.

> The idea of initialising a data structure at the point a data structure is created a key theme. In a C++ class, this is the role of the _constructor_ function.

| **TASK 322** | BMI C API |
| --- | --- |
| 7. | Step **into** the line `calculateHumanBMI(&hh);` with the debugger to see the code inside  |
||

First of all, note the parameter being passed is the **address** of a `Human` structure. This allows it to be modified in-place.

Stepping in we see the following:

```C++
static void calculateHumanBMI(Human* h) {
    h->bmi = h->weight / (h->height * h->height);
}
```

Note the first parameter is a **pointer** to an object of type `Human`. This means we can operate directly on the memory of that object. As we saw, this also happens with C++ classes using the `this` pointer, except with class member functions, it is hidden.

> **You can consider the `this` pointer to be a hidden first parameter in every class member function**

Note also that this is a `static` method. This means it can only be called from within `Human.cpp` and nowhere else. In essence, it is hidden away from other source files. You cannot call this function except from within `Human.cpp`. This is because there is no need as we will see.

> We might say the function `calculateHumanBMI` is **private**
>
> C++ Classes have `public` and `private` sections, only they can enforce even stricter rules.


| **TASK 322** | BMI C API |
| --- | --- |
| 7. | Back in Main.cpp, step **into** the line `displayHuman(&person);` with the debugger to see the code inside  |
||

Once again, it is the address that is passed. Looking inside the function, we see a function where the first parameter is a pointer of type `Human*`

```C++
void displayHuman(const Human* h) {
    printf("Age: %u, Weight: %f, Height: %f, BMI: %f", h->age, h->weight, h->height, h->bmi);
    if (h->bmi>=25.0) {
        printf("*");
    }
    printf("\n");
}
```

This time, the function only needs to read the data, so the parameter type is `const Human*`.

| **TASK 322** | BMI C API |
| --- | --- |
| 8. | Try to add a line that modifies `h->bmi`. Does it compile?  |
||

Again we return to `Main.cpp` and look at the next line:

```C++
updateWeight(&person, 75.0);
```

| **TASK 322** | BMI C API |
| --- | --- |
| 9. | Back in Main.cpp, step **into** the line `updateWeight(&person, 75.0);` with the debugger to see the code inside.  |
||

Again, a similar pattern is observed:

```C++
float updateWeight(Human* h, float ww) {
    float prev = ww;

    //Update property
    h->weight = ww;

    //Update stale calculated properties
    calculateHumanBMI(h);

    return prev;
}
```

The first parameter is the now-familiar pointer. This allows the function to make changes to the data structure. The second parameter is a value type, which is the new `weight`.

The weight is updated with the line:

```C++
    h->weight = ww;
```

but note also the following line that follows:

```C++
    calculateHumanBMI(h);
```

> In updating the `weight` property (via the function `updateWeight`), the `bmi` property is automatically recalculated. This prevents the user from forgetting to update properties that are derived from others 

### Safety
Hopefully, you can see some of the safely features adopted here.

If only the API is used, the we gain the following benefits: 

* When a structure is created, the critical data is required as parameters in the function. 
   * This prevents use of an object before it is initialised. 
   * The derived property `bmi` is also calculated automatically.
* When a property such as `weight` or `height` is updated, so the derived property `bmi` is automatically recalculated
   * This prevents stale properties
* We were able to hide functions that are "internal use only". In this case, it was the `calculateHumanBMI` function. This helps to simplify the API and reduce the temptation do do something out of sequence.

Although this is a great improvement, it is not perfect however. _It is still possible to directly modify the properties of the structure and bypass the API_. 

For C++ classes, we can exercise greater control.

| **TASK 323** | BMI C++ API |
| --- | --- |
| 1. | Make Task-323 the active project |
| 2. | Build the code, then step through the code with the debugger |
|        | Step into each function to see how it works |
| 3. | Modify main and uncomment the following line `//person._height = 0.0;`
| 4. | Try and build the code. What happens and why? |
| |


## Challenge
Return to Task 321. Add some additional functions to the `ComplexNumber` class. 

* `negate` - negates both real imaginary parts 
* `negated` - Same as `negate`, but returns a copy
* `subtract` - (see `add`)
* `subtractFrom` - (see `addedTo`)
* `multiply`
* `multiplyWith`
* `divide`
* `divideWith`

Write code in Main.cpp to test your new member functions.

## Looking Ahead
Right now, you might find it the difference between `add` and `addedTo` confusing. When we discuss **operator overloading**, suddenly you code will look much more natural!

## Case Study: Simple Device Driver
Let's move away from abstract mathematical code and get back to embedded systems. By now we are familiar with types such as `DigitalOut` and `BusOut`. These are classed as _device drivers_. Two key attributes of a device driver:

* consistent software interface on different hardware
* abstracts the developer making code simpler and safer to write

There are two key terms associated with object orientated programming:

> **Encapsulation** is where data and functions (also known as methods) are bound together such that implementation details are hidden and protected (data hiding).
>
> `DigitalOut` is a good example of this. It has the same interface on all Mbed-os boards (of which there are many, with each implementation written by the hardware vendor). The hardware specifics are hidden from the developer.
>
> **object composition** is where an object contains other objects. 
>
> A good example of this is `BusOut` which contains an array of `DigitalOut` objects. 

We will now write a driver of our own, that uses object composition to simplify the control of a traffic light (3 LEDs and a hardware timer).

| **TASK 325** | Device Driver |
| --- | --- |
| 1. | Make Task-325 the active project |
| 2. | Build and run the code. Press and release the blue button to advance to the next state |
| 3. | Study the code in detail |
| | |

Note how the code has been split between a header file `TrafficLight.hpp` and an implementation file `TrafficLight.cpp`

> You could write all your class in the header file. However, there are reasons you might prefer to split them, including:
> * If you are writing a commercially sensitive closed-source library, you might not want to reveal your functions. 
> * If the class becomes large, it is helpful to split it into separate source files

### The scope operator `::`
The scope operator `::` frequently appears in the `TrafficLight.cpp` file.

* When you define a member function outside of a class body, you prefix it with `<ClassName>::<function-name>`. This differentiates with from a global function.
* Sometimes you reference members of a class from outside also using the scope operator
  * In Main.cpp, the enumerated type `LIGHT_STATE` cannot be used directly as it is part of the `TrafficLight` class. 
  * You therefore see the scoping operator `TrafficLight::LIGHT_STATE s;`

### Object Composition and Initialisation
Look inside `TrafficLight.h` and we can see the following private members:

```C++
    private:
    DigitalOut redLED;
    DigitalOut yellowLED;
    DigitalOut greenLED;
    Ticker t;
```
This is a clear example of object composition. Note the following:

* These are all private members. Only class member functions will have direct access to these objects.
* The Objects are not yet initialised. 
   * The `DigitalOut` constructor must have at least one pin name (type `PinName`) - it does not have a parameterless constructor.
   * The `Ticker` does have a parameterless constructor so can be created without further information 

The Traffic light constructor _must_ contain code to initialise these objects immediately.

| **TASK 325** | Device Driver |
| --- | --- |
| 4. | Open `TrafficLight.cpp` and find the constructor |
| 5. | Put a breakpoint on the first line and start in debug mode. Which runs first, `main` or the constructor? |
| |  |
---

This highlights what is referred to as "code before main".

### Member Initialisation Lists
The constructor for `TrafficLight` has a member initialisation list. The constructor declaration has a list of parameters. These are passed to a list of other constructors (separated by a colon). You can think of this as _chaining constructors_ so they run in the correct order.

```C++
TrafficLight::TrafficLight(PinName redPin, PinName yellowPin, PinName greenPin) 
        : redLED(redPin), yellowLED(yellowPin), greenLED(greenPin)
{
    // These objects are already initialised in the member initialisation list above
    redLED = 1;
    yellowLED = 0;
    greenLED = 0;
    // Timer off
    flashYellow(false);
}
```

For the body of the constructor to work, the objects `redLED, yellowLED and greenLED` must already exist.

> The objects in the initialisation list will be created and initialised **first**. _Then_ (and only then) the `TrafficLight` object will be initialised.

### Challenge 1
Extend the `TrafficLight` class API to include the following public member functions:

* `void stop()` - which resets the lights to red at any point
* `void setFlashSpeed(double)` - which sets the speed of the flasher
* `double getFlashSpeed()` - which returns the current flash speed.

These must all be `public`. Any additional members must be `private`. You also need to test these new APIs.

### Challenge 2
Modify the class to allow the second set of traffic lights to be used. Note that these require open-drain (`DigitalInOut`).

Hints

* Consider replacing `DigitalOut` with `DigitalInOut`
* Rather than pass pin names to the constructor, consider a single parameter to specify which set to use.
    * Use an enumerated type to make the code clear
    * Set the correct output mode depending on which set is used.

Write some demo code to simulate a road with two traffic lights, one at each end.

---

[NEXT - Lab2-C++ and OOP](Cplusplus-oop.md)