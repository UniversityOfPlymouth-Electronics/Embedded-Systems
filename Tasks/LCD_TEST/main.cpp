#include "../lib/uopmsb/uop_msb_1_0_0.h"

DigitalOut LCD_RS(PD_11);
DigitalOut LCD_E(PD_13);
DigitalOut LCD_RW(PD_12);
DigitalOut LCD_BKL(PD_14,0);
BusOut LCD_DATA(PD_0, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7);


#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

void write_lcd(uint8_t rs, uint8_t b)
{
    LCD_RS = rs;
    LCD_RW = 0;
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
    write_lcd(0, 0b00000001);
    wait_us(1600); 
}

void lcd_home() {
    write_lcd(0, 0b00000010);
    wait_us(1600);    
}

void lcd_setEntryMode(uint8_t ID, uint8_t SH)
{
    uint8_t dat = 0b00000100;
    dat |= (ID ? 2 : 0);
    dat |= (SH ? 1 : 0);
    write_lcd(0, dat);
    wait_us(50);    
}

void lcd_displayOnOffControl(uint8_t Disp, uint8_t Cursor, uint8_t Blink)
{
    uint8_t dat = 0b00001000;
    dat |= (Disp ? 4 : 0);
    dat |= (Cursor ? 2 : 0);
    dat |= (Blink ? 1 : 0);
    write_lcd(0, dat);
    wait_us(50);       
}

void lcd_cursorOrDisplayShift(uint8_t SC, uint8_t RL)
{
    uint8_t dat = 0b00010000;
    dat |= (SC ? 8 : 0);
    dat |= (RL ? 4 : 0);
    write_lcd(0, dat);
    wait_us(50);  
}

void lcd_functionSet(uint8_t DL=1, uint8_t N=1, uint8_t F=0)
{
    uint8_t dat = 0b00100000;
    dat |= (DL ? 16 : 0);   //Data lines (0: 4 bit; 1: 8 bit)
    dat |= (N ? 8 : 0);     //Number of display lines (0: 1 line; 1: 2 lines)
    dat |= (F ? 4 : 0);     //Font: (0: 5x8; 1: 5x10)
    write_lcd(0, dat);
    wait_us(50);     
}

// main() runs in its own thread in the OS
LCD_16X2_DISPLAY lcd;

int main()
{
    lcd.write_lcd(1, 'X');

    while (1);

    //Power on wait
    wait_us(100000);

    //Function set
    lcd_functionSet(1,1,0);
    
    //Display ON
    lcd_displayOnOffControl(1,1,0);

    //CLS
    lcd_cls();

    //Entry Mode
    lcd_setEntryMode(1, 0);     

    //Write a character
    write_lcd(1, 'X');

    while (true) {
        led1 = !led1;
        wait_us(500000);
        write_lcd(1, '1');
    }
}

