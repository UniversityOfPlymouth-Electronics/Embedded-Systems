[UP - Table of Contents](../README.md)

---
 
*Looking for content on SystemVerilog and Digital System Design?*
[see this repository](https://github.com/UniversityOfPlymouth-Electronics/DigitalSystems).

# Embedded Programming - Level 5

This is a level-5 course in embedded programming. In this module, we focus on the software engineering aspects. To make this more productive, we will use Mbed (as we did in stage-1). This allows us to focus on learning to be better programmers, without the distraction and complexity of hardware specifics.

**Changes for 2022:**

The following changes are confirmed.

* [New Driver Library](https://github.com/UniversityOfPlymouth-Electronics/libuopmsb) is now used to assist with managing different board versions. This includes support for the new devices. These notes have been updated to reflect this.
* All projects are updated to Mbed-OS 6.X and use Mbed Studio 
* Various corrections and typos fixed
* Back porting of topics on blocking, interrupts, rapid polling and state machines
* Some content specific to C++

**Changes for 2023:**

* Introduction of PROJ200, replacing ELEC240 and ELEC241 (level 5)
* Embedded Programming continues with Mbed OS in level 5
   * Further C programming
   * Rapid Polling
   * Software State Machines
   * Interrupts
   * Interfacing
* Bare metal programming has been rationalised and moved from level 5 to level 6
* Added Task-255 showing how to perform switch debounce using interrupts

# Level 5 Course
This course covers a number of topics in embedded programming

| Topic | Content | - | Duration (Weeks) |
| --- | --- | --- | --- |
| 0. | Revision | [DigitalIO](DigitalIO.md) | Self Study |
| 1. | Further C Programming - Structures, Unions and Bitfields | [Further C Programming](Cplusplus-structures.md) | 1 |
| 2. | Rapid Polling and Software State Machines | [Rapid Polling](rapid-poll.md) | 2 | 
| 3. | Interrupts | [Interrupts](interrupts.md) | 2 |
| |

## Setting Expectation
Remember that each student on the course may have a slightly a different background and levels of experience; others may be repeating then module. There are many variations.

This module is designed on the assumption that you have some knowledge and experience of embedded C programming in stage-1, and some familiarity with Mbed.  However, the first lab listed above can act as a refresher on writing C with Mbed and Mbed Studio. 

We will then look at what we mean by **blocking hardware** and the problems it presents.

We will then review two approaches to managing multiple hardware devices in real-time, namely:

* Rapid polling loops
* Interrupts (and interrupt safety)

In stage-4, we will go on to look at multi-threaded programming.

Some of this may be a refresher of what you were taught in level 1. However, repetition is often helpful as students don't often grasp the concepts first time. 

> Even if you have done some of the above before, beware of complacency and seek opportunities to push yourself and try to go deeper into the subject.

As a final remark, this is a fairly intensive course. Some of this will be new, but in our experience, students who grasp it take it further. If you master it, it is a gateway to access more advanced applications in stage-4.


## Your Kits
Different students may already have some of the equipment needed, depending on the year you first enrolled. You will be provided additional components that enable you to work both in the lab and at home. 

## Attending Labs
Formal labs are scheduled at specific times in your timetable. Whether you are attending in person or doing some self-study, you can use the Teams channel for that lab to ask questions.

## Self Study
It is expected that students spend time completing lab tasks as part of self-study. You are unlikely to complete all tasks in the timetabled lab time. **This is a critcal part of undergraduate study.**

## Lectures
Some of the timetabled time is dedicated to a form of lecture, which often includes live demo's. Not everything can be covered in lectures. Success in this module depends on engaging in both lectures and labs. Some of the finer details will only be found in lab sessions. 

We do try to record all lectures, but this is not always possible.

> On the right hand-side, locate the "Panopto Block"

<img src="../img/PanoptoBlock.png" width=300>

There you will find links to recorded lectures. You can also subscribe to these if you have a RSS on your computer or smart-device.

> Panopto is our University video streaming service. It supports multiple video streams, closed captions and chapter points. This makes it much easier for students to find content within a video.
>
> Some videos are restricted to a specific cohort of students, where others may be public. Please do not distribute these videos elsewhere.  

---
NEXT - [Further C Programming](Cplusplus-structures.md)





