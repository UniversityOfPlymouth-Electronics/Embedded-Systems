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

# Level 5 Course
This course covers a number of topics in embedded programming

| Topic | Content | - | Weeks |
| --- | --- | --- | --- |
| 1. | Review | [Lab1-DigitalIO](DigitalIO.md), [Lab2-C and C++ Structures](Cplusplus-structures.md) | 1-5 |
| 2. | Serial Interfacing | [Lab3-Serial Interfacing - Coming Soon](SerialInterfacing.md) | 6 |
| 3. | Multi-tasking: Blocking, polling, interrupts | [Lab4-Rapid Polling](rapid-poll.md), [Lab5-Interrupts](interrupts.md) | 7-8 |
| 4. | Group Project and Management | [Using Collaborative Tools](.), Coursework P1 | 9-13 | 
| |

## Setting Expectation
Remember that each student on the course may have a slightly a different background and levels of experience; others may be repeating then module. There are many variations.

This module is designed on the assumption that you have some knowledge and experience of embedded C programming in stage-1, and some familiarity with Mbed.  However, the first lab will be a refresher on interfacing with Mbed and Mbed Studio. 

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

You may also be loaned other equipment, such as a "Picoscope" (assuming you don't already have one).


## Attending Labs
Formal labs are scheduled at specific times in your timetable. Whether you are attending in person or doing some self-study, you can use the Teams channel for that lab to ask questions.

Labs will also contain interactive elements. There will typically be a briefing at the start and a poll part way through. Participating in these is important.

## Lectures
Each week there is a lecture, which often includes live recorded demo's. By the time you read this, the first lecture will have been delivered and recorded.

If you did not manage to attend the lecture for this week, please ensure you catch up via the video hosted on the [DLE](https://dle.plymouth.ac.uk).

> On the right hand-side, locate the "Panopto Block"

<img src="../img/PanoptoBlock.png" width=300>

There you will find links to recorded lectures. You can also subscribe to these if you have a RSS on your computer or smart-device.

> Panopto is our University video streaming service. It supports multiple video streams, closed captions and chapter points. This makes it much easier for students to find content within a video.
>
> Some videos are restricted to a specific cohort of students, where others may be public. Please do not distribute these videos elsewhere.  

---
[NEXT - Lab1-DigitalIO](DigitalIO.md)





