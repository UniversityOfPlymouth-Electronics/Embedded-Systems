

#ifndef LORANODE_H
#define LORANODE_H

#include "mbed.h"
#include <iostream>
#include <string>

#define LORA_MODE_OTAA              "LWOTAA"
#define LORA_MODE_ABP               "LWABP"
#define LORA_MODE_TEST              "TEST"
#define LORA_EU868_BAND             "EU868"
#define LORA_CHAN_0_2               "0-2"

typedef enum{
    LORA_OK,LORA_TIMEOUT,LORA_ERROR, LORA_UNEXPECTED_REPLY, LORA_UNKNOWN_ERROR
}loraATError_t;

typedef enum{
    LORA_AT_COMMAND,
    LORA_AT_SHOW_ID,
    LORA_AT_SET_DEVADDR,
    LORA_AT_SET_APPEUI,
    LORA_AT_SET_DEVEUI,
    LORA_AT_SET_APP_KEY,
    LORA_AT_SET_MODE,
    LORA_AT_SET_CHANNEL,
    LORA_AT_SET_BAND,
    LORA_AT_JOIN,
    LORA_AT_SEND_STR,
    LORA_AT_SEND_CONF_STR
}loraCommand_t;


class LoraNode {
private:
    BufferedSerial _serial;
    uint8_t _serial_rec=false;
    uint8_t _buffer_reset=true;
    char _rx_buffer[256];
    Timer t;

public:
    LoraNode(PinName txpin, PinName rxpin, uint16_t baud) : _serial(txpin,rxpin,baud){

    }



void generateCommandStrings(char* txbuf, char* rxbuf, loraCommand_t command, char* arg=nullptr ){

    switch(command){
        case LORA_AT_COMMAND:{
            strcpy(txbuf,"AT\n");
            strcpy(rxbuf, "+AT: OK");
            break;
        }
        case LORA_AT_SHOW_ID:{
            strcpy(txbuf,"AT+ID\n");
            strcpy(rxbuf, "+ID: AppEui");
            break;
        }
        case LORA_AT_SET_DEVADDR:{
         //   sprintf(txbuf,"AT+ID=DEVADDR,\"%s\"\n",(char*)arg); 
         //   sprintf(txbuf,"+ID=DEVADDR"" %s ""\n",(char*)arg);  //WRONG!
            break;
        }
        case LORA_AT_SET_APPEUI:{
            sprintf(txbuf,"AT+ID=APPEUI,\"%s\"\n",(char*)arg); 
            sprintf(rxbuf,"+ID: AppEui, %s",(char*)arg); 
            break;
        }
        case LORA_AT_SET_DEVEUI:{
            sprintf(txbuf,"AT+ID=DEVEUI,\"%s\"\n",(char*)arg); 
            sprintf(rxbuf,"+ID: DevEui, %s",(char*)arg); 
            break;
        }
        case LORA_AT_SET_APP_KEY:{
            sprintf(txbuf,"AT+KEY=APPKEY,\"%s\"\n",(char*)arg);
            sprintf(rxbuf,"+KEY: ");
            break;
        }
        case LORA_AT_SET_MODE:{
            sprintf(txbuf,"AT+MODE=\"%s\"\n", (char*) arg);
            sprintf(rxbuf,"+MODE: %s",(char*)arg);
            break;
        }
        case LORA_AT_SET_CHANNEL:{
            sprintf(txbuf,"AT+CH=NUM,%s\n", (char*) arg);
            sprintf(rxbuf,"+CH: NUM, %s",(char*) arg);
            break;
        }

        case LORA_AT_SET_BAND:{
            char b[64];
            strcpy(b,arg);
            sprintf(txbuf,"AT+DR=%s\n", b);
            sprintf(rxbuf,"+DR: %s",b);
            break;
        }
        case LORA_AT_JOIN:{
                        char b[64];
            strcpy(b,arg);
            sprintf(txbuf,"AT+JOIN\n");
            sprintf(rxbuf,"+JOIN: Done");
            break;
        }
        case LORA_AT_SEND_STR:{
            sprintf(txbuf,"AT+MSG=\"%s\"\n", (char*) arg);
            sprintf(rxbuf,"+MSG: Done");
            break;
        }
        case LORA_AT_SEND_CONF_STR:{
            break;
        }
        default:{
            break;
        }

    }
}


loraATError_t sendAndWait(loraCommand_t command, char* arg=nullptr, int timeout=5000, char* ret_str=nullptr){
    char tx_data[256];
    char rx_data [256]={0};
    char expectedrx[256]={0};
    int rx_index=0;


    generateCommandStrings(&tx_data[0],expectedrx,command,arg);
   // queue.call(printf,"ex:%s",expectedrx);
    t.start();
    t.reset();
    _serial.write(tx_data, sizeof(tx_data));
    //queue.call(printf,"Sending AT Command: %s",tx_data);
    
    char c[1]={'c'};
        
    while((t.read_ms()<timeout) && (c[0]!='\0')){
        if(_serial.readable()){
            int bytes_rec = _serial.read(&c,1);
            for(int i=0;i<bytes_rec;i++){      
                rx_data[rx_index] = c[i];
                rx_index++;
            }
       }
    }

    _buffer_reset=true;
    _serial_rec=false;

    if(ret_str !=nullptr){
        strcpy(ret_str,rx_data);
    }

    std::string ex = expectedrx;
    std::string got = rx_data;


    if (strstr(rx_data,"ERROR")){
        return LORA_ERROR;
    }
    else if(got.find(ex)!=string::npos){
       // queue.call(printf,"match\n");
        return LORA_OK;
    }
    
   // queue.call(printf,"no match\nex:%s\ngt:%s\r\n",expectedrx,got.c_str());

    if(t.read_ms()>=timeout){
        return LORA_TIMEOUT;
    }

    return LORA_UNEXPECTED_REPLY;

}

loraATError_t sendAtCommand(int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_COMMAND,nullptr,timeout,ret_str));
}

loraATError_t requestInfo(int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_SHOW_ID,nullptr,timeout,ret_str));
}

loraATError_t setAppKey(char* key, int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_SET_APP_KEY,key,timeout,ret_str));
}

loraATError_t setMode(char* mode, int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_SET_MODE,mode,timeout,ret_str));
}

loraATError_t setBand(char* band, int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_SET_BAND,band,timeout,ret_str));
}

loraATError_t setChannel(char* chan, int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_SET_CHANNEL,chan,timeout,ret_str));
}

loraATError_t setDevEUI(char* eui, int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_SET_DEVEUI,eui,timeout,ret_str));
}

loraATError_t setAppEUI(char* eui, int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_SET_APPEUI,eui,timeout,ret_str));
}

loraATError_t joinNetwork(int timeout=4000, char* ret_str=nullptr){
    return(sendAndWait(LORA_AT_JOIN,nullptr,timeout,ret_str));
}

loraATError_t sendString(char* tx_str, char* ret_str=nullptr){

    return sendAndWait(LORA_AT_SEND_STR, tx_str, 12000, ret_str);
}

BufferedSerial& getSerialInterface(){
    return _serial;
}

};

#endif