#include "mbed.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "uop_msb.h"

uop_msb::LCD_16X2_DISPLAY lcdDisp;
DigitalOut backLight(LCD_BKL_PIN,1);


class NotificationLED{
    private: 
    DigitalOut led;
    Thread th;
    Semaphore sem;
    void thr(){
        while(1){
            sem.acquire();
            led=1;
            ThisThread::sleep_for(100ms);
            led=0;
            ThisThread::sleep_for(100ms);
        }
    }     

    public:
    NotificationLED(PinName led_pin) : led(led_pin){
        th.start(callback(this,&NotificationLED::thr));
    }

    void notify(){
        sem.release();
    }
};


class Identifier{
    
    private:
    
    uint64_t* uid_ptr= (uint64_t*)0x1FFF7A10; //Memory address of Nucleo UID
    uint64_t unique_id=0;
    std::string name = "";
    
    public:
    std::string get_name(){
        return name;
    }

    void set_name(std::string str){
        name = str;
    }
    
    void gen_name(){
        if(unique_id==3546673870078017568){
            name = "subscriber1";
        }
        else{
            name =  "subscriber2";   
        } 
    }

    uint64_t get_id(){
        return unique_id;
    }

    Identifier(){
        unique_id = *uid_ptr;
        gen_name();
  
    }

    Identifier(std::string str){
        unique_id = *uid_ptr;
        name = str;
    }

};
