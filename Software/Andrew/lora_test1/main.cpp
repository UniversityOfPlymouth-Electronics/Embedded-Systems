#include "mbed.h"
#include <chrono>
#include <iostream>
#include <string>
#include "LoraNode.h"

//ttn mqtt pw : NNSXS.LYINEV6OE2AL73HNIHR3SVMWBV6D47JGQMIWMLQ.CZKBQMIEZDPTI63FPVBSGN2SDVSR47NQPC3RLNZAYQYWLRAYFVNA


BufferedSerial Serial(USBTX,USBRX,115200);
char serialbuffer[128];
int serialbufferindex;

Thread serth;
EventQueue queue;

LoraNode node(PD_5,PD_6,9600);
ATCmdParser at(&node.getSerialInterface(), "\r\n");
AnalogIn ldr(PC_0);

int main()
{
    serth.start(callback(&queue, &EventQueue::dispatch_forever));

    char at_rec_buf[256]={0};

        // Send AT (check for sign of life)
        queue.call(printf,"/////////////////////////////////////////\n");
        loraATError_t err = node.sendAtCommand(4000,at_rec_buf);// lora_send_and_wait(LORA_AT_COMMAND,nullptr,4000, at_rec_buf);
        if(err != LORA_OK){
            queue.call(printf,"Lora AT Error (%d)\r\n\n",err);
            queue.call(printf,"%s\n",at_rec_buf);
        }
        else{
            queue.call(printf,"Lora AT OK\r\n\n");
        }

        // Get Ids
        queue.call(printf,"/////////////////////////////////////////\n");
        err = node.requestInfo(4000,at_rec_buf);//lora_send_and_wait(LORA_AT_SHOW_ID,nullptr,4000,at_rec_buf)
        if(err != LORA_OK){
            queue.call(printf,"Lora ID Error (%d)\r\n",err);
        }
        else{
            queue.call(printf,"Lora ID OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);

        // Set App Key
        queue.call(printf,"/////////////////////////////////////////\n");
       // char key[] = "FE7954995A3E156ECFA2DBD326FCF34E";
        char key[] = "A480B207E3D5E3B57E67611981252954";
        
        err = node.setAppKey(key,4000,at_rec_buf);//lora_send_and_wait(LORA_AT_SET_APP_KEY,key,4000,at_rec_buf);
        if(err!=LORA_OK){
           queue.call(printf,"LORA Key Error(%d)\r\n\n",err);
        }
        else{
            queue.call(printf,"Lora Key OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);

        // Set mode
        queue.call(printf,"/////////////////////////////////////////\n");
        err = node.setMode((char*)LORA_MODE_OTAA,4000,at_rec_buf);
        if(err!=LORA_OK){
           queue.call(printf,"LORA Mode Error(%d)\r\n\n",err);
        }
        else{
            queue.call(printf,"Lora Mode OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);

        //Set band
        queue.call(printf,"/////////////////////////////////////////\n");
        err = node.setBand((char*)LORA_EU868_BAND,4000,at_rec_buf);
        if(err!=LORA_OK){
           queue.call(printf,"LORA band Error(%d)\r\n\n",err);
        }
        else{
            queue.call(printf,"Lora band OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);

        //Set Channel Range
        queue.call(printf,"/////////////////////////////////////////\n");
        err = node.setChannel((char*)LORA_CHAN_0_2,4000,at_rec_buf);
        if(err!=LORA_OK){
           queue.call(printf,"LORA chan Error(%d)\r\n\n",err);
        }
        else{
            queue.call(printf,"Lora chan OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);

        //Set Dev EUI
        queue.call(printf,"/////////////////////////////////////////\n");
       // char deveui[] = "70:B3:D5:7E:D0:05:C8:4C";
        char deveui[] ="70:B3:D5:7E:D0:05:E8:5D";
        err = node.setDevEUI(deveui,4000,at_rec_buf);
        if(err!=LORA_OK){
           queue.call(printf,"LORA deveui Error\r\n");
        }
        else{
            queue.call(printf,"Lora deveui OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);

        //Set App EUI
        queue.call(printf,"/////////////////////////////////////////\n");
       // char appeui[] = "00:00:00:00:00:00:00:AD";
        char appeui[] ="70:B3:D5:7E:D0:05:E8:5D";
        err = err = node.setAppEUI(appeui,4000,at_rec_buf);
        if(err!=LORA_OK){
           queue.call(printf,"LORA appeui Error\r\n");
        }
        else{
            queue.call(printf,"Lora appeui OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);

        //Send Join request
        queue.call(printf,"/////////////////////////////////////////\n");
        err = node.joinNetwork(12000,at_rec_buf);
        if(err!=LORA_OK){
           queue.call(printf,"LORA Join Error\r\n");
        }
        else{
            queue.call(printf,"Lora Join OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);

    while(1){

        //Send a string
        float fl = ldr.read();
        char tx_buf[32];
        sprintf(tx_buf,"LDR_VAL:%4.3f",fl);
        err = node.sendString(tx_buf,at_rec_buf);
        if(err!=LORA_OK){
           queue.call(printf,"LORA msg Error\r\n");
        }
        else{
            queue.call(printf,"Lora msg OK\r\n");
        }
        queue.call(printf,"%s\n",at_rec_buf);
        ThisThread::sleep_for(std::chrono::milliseconds(15000));
    }
}
