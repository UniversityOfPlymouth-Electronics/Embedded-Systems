[Back to Contents](README.md)

---

# Thread Abstractions
I could not think of the right title for this section, so I've gone with _thread abstractions_. Multi-threaded programming is in itself an abstraction. The presence of a scheduler and small operating system abstracts you from both the hardware specifics and the job of task switching.

> As problems scale, if you write code at a bare-metal level, you may find yourself replicating the facilities that an RTOS provides.

We have already met what one might call "multi-threading primitives"

* Threads
* Mutex locks
* Counting semaphores
* Condition variables
* Signal-wait

Writing efficient and safe multi-threaded code using these facilities is a non-trivial task of course. 

> What you might discover is that over time, this can become somewhat repetitive as you encounter similar same problems in different projects.

It has been recognised that there are some common tasks which can be identified with known good solutions. Thankfully, some of these common tasks have been anticipated and provided (as classes) for you to reuse. 

> For such tasks, it is usually advisable to not try and reinvent your own solutions and to reuse well established and tested libraries.

Pre-built solutions to such common tasks are what this section is about and includes:

* FIFO Queues for safely moving data from an interrupt/thread to another thread
* Memory pools for safe memory allocation and deallocation
* Mailboxes which combine the above
* EventQueues for safely "dispatching tasks" to run on other threads either once or periodically.

All the above must bebe thread-safe and where blocking is employed, should block in the `WAITING` state.

> In some sense, we are introducing another layer of abstraction, protecting us from the complex details of certain multi-threaded tasks. 

## Message Queues

Where data is shared between threads, mbed offers some higher
level objects to help data move across thread boundaries or
between an interrupt and a thread.

The first of these is the message queue. This is an object that can be used to safely move data between threads and/or
interrupts. It is backed by a FIFO buffer.

In Mbed os, a message queue can be represented by the figure
below:

<figure>
<img src="../img/messagequeue.png" width="600px">
<figcaption>Message Queue - backed by a FIFO buffer</figcaption>
</figure>

The queue is backed by a fixed size (bounded) array. Data that is “put” in one end are added to the queue. If the queue is full, the put function will return an error code indicating that there are no more free resources.

The consumer end will “get” samples from the queue. For an
empty queue, this is blocking, although a timeout can be applied.

A key feature of this object is that the API for the message queue is both thread and interrupt safe.

A limitation of this object is that it can only send 32-bit integers. These can be integer values, or more often **pointers**. In the case of the latter, further support is needed for thread-safe access to shared memory. See the entry on memory pools.

In the next task, you will sample an analogue signal (convert a voltage to a number) at constant intervals using a timer interrupt. This interrupt (producer) will pass the data to a thread (consumer) via a message queue. The thread will get data from the queue and write it to the terminal.
We will examine the impact of blocking in both the producer and consumer.

| TASK-380 | Message Queues |
| --- | --- |
| 1. | Make Task-380 your active project. Read the code carefully |
| 2. | Build and run. |
| -  | The green LED should flash ON/OFF once a second. You can use this to help with the tasks below |
| -  | Check the serial terminal to see data being read from the queue and displayed |
| 3. | Press and hold button A to stop sending data into the buffer for 5 seconds. What happens? |
| 4. | Press and hold button A to stop sending data into the buffer for more than 10 seconds (to allow the buffer to become empty). What happens? |
| 5. | Press and hold button B for 5 seconds (to pause reading data from the buffer). What happens (check the LEDs)? |
| 6. | Press and hold button B for >10 seconds (to allow the buffer to fill). What happens (check the LEDs - `printf` cannot be used in an ISR)? |

This exercise illustrates a few key points:

* The Message Queue is a FIFO buffer - First In, First Out
* The buffering nature of the queue gives this system **timing slack**.
    * If the consumer end is busy, the producer (ISR) can still save the incoming data and is not held up.
    * If the producer end is busy, the consumer will read data as long as there is data in the buffer. Otherwise it will block
* Writing to the message queue is always non-blocking
    * A boolean false is returned if the buffer is full
    * A write can be safely performed in a thread context. The write is said to be both thread and interrupt safe
* Reading from a message queue can be blocking
    * A timeout can be (optional) specified to detect deadlocks
    * Read can be safely performed in a thread. It will block in the `WAITING` state when the buffer is empty. _If cannot be performed in an ISR because it is blocking_

Note how you did not need to use any mutex locks, signals or semaphores? This is all done for you. You can put and fetch data and not concern yourself with thread synchronisation.

The blocking read is a key property of the queue. 

> The idea is that if there is no data in the buffer, there is nothing to do, so read can simply block.
>
> Writing data into the queue will unblock it, and in a thread-safe and interrupt-safe way.
>
> The queue is uni-directional.

**Note**
Used standalone, the `Queue` class can only send 32-bit integers (type `uint32_t*`). The expectation (as we will learn later) is that pointers will be sent through the queue.

> Why `uint32_t*`? That looks scary!
>
> Do not be put off by the data type being a pointer. 
>
> Remember that at a physical level, there is no difference between `uint32_t` and `uint32_t*`. **Both are simply 32-bit integers** (size is platform specific). *The only difference is how the compiler interprets operations, such as arithmetic*

### Challenge
Can you add a watch-dog to this application so that if the buffer becomes full, the device resets?

### Pointer Arithmetic Challenge
Consider the two sections of code below:

```C++
uint32_t u = 0;
u = u + 1;

uint32_t* v = 0;
v = v + 1;
```

Can you predict the final values of `u` and `v`? Explain.

*Hint:* If you use `printf`, you can use the `%p` placeholder for pointer types (instead of `%u`).

