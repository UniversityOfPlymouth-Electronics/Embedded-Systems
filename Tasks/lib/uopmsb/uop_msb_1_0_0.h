// (c) 2020 University of Plymouth

// another edit 16 07 2020

#include "mbed.h"

// *****************************
// Traffic Lights (individual) *
// *****************************
#define TRAFFIC1_GRN_PIN PC_9
#define TRAFFIC1_YELL_PIN PC_8
#define TRAFFIC1_RED_PIN PC_7

#define TRAFFIC2_GRN_PIN PC_2
#define TRAFFIC2_YELL_PIN PC_3
#define TRAFFIC2_RED_PIN PC_6

// ****************************************
// LED strip and 7-segment (All on PORTE) *
// ****************************************
//All lower 16-bits of PORTE pins are outputs
#define LED_MASK 0x0000FFFF
//For initialisation, OE=0, LE=1, DATA=0
#define LED_INIT 0x00007C00 //0b0111 1100 0000 0000
//For OFF condition, OE = 1, LE=0 and DATA=0 
#define LED_OFF 0x00008001


// BUZZER
#define BUZZER PB_13

// THE MATRIX
#define MATRIX_LATCH PB_6
#define MATRIX_OE PB_12

// LCD
#define LCD_D0_PIN PD_0
#define LCD_D1_PIN PD_1
#define LCD_D2_PIN PD_2
#define LCD_D3_PIN PD_3
#define LCD_D4_PIN PD_4
#define LCD_D5_PIN PD_5
#define LCD_D6_PIN PD_6
#define LCD_D7_PIN PD_7
#define LCD_RS_PIN PD_11
#define LCD_RW_PIN PD_12
#define LCD_E_PIN PD_13
#define LCD_BKL_PIN PD_14

class LCD_16X2_DISPLAY {
public:
    enum CURSOR_MOVE_DIR { DECREMENT=0, INCREMENT=1 }; 
    enum DISPLAY_SHIFT {OFF=0, ON=1};

    // 8-bit constructor
    LCD_16X2_DISPLAY(PinName rs=LCD_RS_PIN, PinName rw=LCD_RW_PIN, PinName e=LCD_E_PIN, PinName bkl=LCD_BKL_PIN, 
    PinName d0=LCD_D0_PIN, PinName d1=LCD_D1_PIN, PinName d2=LCD_D2_PIN, PinName d3=LCD_D3_PIN, 
    PinName d4=LCD_D4_PIN, PinName d5=LCD_D5_PIN, PinName d6=LCD_D6_PIN, PinName d7=LCD_D7_PIN) : _rs(rs), _e(e), _rw(rw), _bkl(bkl), _data(d0, d1, d2, d3, d4, d5, d6, d7) 
    {
        //Power on wait
        wait_us(100000);

        //Function set
        functionSet(1,1,0);
        
        //Display ON
        displayOnOffControl(1,1,0);

        //CLS
        cls();

        //Entry Mode
        setEntryMode(1, 0);
    }

protected:
    DigitalOut _rs;
    DigitalOut _e;
    DigitalOut _rw;
    DigitalOut _bkl;
    BusOut _data;
    
public:
    void write_lcd(uint8_t rs, uint8_t b)
    {
        _rs = rs;
        _rw = 0;
        wait_ns(5);
        _e = 1;
        wait_ns(25);    //Rising edge
        wait_ns(100);   //Setup
        _data = b;
        wait_ns(40);    //Data setup time
        _e = 0;
        wait_ns(25);    //Falling edge
        wait_ns(10);    //Hold time

        //Prevent premature write
        wait_us(1);
    }

    void cls() {
        write_lcd(0, 0b00000001);
        wait_us(1600); 
    }

    void home() {
        write_lcd(0, 0b00000010);
        wait_us(1600);    
    }

    void setEntryMode(CURSOR_MOVE_DIR ID=INCREMENT, DISPLAY_SHIFT SH=OFF)
    {
        uint8_t dat = 0b00000100;
        dat |= (ID ? 2 : 0);
        dat |= (SH ? 1 : 0);
        write_lcd(0, dat);
        wait_us(50);          
    }
    void setEntryMode(uint8_t ID, uint8_t SH)
    {
        uint8_t dat = 0b00000100;
        dat |= (ID ? 2 : 0);
        dat |= (SH ? 1 : 0);
        write_lcd(0, dat);
        wait_us(50);    
    }

    void displayOnOffControl(uint8_t Disp, uint8_t Cursor, uint8_t Blink)
    {
        uint8_t dat = 0b00001000;
        dat |= (Disp ? 4 : 0);
        dat |= (Cursor ? 2 : 0);
        dat |= (Blink ? 1 : 0);
        write_lcd(0, dat);
        wait_us(50);       
    }

    void cursorOrDisplayShift(uint8_t SC, uint8_t RL)
    {
        uint8_t dat = 0b00010000;
        dat |= (SC ? 8 : 0);
        dat |= (RL ? 4 : 0);
        write_lcd(0, dat);
        wait_us(50);  
    }

    void functionSet(uint8_t DL=1, uint8_t N=1, uint8_t F=0)
    {
        uint8_t dat = 0b00100000;
        dat |= (DL ? 16 : 0);   //Data lines (0: 4 bit; 1: 8 bit)
        dat |= (N ? 8 : 0);     //Number of display lines (0: 1 line; 1: 2 lines)
        dat |= (F ? 4 : 0);     //Font: (0: 5x8; 1: 5x10)
        write_lcd(0, dat);
        wait_us(50);     
    }    
};