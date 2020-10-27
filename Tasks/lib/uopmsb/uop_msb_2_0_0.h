// (c) 2020 University of Plymouth

// updated 25 10 2020
#ifndef __UOP_MSB_2_0_0_
#define __UOP_MSB_2_0_0_

#include "mbed.h"
#include "Stream.h"

//#include <iostream>
#include <chrono>
#include <map>

namespace uop_msb_200 {

    // *****************************
    // Traffic Lights (individual) *
    // *****************************
    
    //PUSH PULL
    #define TRAF_GRN1_PIN PC_6
    #define TRAF_YEL1_PIN PC_3
    #define TRAF_RED1_PIN PC_2

    //OPEN DRAIN
    #define TRAF_GRN2_PIN PC_9
    #define TRAF_YEL2_PIN PC_8
    #define TRAF_RED2_PIN PC_7
    #define TRAF_WHITE_PIN PF_10

    // ****************************************
    // LED strip and 7-segment (All on PORTE) *
    // ****************************************
    //All lower 16-bits of PORTE pins are outputs
    #define LED_MASK 0x0000FFFF
    //For initialisation, OE=0, LE=1, DATA=0
    #define LED_INIT 0x00007C00 //0b0111 1100 0000 0000
    //For OFF condition, OE = 1, LE=0 and DATA=0 
    #define LED_OFF 0x00008001

    #define LED_BAR_OE_PIN PE_0
    #define LED_D0_PIN PE_2
    #define LED_D1_PIN PE_3
    #define LED_D2_PIN PE_4
    #define LED_D3_PIN PE_5
    #define LED_D4_PIN PE_6
    #define LED_D5_PIN PE_7
    #define LED_D6_PIN PE_8
    #define LED_D7_PIN PE_9
    #define LED_D1_LE_PIN PE_10
    #define LED_D2_LE_PIN PE_11
    #define LED_RED_LE_PIN PE_12
    #define LED_GRN_LE_PIN PE_13
    #define LED_BLUE_LE_PIN PE_14
    #define LED_DIGIT_OE_PIN PE_15

    // *********
    // BUTTONS *
    // *********
    #define BTN1_PIN PG_0
    #define BTN2_PIN PG_1
    #define BTN3_PIN PG_2
    #define BTN4_PIN PG_3

    class Buttons {
    public:
        Buttons(PinName b1 = BTN1_PIN, PinName b2 = BTN2_PIN, PinName b3 = BTN3_PIN, PinName b4 = BTN4_PIN, PinName buser = USER_BUTTON) :
        Button1(b1), Button2(b2), Button3(b3), Button4(b4), BlueButton(buser)
        {
            
        }
        DigitalIn Button1, Button2, Button3, Button4, BlueButton;
    };

    // BUZZER
    #define BUZZER_PIN PB_13
    class Buzzer {
        public:
        typedef enum {LOWER_OCTAVE, MIDDLE_OCTAVE, HIGHER_OCTAVE} OCTAVE_REGISTER;

        Buzzer(PinName p = BUZZER_PIN) : _buzzer(p) {
            volatile double T = periodForNote_us("C");
            _buzzer.period_us(T);
            rest();      
        }

        void playTone(const char* note, OCTAVE_REGISTER octave=MIDDLE_OCTAVE)
        {
            _buzzer.period_us(periodForNote_us(note, octave));
            _buzzer.write(0.5f);
        }

        void rest() {
            _buzzer.write(0.0);
        }

        protected:
        
        PwmOut _buzzer;
        double periodForNote_us(const char* note, OCTAVE_REGISTER octave=MIDDLE_OCTAVE)
        {
            volatile uint8_t idx = offsetForNote(note); 
            volatile double f = note_freq[idx];

            switch (octave) {
                case LOWER_OCTAVE:
                    f *= 0.5;
                    break;
                case MIDDLE_OCTAVE:
                    break;
                case HIGHER_OCTAVE:
                    f *= 2.0;
                    break;
                default:
                    break;
            }
            return 1000000.0 / f;
        }

        private:
        uint8_t offsetForNote(const char *noteStr)
        {
            switch (noteStr[0])
            {
                case 'A':
                    return (noteStr[1]=='#') ? 1 : 0;
                case 'B':
                    return 2;
                case 'C':
                    return (noteStr[1]=='#') ? 4 : 3; 
                case 'D':
                    return (noteStr[1]=='#') ? 6 : 5;                    
                case 'E':
                    return 7;
                case 'F':
                    return (noteStr[1]=='#') ? 9 : 8;                                           
                case 'G':
                    return (noteStr[1]=='#') ? 11 : 10;  
                default:
                    return 0;                   
            }
        }

        double note_freq[12] = {
            220.0, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3
        };

    };

    // THE MATRIX
    #define MATRIX_LATCH_PIN PB_6
    #define MATRIX_OE_PIN PB_12

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

    class LCD_16X2_DISPLAY : public Stream {
    public:
        typedef enum {INSTRUCTION=0, DATA=1} REGISTER_SELECT;   // RS
        typedef enum {WRITE=0, READ=1} READWRITE;               // R/W
        typedef enum {DISABLE=0, ENABLE=1} ENABLE_STATE;        // E

        typedef enum {DECREMENT=0, INCREMENT=1} ENTRY_MODE_DIR;                             // I/D
        typedef enum {CURSOR_MOVE_ON_ENTRY=0, DISPLAY_SHIFT_ON_ENTRY=1} ENTRY_MODE_SHIFT;   // S
        typedef enum {DISP_OFF=0, DISP_ON=1} DISPLAY_STATUS;                        // D
        typedef enum {CURSOR_VISIBLE_OFF=0, CURSOR_VISIBLE_ON=1} CURSOR_VISIBLE;    // C
        typedef enum {BLINK_OFF=0, BLINK_ON=1} BLINK_STATUS;                        // B
        typedef enum {CURSOR_MOVE=0, DISPLAY_SHIFT=1} CURSOR_OR_DISPLAY_SHIFT;      // S/C
        typedef enum {SHIFT_LEFT=0, SHIFT_RIGHT} CURSOR_OR_DISPLAY_SHIFT_DIR;       // R/L
        typedef enum { FOURBIT=0, EIGHTBIT=1 } INTERFACE_DATA_LENGTH;               // DL
        typedef enum { ONELINE=0, TWOLINES=1 } INTERFACE_NUM_LINES;                 // N
        typedef enum { FONT_5X8=0, FONT_5X10=1} INTERFACE_FONT_SIZE;                // F

        enum LCDType {
            LCD16x2     /**< 16x2 LCD panel (default) */
            , LCD16x2B  /**< 16x2 LCD panel alternate addressing */
            , LCD20x2   /**< 20x2 LCD panel */
            , LCD20x4   /**< 20x4 LCD panel */
        };

        // 8-bit constructor
        LCD_16X2_DISPLAY(PinName rs=LCD_RS_PIN, PinName rw=LCD_RW_PIN, PinName e=LCD_E_PIN, PinName bkl=LCD_BKL_PIN, 
        PinName d0=LCD_D0_PIN, PinName d1=LCD_D1_PIN, PinName d2=LCD_D2_PIN, PinName d3=LCD_D3_PIN, 
        PinName d4=LCD_D4_PIN, PinName d5=LCD_D5_PIN, PinName d6=LCD_D6_PIN, PinName d7=LCD_D7_PIN,
        LCDType type=LCD16x2) : _rs(rs), _e(e), _rw(rw), _bkl(bkl), _data(d0, d1, d2, d3, d4, d5, d6, d7),_type(type) 
        {
            //Power on wait
            wait_us(100000);

            //Function set
            functionSet(EIGHTBIT, TWOLINES, FONT_5X8);
            
            //Display ON
            displayOnOffControl(DISP_ON, CURSOR_VISIBLE_OFF, BLINK_OFF);

            //CLS
            cls();

            //Entry Mode
            setEntryMode(INCREMENT, CURSOR_MOVE_ON_ENTRY);

            //Cursor moves right
            //cursorOrDisplayShift(CURSOR_MOVE, SHIFT_RIGHT);        
        }

    protected:
        LCDType _type;
        DigitalOut _rs;
        DigitalOut _e;
        DigitalOut _rw;
        DigitalOut _bkl;
        BusOut _data;
        uint8_t _row;
        uint8_t _column;

        uint8_t address(int row, int column) {
            switch (_type) {
                case LCD20x4:
                    switch (row) {
                        case 0:
                            return 0x80 + column;
                        case 1:
                            return 0xc0 + column;
                        case 2:
                            return 0x94 + column;
                        case 3:
                            return 0xd4 + column;
                    }
                case LCD16x2B:
                    return 0x80 + (row * 40) + column;
                case LCD16x2:
                case LCD20x2:
                default:
                    return 0x80 + (row * 0x40) + column;
            }
        }


    public:
        void character(int row, int column, uint8_t c) {
            volatile int a = address(row, column);
            set_DDRAM_Address(a);
            write(DATA, c);
        }

        void write(REGISTER_SELECT rs, uint8_t b)
        {
            _rs = rs;
            _rw = WRITE;
            wait_ns(5);
            _e = ENABLE;
            wait_ns(25);    //Rising edge
            wait_ns(100);   //Setup
            _data = b;
            wait_ns(40);    //Data setup time
            _e = DISABLE;
            wait_ns(25);    //Falling edge
            wait_ns(10);    //Hold time

            //Prevent premature write
            wait_us(50);
        }

        uint8_t read(REGISTER_SELECT rs=INSTRUCTION)
        {
            _rs = rs;
            _rw = 1;
            wait_ns(5);
            _e = 1;
            wait_ns(25);    //Rise time
            wait_ns(100);   //T_DDR
            uint8_t data = _data;    //Read
            wait_ns(40);
            _e = 0;
            wait_ns(25);    //Fall time
            wait_ns(10);    //t_H
            _rw = 0;
            wait_us(1);     //Final wait to prevent early trans
            return data;
        }

        void cls() {
            write(INSTRUCTION, 0b00000001);
            wait_us(1600); 
            home();
        }

        void home() {
            write(INSTRUCTION, 0b00000010);
            wait_us(1600); 
            _column = 0;
            _row = 0;       
        }

        void setEntryMode(ENTRY_MODE_DIR id=INCREMENT, ENTRY_MODE_SHIFT sh=CURSOR_MOVE_ON_ENTRY)
        {
            uint8_t dat = 0b00000100;
            dat |= (id ? 2 : 0);
            dat |= (sh ? 1 : 0);
            write(INSTRUCTION, dat);          
        }

        void displayOnOffControl(DISPLAY_STATUS d=DISP_ON, CURSOR_VISIBLE c=CURSOR_VISIBLE_OFF, BLINK_STATUS b=BLINK_OFF)
        {
            uint8_t dat = 0b00001000;
            dat |= (d ? 4 : 0);
            dat |= (c ? 2 : 0);
            dat |= (b ? 1 : 0);
            write(INSTRUCTION, dat);      
        }

        void cursorOrDisplayShift(CURSOR_OR_DISPLAY_SHIFT sc=CURSOR_MOVE, CURSOR_OR_DISPLAY_SHIFT_DIR rl=SHIFT_RIGHT)
        {
            uint8_t dat = 0b00010000;
            dat |= (sc ? 8 : 0);
            dat |= (rl ? 4 : 0);
            write(INSTRUCTION, dat); 
        }

        void functionSet(INTERFACE_DATA_LENGTH dl=EIGHTBIT, INTERFACE_NUM_LINES n=TWOLINES, INTERFACE_FONT_SIZE f=FONT_5X8)
        {
            uint8_t dat = 0b00100000;
            dat |= (dl ? 16 : 0);   //Data lines (0: 4 bit; 1: 8 bit)
            dat |= (n ? 8 : 0);     //Number of display lines (0: 1 line; 1: 2 lines)
            dat |= (f ? 4 : 0);     //Font: (0: 5x8; 1: 5x10)
            write(INSTRUCTION, dat);     
        }    

        void set_CGRAM_Address(uint8_t Addr)
        {
            uint8_t dat =  0b01000000;
            dat |= (Addr & 0b00111111);
            write(INSTRUCTION, dat);
        }

        void set_DDRAM_Address(uint8_t Addr)
        {
            uint8_t dat =  Addr & 0b01111111;
            dat |= 0b10000000;
            write(INSTRUCTION, dat);
        }

        bool isBusy()
        {
            return (read(INSTRUCTION) & 0b10000000) ? true : false;
        }

        void locate(uint8_t row, uint8_t column) {
            _column = column;
            _row = row;
        }

        uint8_t columns() {
            switch (_type) {
                case LCD20x4:
                case LCD20x2:
                    return 20;
                case LCD16x2:
                case LCD16x2B:
                default:
                    return 16;
            }
        }

        uint8_t rows() {
            switch (_type) {
                case LCD20x4:
                    return 4;
                case LCD16x2:
                case LCD16x2B:
                case LCD20x2:
                default:
                    return 2;
            }
        }

        // STDIO
        virtual int _putc(int value) {
            if (value == '\n') {
                _column = 0;
                _row++;
                if (_row >= rows()) {
                    _row = 0;
                }
            } else {
                character(_row, _column, value);
                _column++;
                if (_column >= columns()) {
                    _column = 0;
                    _row++;
                    if (_row >= rows()) {
                        _row = 0;
                    }
                }
            }
            return value;
        }

        virtual int _getc() {
            return -1;
        }


    };

    // Mbed os 5 like Timer
    using namespace std::chrono;
    class TimerCompat : public Timer {

        public:
        long long read_ms() {
            return duration_cast<milliseconds>(elapsed_time()).count();
        }

        long long read_us() {
            return duration_cast<microseconds>(elapsed_time()).count();
        }
    };    

}

#endif