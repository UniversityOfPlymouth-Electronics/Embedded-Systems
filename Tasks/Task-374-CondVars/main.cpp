#include "uop_msb.h"
#include <chrono>
using namespace uop_msb;

// Example derived from the documentation (and modified)

Mutex mutex;
ConditionVariable cond(mutex);

// Both these variables are protected by the locking mutex
uint32_t counter = 0;
bool done = false;

void worker_thread1()
{
    //Take the lock on the first occasion
    mutex.lock();

    do {
        printf("Worker 1: Count %u\r\n", counter);

        // Release the lock and wait for a notification
        cond.wait();

        //Once unblocked, **the lock is re-acquired automatically**

    } while (!done);

    printf("Worker1: Exiting\r\n");

    // Remember we still have the lock!
    // This is very important (and easy to forget!)
    mutex.unlock();
}

//Same as workder_thread1
void worker_thread2()
{
    mutex.lock();
    do {
        printf("Worker 2: Count %u\r\n", counter);
        cond.wait();
    } while (!done);
    printf("Worker2: Exiting\r\n");
    mutex.unlock();
}

int main()
{
    Thread t1;
    Thread t2;
    t1.start(worker_thread1);
    t2.start(worker_thread2);

    for (int i = 0; i < 5; i++) {

        mutex.lock();

        // Enter the critical section and modify the protected resource(s)
        counter++;
        printf("Main: Set count to %u\r\n", counter);

        //Notify waiting threads that some change has occured
        cond.notify_all();

        //Release the lock (and exit the critical section)
        mutex.unlock();

        ThisThread::sleep_for(1s);
    }


    //Same pattern as above - only this time for the `done` variable
    mutex.lock();
    // Change done and notify
    done = true;
    printf("Main: Set done\r\n");
    cond.notify_all();
    mutex.unlock();

    //Wait for the thread to exit
    t1.join();
    t2.join();

    //Flash happily :)
    DigitalOut led(LED1);
    while (true) {
        led = !led;
        ThisThread::sleep_for(500ms);
    }
}