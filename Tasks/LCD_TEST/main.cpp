#include "../lib/uopmsb/uop_msb_1_0_0.h"

DigitalOut LCD_RS(PD_11);
DigitalOut LCD_E(PD_13);
DigitalOut LCD_RW(PD_12);
DigitalOut LCD_BKL(PD_14,0);
BusOut LCD_DATA(PD_0, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7);


#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

void write_lcd(uint8_t rs, uint8_t rw, uint8_t b)
{
    LCD_RS = rs;
    LCD_RW = rw;
    wait_ns(5);
    LCD_E = 1;
    wait_ns(25);    //Rising edge
    wait_ns(100);   //Setup
    LCD_DATA = b;
    wait_ns(40);    //Data setup time
    LCD_E = 0;
    wait_ns(25);    //Falling edge
    wait_ns(10);    //Hold time

    //Prevent premature write
    wait_us(1);
}

void lcd_cls() {
    write_lcd(0, 0, 0b00000001);
    wait_us(1600); 
}

void lcd_home() {
    write_lcd(0, 0, 0b00000010);
    wait_us(1600);    
}

void lcd_setEntryMode(uint8_t ID, uint8_t SH)
{
    uint8_t dat = 0b00000100;
    dat |= (ID ? 2 : 0);
    dat |= (SH ? 1 : 0);
    write_lcd(0, 0, dat);
    wait_us(50);    
}

void lcd_displayOnOffControl(uint8_t Disp, uint8_t Cursor, uint8_t Blink)
{
    uint8_t dat = 0b00001000;
    dat |= (Disp ? 4 : 0);
    dat |= (Cursor ? 2 : 0);
    dat |= (Blink ? 1 : 0);
    write_lcd(0, 0, dat);
    wait_us(50);       
}

void lcd_cursorOrDisplayShift(uint8_t SC, uint8_t RL)
{
    uint8_t dat = 0b00010000;
    dat |= (SC ? 8 : 0);
    dat |= (RL ? 4 : 0);
    write_lcd(0, 0, dat);
    wait_us(50);  
}

void lcd_functionSet(uint8_t DL=1, uint8_t N=1, uint8_t F=0)
{
    uint8_t dat = 0b00100000;
    dat |= (DL ? 16 : 0);
    dat |= (N ? 8 : 0);
    dat |= (F ? 4 : 0);
    write_lcd(0, 0, dat);
    wait_us(50);     
}

// main() runs in its own thread in the OS
int main()
{
    //Poweron wait
    wait_us(100000);
    //Function set
    write_lcd(0, 0, 0b00111000);
    wait_us(50);
    //Function set
    write_lcd(0, 0, 0b00111000);
    wait_us(50);
    //Display ON
    lcd_displayOnOffControl(1,1,0);
    //CLS
    lcd_cls();
    //Entry Mode
    write_lcd(0, 0, 0b00000110);
    wait_us(50);        

    write_lcd(1, 0, 'X');

    while (true) {
        led1 = !led1;
        wait_us(500000);
        write_lcd(1, 0, '1');
    }
}

