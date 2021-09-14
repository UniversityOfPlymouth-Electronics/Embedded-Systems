// Send SOS in Morse code
// ----------------------
// DOT 150 ms
// DASH 450 ms
//
// Symbol Space 1 DOT  150 ms
// Letter Space 3 DOTS 450 ms
// Word   Space 6 DOTS 600 ms
//
// Each symbol is followed by 150ms OFF time
// Each letter is followed by a further 300 ms OFF time
// Each word is follwed by a further 450 ms OFF time
//
// University of Plymouth 
// Chris Tipney September 2020 V1.0

// You need this to use the Module Support Board
#include "uop_msb.h"
using namespace uop_msb;
 
DigitalOut greenLED(TRAF_GRN1_PIN);
Buzzer buzz;
Buttons buttons;

//Function prototypes
void dot();
void dash();
void letterSpace();
void wordSpace();
void sierra();
void oscar();

int main()
{
    //Wait for the BLUE button to be pressed (otherwise this becomes super annoying!)
    while (buttons.BlueButton == 0);
    
    //Repeat everything "forever" (until the power is removed or the chip is reset)
    while (true)
    {
        sierra();       // Send 'S'
        oscar();        // Send 'O'
        sierra();       // Send 'S'
        wordSpace();    // Send space after word
    }
}

// Send one dot symbol 
// ON  150 ms
// OFF 150 ms
void dot()
{
        // ON
        greenLED = 1;           // LED ON
        buzz.playTone("C");     // Play tone
        wait_us(150000);        // Wait 150ms

        // OFF
        greenLED = 0;           // LED OFF
        buzz.rest();            // Stop tone
        wait_us(150000);        // Wait 150ms
}

// Send one dash symbol
// ON  450 ms
// OFF 150 ms
void dash()
{
        // ON
        greenLED = 1;           // LED ON
        buzz.playTone("C");     // Play tone
        wait_us(450000);        // Wait 450ms

        // OFF
        greenLED = 0;           // LED OFF
        buzz.rest();            // Stop tone 
        wait_us(150000);        // Wait 150ms
}

// Send letterspace 450 ms minus the 150 ms from the last symbol = 300 ms
void letterSpace()
{
    wait_us(300000); // 300 ms
}

// Send wordspace 900 ms - the 150 ms from last symbol = 750 ms
void wordSpace()
{
    wait_us(750000); // 750 ms
}

// Send the latter 'S' dot dot dot followed by the wordspace
void sierra()
{
    dot();
    dot();
    dot();
    letterSpace();
}

// Send the letter 'O' dash dash dash followed by the wordspace
void oscar()
{
    dash();
    dash();
    dash();
    letterSpace();
}

