/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "F429_Mega_Shell_Header.h"
#include "TextLCD/TextLCD.h"
#include <cstdio>

//prototypes
void Traffic_Lights();
void LCD_BackLight_Effect();
void Bar_Flash();
void clearMatrix();
void matrix_scan();
int seg7num(int);
void seg7clear();
void count_thread();
float potav();
void environment_data();
int write_sdcard();
int read_sdcard();

Thread t1;
Thread t2;
Thread t3;
Thread t4;
Thread t5;
Thread t6;

Timer stopwatch;

int main()
{

    printf("\n\nstarting...\n");
    //write_sdcard();

  //  read_sdcard();

//printf("read second time\n");
        //read_sdcard();
    
    seg7clear();

    Traffic_Lights_2.output();
    Traffic_Lights_2.mode(OpenDrainNoPull);
    Traffic_Lights_2=1;

    Pedestrian.output();
    Pedestrian.mode(OpenDrainNoPull);

    Pedestrian=0;
    ThisThread::sleep_for(DELAY);//    wait_us(1000000);
    Pedestrian=1;

    // 7 segment display setup
    spi.format(8,0);            // 8bits, Rising edge, +VE Logic Data
    spi.frequency(1000000);     //1MHz Data Rate
    oe=0;                       //Enable Output NB can be more selective than this if you wish
    
    char switchNum=' ';
    printf("Starting Program..\n");
    t1.start(Traffic_Lights);
    t2.start(LCD_BackLight_Effect);
    t3.start(Bar_Flash);
    t4.start(matrix_scan);
    t5.start(count_thread);
    t6.start(environment_data);

    myLCD.cls();
    myLCD.printf("SECaM PU");
    myLCD.locate(0,1);myLCD.printf("Switch=");
    buzzer.period_us(2273);
    //buzzer=0.5f;wait_us(200000);buzzer=0;

    while(true){
        if (swA)switchNum='A';
        if (swB)switchNum='B';
        if (swC)switchNum='C';
        if (swD)switchNum='D';
        switch(switchNum){
            case 'A': buzzer.period_us(350);buzzer=0.5f;break;//spk.period_us(2273);
            case 'B': buzzer.period_us(360);buzzer=0.5f;break;//spk.period_us(2024);
            case 'C': buzzer.period_us(370);buzzer=0.5f;break;//spk.period_us(1912);
            case 'D': buzzer.period_us(380);buzzer=0.5f;break;//spk.period_us(1704);
            default:switchNum=' ';buzzer=0;break;
        }
        //Voltage = 3.3f * Pot_AN_INPUT.read();
        myLCD.locate(7, 1);myLCD.printf("%c",switchNum);
        myLCD.locate(10,1);myLCD.printf("%4.2fV",potav());
        //spk=0;
        switchNum=0;
        wait_us(200000);
    }
}


float potav(){
    unsigned int adc_sample[SAMPLES+1];
    float Voltage;
    adc_sample[0]=0;
    for(int i=1; i<=SAMPLES; i++){
        adc_sample[i] = pot_an_input.read_u16();
        adc_sample[0]+=adc_sample[i];
    }
    Voltage = 3.3f * ((float)adc_sample[0]/(float)SAMPLES)/65535.0f;
    return Voltage;
}

void LCD_BackLight_Effect(){
    for(float i=0; i<1.0f; i+=0.01){
        myLCD_BL=i;
        ThisThread::sleep_for(20ms);
    }
    myLCD_BL=1.0f;
}

void Traffic_Lights(){
    while (true)
    {

        Pedestrian=0;

        Traffic_Lights_1 = RED;
        Traffic_Lights_2 = 3;//7-GREEN;
        ThisThread::sleep_for(DELAY);

        Pedestrian = 1;
        Traffic_Lights_1 = RED + AMBER;
        Traffic_Lights_2 = 5;//7-AMBER;
        ThisThread::sleep_for(DELAY);
        Traffic_Lights_1 = GREEN;
        Traffic_Lights_2 = 6;
        ThisThread::sleep_for(DELAY);
        Traffic_Lights_1 = AMBER;
        Traffic_Lights_2 = 4;
        ThisThread::sleep_for(DELAY);
    }
}

void Bar_Flash()
{

//RGBled is the value of the Leds NB SHared Bus for Red Green and Blue
//RGBcol will select the Capitalised Colour NB rgb lower case is all off
// So Value then Latch and then latch off in that order
    while(true){
        RGBoe = 0; //Enable Output

        //RED
        RGBled = 255; RGBcol = Rgb; RGBcol = rgb; //NB see above i.e. LED value then latch High and Latch Low and repeat for below
        ThisThread::sleep_for(DELAY/4);
        RGBled = 0; RGBcol = Rgb; RGBcol = rgb; 

        //GREEN
        RGBled = 255; RGBcol = rGb; RGBcol = rgb; 
        ThisThread::sleep_for(DELAY/4);
        RGBled = 0; RGBcol = rGb; RGBcol = rgb; 

        //BLUE
        RGBled = 255; RGBcol = rgB; RGBcol = rgb; 
        ThisThread::sleep_for(DELAY/4);
        RGBled = 0; RGBcol = rgB; RGBcol = rgb; 

        // Put all LEDs on
        RGBled = 255; RGBcol = Rgb; RGBcol = rgb; 
        RGBled = 255; RGBcol = rGb; RGBcol = rgb; 
        RGBled = 255; RGBcol = rgB; RGBcol = rgb; 
        //Use Output Enable line to flash LED bar    
        for(int i=0; i<20;i++){
            RGBoe = !RGBoe;
            ThisThread::sleep_for(100ms);
        }
        // Reset Red Green and Blue to Zero and latch
        RGBled = 0; RGBcol = Rgb; RGBcol = rgb; 
        RGBled = 0; RGBcol = rGb; RGBcol = rgb; 
        RGBled = 0; RGBcol = rgB; RGBcol = rgb; 

        RGBoe = 1;//Disable Output
    }

}


void matrix_scan(void)
{
    while(true)
    {
        for (int j=0;j<=7;j++)  //NB ROW has 3 to 8 decoder so 0 to 7 to Row Select
                                //COLUMNS(COL) are 0 to 255 to select each Byte
        {
            for (int i=1;i<255;i*=2) //Increment LEFT Hand Block of 8
            {
                cs=0;           //Send Data to Matrix
                spi.write(0x00);//COL RHS
                spi.write(i);   //COL LHS
                spi.write(j);   //ROW RHS
                cs=1;           //low to high will effectivelly LATCH the Shift register to output
                thread_sleep_for(SCAN_RATE_MS);
            }
            for (int i=1;i<255;i*=2) //Increment RIGHT Hand Block of 8
            {
                cs=0;           //Send Data to Matrix
                spi.write(i);   //COL RHS
                spi.write(0x00);//COL LHS
                spi.write(j);   //ROW RHS
                cs=1;           //low to high will effectivelly LATCH the Shift register to output
                thread_sleep_for(SCAN_RATE_MS);
            }
        }
    for (int j=0;j<=7;j++)  //NB ROW has 3 to 8 decoder so 0 to 7 to Row Select
                                //COLUMNS(COL) are 0 to 255 to select each Byte
        {
            {
                cs=0;           //Send Data to Matrix
                spi.write(0xFF);//COL RHS
                spi.write(0xFF);   //COL LHS
                spi.write(j);   //ROW RHS
                cs=1;           //low to high will effectivelly LATCH the Shift register to output
                thread_sleep_for(SCAN_RATE_MS);
            }
        }
     for (int j=7;j>=0;j--)  //NB ROW has 3 to 8 decoder so 0 to 7 to Row Select
                                //COLUMNS(COL) are 0 to 255 to select each Byte
        {
            {
                cs=0;           //Send Data to Matrix
                spi.write(0xFF);//COL RHS
                spi.write(0xFF);   //COL LHS
                spi.write(j);   //ROW RHS
                cs=1;           //low to high will effectivelly LATCH the Shift register to output
                thread_sleep_for(SCAN_RATE_MS);
            }
        }

    }
}


void clearMatrix(void)
{
    cs=0;           //CLEAR Matrix
    spi.write(0x00);//COL RHS
    spi.write(0x00);//COL LHS
    spi.write(0x00);//ROX RHS
    cs=1;
}

void count_thread(){
    seg7clear();
    unsigned char counter=0;
    while(true){
        seg7num(counter);
        counter++;
        if (counter>99){counter=0;}
        thread_sleep_for(250);
    }
}


int seg7num(int num){
    int temp,count=0;

    if (num<0||num>99){return -1;} // Out of Range check

    while(count<2){
        if (count==0){temp=(num/10)%10;} // Tens
        if (count==1){temp=num%10;}      // Units
        switch(temp){
            case 0: seg7=A+B+C+D+E+F;break;
            case 1: seg7=B+C;break;
            case 2: seg7=A+B+D+E+G;break;
            case 3: seg7=A+B+C+D+G;break;
            case 4: seg7=B+C+F+G;break;
            case 5: seg7=A+C+D+F+G;break;
            case 6: seg7=C+D+E+F+G;break;
            case 7: seg7=A+B+C;break;
            case 8: seg7=A+B+C+D+E+F+G;break;
            case 9: seg7=A+B+C+D+F+G;break;
            default: seg7=0;break;
        }
        if (count==0){LatE1=1;LatE1=0;} //Latch Tens Digit
        if (count==1){LatE2=1;LatE2=0;} //Latch Units Digit
        count++;
    }
    return 0; // Return Completed OK
}


void seg7clear(void){
    seg7=0;
    LatE1=1;LatE1=0;
    LatE2=1;LatE2=0;
}
 
void environment_data(void)
{   int err=0;
    float temperature,pressure;
    
    err = sensor.initialize();
    DEBUG_PRINT("ERROR CODE IS %d\n",err);
    switch (err){
        case 280: sensor.~SPL06_001_SPI(); bmp280.initialize();printf("BMP280 found\n");break;      //BMP280 found so Destruct SPL06 driver and initialize BMP280 !!
        case   6: bmp280.~BMP280_SPI();sensor.initialize();printf("SPL06_001 found\n");break;                           //SPL06_001 found so Destruct BMP280
        case  -1: printf("No Environmental Sensor found!\n");break;            //None found
        default : break;                                 
    }

    while(true)
    {
        switch (err)
        {
            case 280:temperature=bmp280.getTemperature();pressure=bmp280.getPressure();break;
            case 6:temperature=sensor.getTemperature();pressure=sensor.getPressure();break;
            case -1:break;
            default:break;
        }

        printf("Temperature = %4.1f ",temperature);
        printf("Pressure = %4.1f\n",pressure);
        thread_sleep_for(WAIT_TIME_MS);
    }
}

int write_sdcard()
{
    printf("Initialise and write to a file\n");
 int err;
    // call the SDBlockDevice instance initialisation method.

    err=sd.init();
    if ( 0 != err) {
        printf("Init failed %d\n",err);
        return -1;
    }
    
    FATFileSystem fs("sd", &sd);
    FILE *fp = fopen("/sd/test.txt","w");
    if(fp == NULL) {
        error("Could not open file for write\n");
        sd.deinit();
        return -1;
    } else {
        //Put some text in the file...
        fprintf(fp, "Martin Says Hi!\n");
        //Tidy up here
        fclose(fp);
        printf("SD Write done...\n");
        sd.deinit();
        return 0;
    }
    
}

int read_sdcard()
{
    printf("Initialise and read from a file\n");

    // call the SDBlockDevice instance initialisation method.
    if ( 0 != sd.init()) {
        printf("Init failed \n");
        return -1;
    }
    
    FATFileSystem fs("sd", &sd);
    FILE *fp = fopen("/sd/test.txt","r");
    if(fp == NULL) {
        error("Could not open or find file for read\n");
        sd.deinit();
        return -1;
    } else {
        //Put some text in the file...
        char buff[64]; buff[63] = 0;
        while (!feof(fp)) {
            fgets(buff, 63, fp);
            printf("%s\n", buff);
        }
        //Tidy up here
        fclose(fp);
        printf("SD Write done...\n");
        sd.deinit();
        return 0;
    }
}