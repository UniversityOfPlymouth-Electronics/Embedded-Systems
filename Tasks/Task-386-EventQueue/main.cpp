#include "uop_msb.h"
#include <chrono>
#include <iterator>
using namespace uop_msb;

#include "mbed_events.h"

DigitalOut onBoardLED(LED1);
DigitalOut redLED(TRAF_RED1_PIN);
DigitalOut yellowLED(TRAF_YEL1_PIN);
DigitalOut greenLED(TRAF_GRN1_PIN);

void buttonPressedISR();
void addSample(long long dur);
void heartBeat();
void workerThread();
 
InterruptIn btn(USER_BUTTON);

//Creates a queue with the default size
EventQueue mainQueue;
EventQueue workerQueue;

Timer tmr1;
Thread t1;

//Buffer
float arrayOfTimes[10];

int main() {
    
    //Start worker queue
    t1.start(workerThread);

    //Dispatch deferred one-off tasks to the queue in the worker thread
    workerQueue.call_in(3s, printf, "(Note the switch bounce)\n");
    workerQueue.call_in(1s, printf, "Press the BLUE button to as the RED lights up\n");
    workerQueue.call_in(20s, printf, "Noisy isn't it!\n");

    //Set up ISR for button
    btn.rise(buttonPressedISR);
    
    //Start timer
    tmr1.start();
    
    //Repeated dispatch - Background flash (backed by a Ticker) using queue on main thread
    mainQueue.call_every(2s, heartBeat);
    
    //Set up queue on main thread as well
    mainQueue.dispatch_forever();

    //Unreachable code
    printf("This should never appear!\n");
}

// A parallel thread used for displaying text on the serial terminal
void workerThread()
{
    workerQueue.dispatch_forever();
}

void buttonPressedISR() { 
    //Measure the time
    long long t = duration_cast<milliseconds>(tmr1.elapsed_time()).count();  //Immediately read time in seconds

    //Dispatch addSample to run on the worker thread, passing the time as a parameter
    workerQueue.call(addSample, t);  
}

// Add sample to buffer
// Single parameter t, copy of latest switch time
void addSample(long long dur) {
    static float prev_t = 0.0; 
    static uint16_t bounce_count = 0;

    float t = 0.001f*dur;
    printf("t=%.6fs", t);
    if ((t - prev_t) < 0.25) {
        bounce_count++;
        printf("\t%u\n", bounce_count);
    } else {
        printf("\n");
        bounce_count = 0;
    }
    prev_t = t;
}

//Flashing LED 
void heartBeat() {
    redLED = !redLED;
}