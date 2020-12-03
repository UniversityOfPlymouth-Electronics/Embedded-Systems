[Back to Contents](README.md)

---

# Thread Abstractions
I could not think of the right title for this section, so I've gone with _thread abstractions_. Multi-threaded programming is in itself an abstraction. The presence of a scheduler and small operating system abstracts you from both the hardware specifics and the job of task switching.

> As problems scale, if you write code at a bare-metal level, you may find yourself replicating the facilities that an RTOS provides.

Writing good quality multi-threaded code is a non-trivial of course. Some of it can be somewhat repetitive. There are some common tasks which again, you do really want to reinvent, write and debug. Thankfully, some of these common tasks have been anticipated, and solutions provided for you. So in this sense, we are given another layer of abstraction. These tools are what this section is about, and include:

* FIFO Queues for safely moving data from an interrupt/thread to another thread
* Memory pools for safe memory allocation and deallocation
    * Mailboxes which combine the above
* EventQueues for safely scheduling "tasks" on other threads to run once or periodically.


