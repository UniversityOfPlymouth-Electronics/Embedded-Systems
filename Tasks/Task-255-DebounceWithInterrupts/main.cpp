#include "uop_msb.h"
#include <chrono>
using namespace uop_msb;

InterruptIn buttonA(BTN1_PIN);    //ButtonA is synonamous with buttons[0]
InterruptIn buttonB(BTN2_PIN);
Timeout buttonA_Timer;
Timeout buttonB_Timer;

DigitalOut redLED(TRAF_RED1_PIN);       //Red Traffic 1
DigitalOut yellowLED(TRAF_YEL1_PIN);    //Yellow Traffic 1
DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

//Function declarations
void buttonA_Rise();
void buttonA_WaitForNoise1();
void buttonA_Fall();
void buttonA_WaitForNoise2();


//Interrupt Service Routines

//Timer ISR
void flashy() {
    led1 = !led1;
}

// ****************************
// State machine for button A *
// ****************************

// State A
void buttonA_Rise() {
    buttonA.rise(nullptr); //Turn off ISR
    redLED = !redLED;
    buttonA_Timer.attach(buttonA_WaitForNoise1, 50ms); //Set up timer interrupt
}
// State B
void buttonA_WaitForNoise1() {
    buttonA_Timer.detach();
    buttonA.fall(buttonA_Fall);
}
// State C
void buttonA_Fall() {
    buttonA.fall(nullptr);
    buttonA_Timer.attach(buttonA_WaitForNoise2, 50ms); //Set up timer interrupt  
}
// State D
void buttonA_WaitForNoise2() {
    buttonA_Timer.detach();
    buttonA.rise(buttonA_Rise);
}

//Serial comms
static UnbufferedSerial serial_port(USBTX, USBRX,9600);
char dot = '.';

int main()
{
    //Timer interrupt
    Ticker flash;
    flash.attach(flashy, 5000ms);

    //Switch A Interrupt-based FSM
    buttonA.rise(buttonA_Rise);

    while (true)
    {
        sleep();

        //Echo a dot each time one or more interrupts occur
        serial_port.write(&dot,1);
    }
}
