[Up - Digital Outputs: Week 2](Digital_Outputs_1.md)

--- 

## Task102 - 1
In this task, you are going to try and write some code for yourself, using code provided as a starting point. There is no expectation to write clever or elegant code, just something that works!

| TASK | Details |
| --- | --- |
| 1 | Set `TASK-102-SOS` as the active project |
| 2 | Build the project |
| 3 | Run the code. Press the BLUE button the Nucleo board to start |
| 4 | Press the BLACK reset button to reset the Nucleo board |
| 5 | Now debug the code, stepping line by line to understand the flow of the code |
| 6 | Modify the code to repeatedly play a major scale (C,D,E,F,G,A,B,C). Each note should last 250 ms (250,000 &micro;S)
|| 

## Task102 - 2 SOS
Next, we are going to take the idea above and extend it to something closer to a real-world application. The task is to get the board to output the morse-code for SOS (both with light and sound):

| TASK | Details |
| --- | --- |
| 7 | Modify the code to repeatedly output the morse code for SOS (details below). Ensure the LED is ON while a tone is playing and OFF during a pause |
|| 

<figure>
<img src="../img/sos.png" width=300>
<figcaption>SOS in morse code. Short beeps are called "dots"; long tones are called "dashes". Note also the pauses between tones</figcaption>
</figure>

| Symbol | Duration (ms) |
| --- | --- |
| DOT | 150 |
| DASH | 450 |
| --- | --- |
| Symbol Space | 1 dot |
| Letter Space | 3 dots |
| Word Space | 6 dots |
||  ||

Assume SOS is one word.

## A closer look at sound output
Let's look at the code to see what is new. First of all, a new object _type_ is created in the code:

```C++
Buzzer buzz;
```

A new object `buzz` was created, of type `Buzzer`. This is NOT part of Mbed os, but a new object _type_ created by the tutor. The code is purposely hidden away (but you can find it if you are determined!)

To make a sound, we tell this object to play a note using a statement such as the following:

```C++
buzz.playTone("C");
```

We say that `buzz` is an *object*, and `playTone` is the `member function` that makes the object do something useful. 

> **dot notation**. Note how the object and function are separated by a dot (sometimes known as *dot notation*). We see this a lot in C++ and many other OOP languages.
>
> In general we can write the following:
> ```
> <object>.<member_function>([<parameters>])
> ```
>
> where the _square parenthesis_ [] indicate that parameters are not always specified or required. 

For the `playTone` function, a parameter _is_ needed (to tell it which note to play). The *string* "C" is a *function parameter* passed to the function `playTone`. This is the required additional information needed to play a note.

In short, you end up with code that is simple to write and understand. This is possible because we have a *device driver* to hide away the complexities of interacting with the hardware.

> **Device Drivers** 
>
> The details of playing a tone are hidden within the `Buzzer` code. You could look at the code, but for now, there is really no need. This is the same of other _types_ of object, such as `DigitalOut`
> 
> Code that is written to provide access to hardware devices is known as a *device driver*. Once again, C++ has been used to hide away the complexity so you can focus on the functionality of your application.

You will not always have access to a device driver, and sometimes we cannot avoid writing our own. This is a typical role for a developer with knowledge of electronics and is something you will do later in course.


## Quiz
Please attempt all questions in the following Quiz. This is important and you should not proceed until you have done this.

[Click here to complete the Quiz](https://dle.plymouth.ac.uk/mod/quiz/view.php?id=1161832)

Next, we are going to cover another type of output: text. For this, we will stick to tradition and meet the "Hello World" application, embedded style!

---

[NEXT - Task 103 - Hello World](TASK103.md)