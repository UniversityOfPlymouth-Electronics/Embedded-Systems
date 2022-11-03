// You need this to use the Module Support Board
#include "uop_msb.h"
using namespace uop_msb;

#define WAIT_TIME_MS 500 
DigitalOut greenLED(TRAF_GRN1_PIN);
Buzzer buzz;
Buttons buttons;

// TIP: (I suggest you read this!)
//
// Press the black reset button to restart the code (and stop the sound)
// Otherwise, the noise can be "distracting" :)

int main()
{
    //Wait for the BLUE button to be pressed (otherwise this becomes super annoying!)
    while (buttons.BlueButton == 0);
    
    //Repeat everything "forever" (until the power is removed or the chip is reset)
    while (true)
    {
        //On for 500ms
        greenLED = 1;
        buzz.playTone("A");
        wait_us(WAIT_TIME_MS * 1500);  //500ms


        //Off for 500ms
        greenLED = 0;
        buzz.playTone("C");
        wait_us(WAIT_TIME_MS * 1500);  //500ms

        greenLED = 1;
        buzz.playTone("D");
        wait_us(WAIT_TIME_MS * 2000);  //500ms

        
        buzz.playTone("A");
        wait_us(WAIT_TIME_MS * 1500);  //500ms
        
        buzz.playTone("C");
        wait_us(WAIT_TIME_MS * 1500);  //500ms
        
        buzz.playTone("D#");
        wait_us(WAIT_TIME_MS * 750);  //250ms
        greenLED = 1;
        buzz.playTone("D");
        wait_us(WAIT_TIME_MS * 1500);  //500ms
        buzz.playTone("A");
        wait_us(WAIT_TIME_MS * 1500);  //500ms


        //Off for 500ms
        greenLED = 0;
        buzz.playTone("C");
        wait_us(WAIT_TIME_MS * 1500);  //500ms

        greenLED = 1;
        buzz.playTone("D");
        wait_us(WAIT_TIME_MS * 1500);  //500ms
        
        buzz.playTone("C");
        wait_us(WAIT_TIME_MS * 1500);  //500ms
        buzz.playTone("A");
        wait_us(WAIT_TIME_MS * 2000);  //500ms

        //Pause
        buzz.rest();
        wait_us(WAIT_TIME_MS * 1000);

    }
}
//D D (Oct. Higher) D A G# G F D F G C C (Oct. Higher) D A G# G F D F G B B (Oct. Higher) D A G# G F D F G A# A# (Oct. Higher) D A G# G F D F G F F F F D D D F F F G G# G F D F G F F F G G# A C A D D D A D C A A A A G G G A A A A G A C A G D A G F C G F E D D D D F C F D F G G# G F