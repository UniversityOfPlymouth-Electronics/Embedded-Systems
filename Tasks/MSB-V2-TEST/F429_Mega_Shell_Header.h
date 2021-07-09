#ifndef F429_MEGA_SHELL_HEADER_H
#define F429_MEGA_SHELL_HEADER_H

#include "mbed.h"

#include "BMP280_SPI.h"
#include "TextLCD.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_MS     500ms
//IDE Constants
#define DELAY 2000ms
#define RED   1
#define AMBER 2
#define GREEN 4

#define rgb 0   //no Latch
#define Rgb 1   //Red Latch
#define rGb 2   //Green Latch
#define rgB 4   //Blue Latch

#define SCAN_RATE_MS   50

// 7 Segment labels A to G and Decimal Point (DP)
#define A  0x10
#define B  0x20
#define C  0x40
#define D  0x08
#define E  0x02
#define F  0x01
#define G  0x04
#define DP 0x80

#define WAIT_TIME_MS 1000

#define SAMPLES 300

//API Class type instance

// LCD
extern TextLCD myLCD;   // rs, e, rw,  then data lines =  d4,d5,d6,d7
extern PwmOut myLCD_BL;

// SOUNDER
extern PwmOut buzzer;

// TRAFFIC LIGHTS (NON LATCHED LEDS)
extern BusOut Traffic_Lights_1;                         //BusOut here can be DigitalOut
extern BusInOut Traffic_Lights_2;                       //NB this is BusInOut for open drain  you will need to add the following lines
                                                        // Traffic_Lights_2.output();
                                                        // Traffic_Lights_2.mode(OpenDrainNoPull);
                                                        // Traffic_Lights_2=assign a value remember that 1==OFF and 0==ON
                                                        //however..
                                                        //can use DigitalInOut see 'Pedestrian' for example
extern DigitalInOut Pedestrian;                         //Set as output, open drain, and set high to switch LED off initially 1==OFF 0==ON

// NUCLEO BOARD LEDS
extern DigitalOut led1;
extern DigitalOut led2;
extern DigitalOut led3;

// RGB Bar LED LATCHED by used of RGBcol, number of LEDS selected by RGBled, output enable active LOW
extern BusOut RGBled;
extern BusOut RGBcol;
extern DigitalOut RGBoe;

// SWITCHES A B C D.  NB C and D are configured for open drain inputs need a pull down as when switch is not pressed then has a floating input
extern DigitalIn swA;
extern DigitalIn swB;
extern DigitalInOut swC;
extern DigitalInOut swD;

//Analogue Inputs
extern AnalogIn pot_an_input;
extern AnalogIn microphone;
extern AnalogIn signal_in;
extern AnalogIn ldr;
extern AnalogIn audio_in_L;
extern AnalogIn audio_in_R;

//Analogue Outputs
extern AnalogOut dac_out_1;
extern AnalogOut dac_out_2;

// MATRIX DISPLAY SPI WITH OUTPUT ENABLE
extern SPI spi;   // MOSI, MISO, SCLK
extern DigitalOut cs;            //Chip Select ACTIVE LOW
extern DigitalOut oe;           //Output Enable ACTIVE LOW

// 7 SEGMENT DISPLAY LATCHED AND OUTPUT ENABLED
extern BusOut seg7;
extern DigitalOut LatE1;
extern DigitalOut LatE2;
extern DigitalOut nOE;

// Environmetal sensor
extern BMP280_SPI bmp280;

// SD Card 
// Instantiate the SDBlockDevice by specifying the SPI pins connected to the SDCard
// socket. The PINS are: (This can also be done in the JSON file see mbed.org Docs API Storage SDBlockDevice)
// PB_5    MOSI (Master Out Slave In)
// PB_4    MISO (Master In Slave Out)
// PB_3    SCLK (Serial Clock)
// PF_3    CS (Chip Select)
//
// and there is a Card Detect CD on PF_4 ! (NB this is an Interrupt capable pin..)
extern SDBlockDevice sd;

#endif