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

* FIFO Queues for safely moving data from an interrupt/thread to another interrupt/thread
* Memory pools for safe memory allocation and deallocation
* Mailboxes which combine the above
* EventQueues for safely "dispatching tasks" to run on other threads either once or periodically.

All the above must be thread-safe and where blocking is employed, should block in the `WAITING` state.

> In some sense, we are introducing another layer of abstraction, protecting us from the complex details of certain multi-threaded tasks. 

## Message Queues

Where data is shared between threads, mbed offers some higher
level objects to help data move across thread boundaries or
between an interrupt and a another interrupt or (more typically) thread.

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
empty queue, this is blocking if a timeout is specified. There are non-blocking versions as well.

A key feature of this object is that the API for the message queue is both thread and interrupt safe.

A limitation of this object is that it can only send 32-bit integers. These can be integer values, or more often **pointers**. In the case of the latter, further support is needed for thread-safe access to shared memory. See the entry on memory pools.

In the next task, you will send data at constant intervals using a timer interrupt. This interrupt (producer) will pass the data to a thread (consumer) via a message queue. The thread will get data from the queue and write it to the terminal. We will examine the impact of blocking in both the producer and consumer.

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
* Writing to the message queue is usually non-blocking (although other variants exist)
    * A boolean false is returned if the buffer is full
    * A write can be safely performed in a thread context. The write is said to be both thread and interrupt safe
* Reading from a message queue can be blocking
    * A timeout can be (optional) specified to detect deadlocks
    * Read can be safely performed in a thread or an interrupt. However, if a timeout is specified, it will block in the `WAITING` state when the buffer is empty. In such cases, _it should not be performed in an ISR because it is blocking_ (see the non-blocking APIs)

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

## Memory Pool
In the previous example, a message queue was used to (safely)
pass a simple integer from an ISR to a thread. In the next task, we pass a more complex data structure with the aid of another object, a memory pool.

<figure>
<img src="../img/memory-pool.png" width="600px">
<figcaption>Memory pool. A pre-allocated block of memory divided into equal size segments. Each segment is enough space for the specified data type</figcaption>
</figure>

A memory pool is a pre-allocated block of memory, divided up into equal size segments. It provides a thread-safe and interrupt-safe mechanism to "requesting" and "releasing" a block of memory.

We then fill this segment of memory with some data and send the address through a message queue.

| TASK-382 | Memory Pools |
| --- | --- |
| 1. | Build and run Task 382. Use the serial monitor to view the output |
| 2. | Add some code to the ISR to busy-wait block on buttonA |
| - | What happens if you hold down buttonA? |
| 3. | Add some code to the consumer thread to busy-wait block on buttonB |
| - | What happens if you hold down buttonB? |
| 4. | For each interrupt, how many bytes are sent by the message queue to the consumer thread? |
| 5. |  The objects use shared memory without any locks. Why is this code thread safe? |

First, let's look at how we create the memory pool:

```C++
//Memory Pool - with capacity for 16 message_t types
MemoryPool<message_t, 16> mpool;

//Message queue - matched to the memory pool
Queue<message_t, 16> queue;
```

Both the Memory Pool and Queue has the same dimensions (16). However:

* The memory pool reserves `16 * sizeof(message_t)`
* The queue reserves space for 16 pointers

The angle brackets are a C++ feature known as **templates**. This is a somewhat advanced C++ topic, but one well worth researching.

Note the following code in the ISR:

```C++
message_t* message = mpool.try_alloc();
```

This asks the memory pool for a block of memory (same size as the structure type `message_t`). It is NON BLOCKING and will return NULL if the memory is already fully allocated.
It can also be called from an ISR context.

Note that `message` is a pointer to a block of memory. This is now filled with data as follows:

message->fValue = sample;
message->sw1State = switch1State;
message->sw2State = switch2State;
```

We then send the pointer to this block down the queue.

```C++
bool ok = queue.try_put(message);
```

At the receiving end (thread), we see the blocking call to read data from the queue:

```C++
message_t* payload;

//Block on the queue (non blocking versions exist)
bool ok = queue.try_get_for(10s, &payload);
```

Note that the pointer is now copied into the variable `payload`. **The next two steps are very important**:

1. You must copy the data pointed to by `payload` into a (local) variable, in this case `msg`

```C++
message_t msg(payload->fValue, payload->sw1State, payload->sw2State);
```

Here we use a constructor to create a new instance of `message_t` and copy the values.

2. Once you have a copy, you must free the memory up for another sample:

```C++
mpool.free(payload);
```

If you forget to free the memory, the memory pool will fill and attempts to allocate will return a `NULL`.

### Dynamic memory vs memory pools
Some might be wondering why we need this given dynamic memory allocation already exists in C and C++.

For those unsure what this means, this is where you also request a quantity of memory from the region of the system memory known as the **heap**.

* In C you use `malloc` to request a block of bytes and `free` to return it
* In C++ you use `new` and `delete`

Dynamic memory allocation can be both slow and hazardous. 

* Memory leaks can occur if you forget to free even 1 byte
* It takes time to locate and allocate a block of memory
* It makes it harder to guarantee the total memory requirement does not exceed the system memory during any point of execution.
* Memory can become fragmented
* Do not assume `malloc/free` (C) or `new/delete` (C++) are re-entrant.

> For these reasons, preallocating memory is recommended for embedded systems. It helps us guarantee that the system will not run out of memory if left to run for long periods of time.

The disadvantages of memory pools are:

* You preallocate memory even if you never use it all
* Each block must be the same size. Dynamic memory allocation allows you to allocate blocks of an arbitrary size.

### Challenge
Change the interrupt from a timer to a switch press. If **either** switch A or B are pressed and then released, the `switchISR` function should be invoked.

* Use the same ISR for both switches
* Add a watch-dog to reset the board if nothing is pressed within 30s.

## Mailbox
As you probably appreciate, the queue and memory pool are designed to work together, so much so that the `Mailbox` class uses composition to combine them together.

<figure>
<img src="../img/mail-queue.png" width="600px">
<figcaption>Mailbox - encapsulating both a message queue and memory pool</figcaption>
</figure>


| TASK-384 | Mailbox |
| --- | --- |
| 1. | Make Task-384 your active program. |
| -  | Study the code. Build and run, while watching the serial monitor |

This code is quite similar to the previous examples. Instead of creating a queue and memory pool, you now only need one object:

```C++
Mail<message_t, 16> mail_box;
```

Acquiring memory is also similar:

```C++
message_t* message = mail_box.try_alloc();
```

What is slightly different is the `put` function:

```C++
osStatus stat = mail_box.put(message);
```

> **Note:** At the time of writing, this returns a value of type `osStatus`. If `message` is not `NULL`, then given the queue is the same size as the mailbox, there must be room so this should always succeed. The return type is somewhat redundant and is expected to be deprecated (see comments in `Mail.h`)

In the consumer thread, we again use a blocking call with a timeout:

```C++
message_t* payload;

//Block on the queue
payload = mail_box.try_get_for(10s);
```

> Note that non-blocking variants exist

## What about interrupts?
In the examples above, data has been copied from an interrupt context to a thread. Other options to consider:

* Interrupt to thread - a very useful way to cross from the ISR context to the thread context.
* Thread to thread - useful for passing data between threads as the synchronisation and buffering is built in
* Thread to interrupt - this requires use of the non-blocking APIs for get.  
* Interrupt to interrupt - both ends use non-blocking APIs (although I've not tried this!)

So yes, these can be used with interrupts for both put and get, but you need to ensure that interrupts should never be blocked.

## Event Queues
I confess this is my personal favourite and they deserve some exploration.

One of the most interesting objects in Mbed os is the EventQueue. This is something that will feel familiar to developers on mobile and desktop computing platforms. In essence, for a given thread, it is possible to have a queue of jobs that will be performed **sequentially** (one after the other). Furthermore, tasks can be posted to a queue from any context (another thread or ISR). 

> A task in this context is “calling a function, with optional parameters”.

<figure>
<img src="../img/event-queue.png" width="600px">
<figcaption>Event Queue Concept: </figcaption>
</figure>

The event queue will "dispatch" each task in a defined sequence on the thread in which it is running.

Tasks can be set to run in the following ways:

* Periodically
* After a delay (which can be zero)

A key point is that all queued tasks (in given queue, running in a dedicated thread) will run atomically and in  sequence with respect to each other. In other words, non of the tasks in an event queue can pre-empt each other.

Of course, they can pre-empt tasks on other threads.

Some uses cases for this are:

* An interrupt can easily defer non-real-time tasks to a background thread (allowing it to exit more quickly)
* Queuing up non re-entrant functions - thus helping to avoid
race conditions
* Queues can also be chained together, and allow the developer to synchronise operations to avoid races and maximise throughput.

Remember that you can do much more in a thread than you can in an ISR. Nearly every object in Mbed os is protected and thread safe whereas only a minority are interrupt safe. The same applies to the standard library (`printf`, `scanf` etc.).

| TASK-386 | Event Queues |
| --- | --- |
| 1. | Make Task 386 your active program. Build and run it |
| 2. | Monitor the serial terminal. Every time the red LED lights, press and release the blue user button |
| -  | Note the number of switch bounces! |

This task is not about switch-bounce per-se, but about how you can use event queues to simplify your code.

This application has two threads:

* main
* `t1`

For each thread, an instance of `EventQueue` has been created for illustrative purposes.

```C++
EventQueue mainQueue;
EventQueue workerQueue;
```

Early in the code, the function `workerThread` is run in a parallel thread.

```C++
t1.start(workerThread);
...
void workerThread()
{
    workerQueue.dispatch_forever();
}
...
```

This function has only one task: to run `workerQueue.dispatch_forever()`

From the documentation, it says "Dispatch events without a timeout." So what does this mean?

> Dispatch queues initially block and wait for tasks to be sent to them.
>
> As tasks are received, these are held in a queue and dispatched in turn. Tasks are essentially functions and their parameters. These tasks are run in sequential order, and not concurrently. 
>
> From an ISR or another thread, you can add a task to the queue.
>
> There there are no tasks to perform, they block in the `WAITING` state. 

We can see a number of examples in this application:

```C++
workerQueue.call_in(3s, printf, "(Note the switch bounce)\n");
```

This requests that the queue `workerQueue` (on thread `t1`) dispatches the function `printf("(Note the switch bounce)\n")` in 3 seconds time.

```C++
mainQueue.call_every(2s, heartBeat);
```

This requests that the queue (on the main thread) dispatches the function `heartBeat()` every 2 seconds

```C++
workerQueue.call(addSample, t);
```

Called from the switch ISR, this requests that the function `addSample(t)` is dispatched at the next opportunity(on thread `t1`). 

* `addSample` is non-reentrant and not thread safe as it uses static local variables. It does not contain any mutex locks either.
    * However, is it is always called on the same event queue, there is no danger of it pre-empting itself, so this is permitted
* Similarly, all the `printf` operations are performed on the same thread `t1` via it's event queue.
    * Although this does contain locks, this is still  useful as it ensures that each `printf` is allowed to fully complete before the next, thus avoiding their output being interleaved.

| TASK-386 | Event Queues |
| --- | --- |
| 3. | Can you modify the `hearBeat()` function to call `printf("Main Thread Alive\n")` by posting this to the workerQueue on thread `t1` |
| - | For your reference, the current `heartBeat` function is as follows |

```C++
void heartBeat() {
    redLED = !redLED;
}
```

## Reflection
Event queues are incredibly useful and can really simplify your code.

A critical points are:

* Each event queue runs in it's own thread
* All functions dispatched by an event queue are allowed to complete and are atomic with respect to each other

A useful use-case it to separate different tasks to run on different event queues.

* If all functions sharing some mutable data can be run on the same event queue, then races can be avoided
* Functions that are non-re-entrant do not need locks if only run on the same event queue

---

[Back to Contents](README.md)
