#include "F429_Mega_Shell_Header.h"

TextLCD myLCD(PD_11, PD_13, PD_12, PD_4,PD_5,PD_6,PD_7);   // rs, e, rw,  then data lines =  d4,d5,d6,d7
PwmOut myLCD_BL(PD_14);

// SOUNDER
PwmOut buzzer(PB_13);

// TRAFFIC LIGHTS (NON LATCHED LEDS)
BusOut Traffic_Lights_1(PC_2,PC_3,PC_6);                //BusOut here can be DigitalOut
BusInOut Traffic_Lights_2(PC_7,PC_8,PC_9);              //NB this is BusInOut for open drain  you will need to add the following lines
                                                        // Traffic_Lights_2.output();
                                                        // Traffic_Lights_2.mode(OpenDrainNoPull);
                                                        // Traffic_Lights_2=assign a value remember that 1==OFF and 0==ON
                                                        //however..
                                                        //can use DigitalInOut see 'Pedestrian' for example
DigitalInOut Pedestrian(PF_10,PIN_OUTPUT,OpenDrain,1);  //Set as output, open drain, and set high to switch LED off initially 1==OFF 0==ON

// NUCLEO BOARD LEDS
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

// RGB Bar LED LATCHED by used of RGBcol, number of LEDS selected by RGBled, output enable active LOW
BusOut RGBled(PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9);
BusOut RGBcol(PE_12, PE_13, PE_14);
DigitalOut RGBoe(PE_0,1);

// SWITCHES A B C D.  NB C and D are configured for open drain inputs need a pull down as when switch is not pressed then has a floating input
DigitalIn swA(PG_0);
DigitalIn swB(PG_1);
DigitalInOut swC(PG_2,PIN_INPUT,OpenDrainPullDown,0);
DigitalInOut swD(PG_3,PIN_INPUT,OpenDrainPullDown,0);

//Analogue Inputs
AnalogIn pot_an_input(PA_0);
AnalogIn microphone(PA_3);
AnalogIn signal_in(PA_6);
AnalogIn ldr(PC_0);
AnalogIn audio_in_L(PB_0);
AnalogIn audio_in_R(PB_1);

//Analogue Outputs
AnalogOut dac_out_1(PA_4);
AnalogOut dac_out_2(PA_5);

// MATRIX DISPLAY SPI WITH OUTPUT ENABLE
SPI spi(PC_12, PC_11, PC_10);   // MOSI, MISO, SCLK
DigitalOut cs(PB_6);            //Chip Select ACTIVE LOW
DigitalOut oe(PB_12);           //Output Enable ACTIVE LOW

BusOut seg7(PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9);
DigitalOut LatE1(PE_10,0);
DigitalOut LatE2(PE_11,0);
DigitalOut nOE(PE_15,0);

BMP280_SPI bmp280(PB_5, PB_4, PB_3, PB_2);

SDBlockDevice sd(PB_5, PB_4, PB_3, PF_3);
