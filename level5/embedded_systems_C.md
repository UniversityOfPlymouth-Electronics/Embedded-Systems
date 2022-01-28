[UP - Table of Contents](../README.md)

---
 
# Embedded Systems - Level 5

## What is new
This content has been migrated from [a previous version](http://blogs.plymouth.ac.uk/embedded-systems/microcontrollers/mbed-os-2/courses/embedded-systems-in-context-level-4/foreward/) based on mbed-os 5.

Changes for 2021:

* Migration of materials on Blocking, Polling, FSM and Interrupts to level 5 (previously delivered in stage-3)
 * Adoption of Mbed OS into level-5


# Level 5 Course
This course is divided logical blocks:

| Block | Content | - | Weeks |
| --- | --- | --- | --- |
| 1. | Review of Mbed-OS and Interfacing | [Lab-1-1-DigitalIO](DigitalIO.md), [Lab-1-2-C and C++ Structures](Cplusplus-structures.md), [Lab-1-3-Interfacing-**TBD**](interfacing.md) | 1-3 |
| 2. | Multi-tasking 1: Blocking, Polling and State Machines | [Lab-2-1-Rapid Polling and State Machines](rapid-poll.md), [Lab-2-2-Interrupts](interrupts.md) | 4 - 6 |
| 3. | Coursework | | 7 - 13 |
| |


## Using the Glossary
Some crucial information is contained in the [glossary](/glossary/README.md).

This is so that the document is not cluttered with every detail. Do not ignore the glossary. You should read every entry referenced in each lab. In many cases, you may see a hyperlinked word (jargon typically). Some of these are links to glossary items. If you select them you can jump to the glossary items.

## Setting Expectation
Remember that each student on the course may have a slightly a different background. Some will be returning from placement; others may be repeating then module. There are many variations.

This module is designed on the assumption that you have some knowledge and experience of embedded C programming, and some familiarity with Mbed.  However, the first lab will be a refresher on interfacing with Mbed and Mbed Studio. 

We will discuss what we mean by **blocking hardware** and the problems it presents.

We will then review some approaches to managing multiple hardware devices in real-time, namely:

* Rapid polling loops
* Interrupts (and interrupt safety)

Some of this may be familiar from level 4. However, repetition is often helpful as students don't often grasp the concepts first time. 

> Even if you have done some of the above before, beware of complacency and seek opportunities to push yourself and try to go deeper into the subject.

As a final remark, this is a fairly intensive course. Much of the programming will be new, but in our experience, students who grasp it take it further when they attempt to write their own projects. This content also underpins the content in level 6 (Real Time Operating Systems).


## Your Kits
Different students may already have some of the equipment needed, depending on the year you first enrolled. You will be provided additional components that enable you to work both in the lab and at home. 

You may also be loaned other equipment, such as a "Picoscope" (assuming you don't already have one).


## Attending Labs
Formal labs are scheduled at specific times in your timetable. Whether you are attending in person or remotely, you should use the Teams channel for that lab.

Look for the channel that says "Lab Sessions"

<figure>
<img src="../img/Teams143-Expand-Lab-Sessions.png" width="300">
<figcaption>Screen capture from the ELEC143 module Team. Your module code may be different</figcaption>
</figure>

When you click this channel, you should see meeting links

<figure>
<img src="../img/Teams143-Lab-Meeting.png" width="600">
<figcaption>Click the appropriate lab session (module codes again will vary) and join the meeting. Turn off your camera and microphone</figcaption>
</figure>

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



