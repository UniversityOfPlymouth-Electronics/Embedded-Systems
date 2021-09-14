#include "mbed.h"
#include "uop_msb.h"
using namespace uop_msb;

void countUp();
void countDown();

#define N 5000000
#define RELEASED 0
#define PRESSED  1

//Hardware
DigitalOut red_led(TRAF_RED1_PIN);     //CountUp is in its critical section
DigitalOut yellow_led(TRAF_YEL1_PIN);  //CountDown is in its critical section
DigitalOut green_led(TRAF_GRN1_PIN);   //counter != 0
DigitalOut backLight(LCD_BKL_PIN,0);
DigitalIn button(USER_BUTTON);
AnalogIn pot(AN_POT_PIN);
LCD_16X2_DISPLAY disp;

//Additional Threads
Thread t1;
Thread t2;

//Shared mutable state
volatile long long counter = 0; //Volatile means it must be stored in memory
//Associated MUTEX
Mutex counterLock;


//Increment the shared variable 
void countUp()
{
    //RED MEANS THE COUNT UP FUNCTION IS IN ITS CRITICAL SECTION
    green_led = 1;
    for (unsigned int n=0; n<N; n++) {
        counterLock.lock();
        counter++; 
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;
        counter++;
        counter++; 
        counterLock.unlock();          
    }  
    green_led = 0; 
    
}

//Decrement the shared variable
void countDown()
{
    //YELLOW MEANS THE COUNT DOWN FUNCTION IS IN ITS CRITICAL SECTION
    yellow_led = 1;
    for (unsigned int n=0; n<N; n++) {
        counterLock.lock();
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;
        counter--;   
        counterLock.unlock();        
    }
    yellow_led = 0;
    
}


int main() {
    disp.cls();
    uint16_t skew = pot.read_u16() >> 12;
    red_led = 1;
    
    //Start competing threads
    
    if (button == 0) {
        t1.start(countUp);
        t1.join();  //Wait for t1 to complete
        t2.start(countDown);
        t2.join();  //Wait for t2 to complete
    } else {
        backLight = 1;
        disp.printf("Skew: %uuS\n", skew);   
        t1.start(countUp);
        wait_us(skew);
        t2.start(countDown);
        t1.join();  //Wait for t1 to complete
        t2.join();  //Wait for t2 to complete
    }
    
    //Did the counter end up at zero?
    backLight = 1;
    disp.locate(1, 0);

    counterLock.lock(); //Pedantic, but setting an example :)
    disp.printf("Counter=%Ld\n", counter);

    if (counter == 0) {
        red_led = 0;   
    }
    counterLock.unlock();   

    //Now wait forever
    while (true) {
        ThisThread::sleep_for(Kernel::wait_for_u32_forever);
    }
    
}

