/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "F429_Mega_Shell_Header.h"
#include "TextLCD/TextLCD.h"
#include <cstdio>

//prototypes

void clearMatrix();
void matrix_scan();

int pic[8][16] = {
            {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
            };




void arrayReader(int picArray[8][8], int numArray[8][2]);
void matrix_print();

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

    matrix_print();
    
}

void arrayReader(int pic [8][16], int numArray[8][2]){
    for(int i = 0; i<7; i++){
        for(int j = 0; j<7; j++){
            numArray[i][0]+=pow(2,j)*pic[i][j];
        }
        for(int j = 0; j<7; j++){
            numArray[i][1]+=pow(2,j)*pic[i+8][j];
        }
        
    }
}

void matrix_print(){
    int picNum[8][2] = {
            {0,0},
            {0,0},
            {0,0},
            {0,0},
            {0,0},
            {0,0},
            {0,0},
            {0,0}
            
    };
            arrayReader(pic,picNum);

    while(true){
        for(int i = 0; i< 7; i++){
            cs = 0;
            spi.write(picNum[i][0]);
            spi.write(picNum[i][1]);
            spi.write(i);
            cs = 1;
            
        }
        
        
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
