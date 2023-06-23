// #include "mbed.h"
// #include <chrono>
// #include <iostream>
// #include <string>


// UnbufferedSerial loraSerial(PD_5,PD_6,9600);

// int loraserialbufferindex;
// bool loraSerialrecevied = false;
// BufferedSerial Serial(USBTX,USBRX,115200);
// char serialbuffer[128];
// char loraserialtxbuffer[256];
// char loraserialrxbuffer[256];
// int serialbufferindex;



// // LORA_AT_COMMAND             "AT\n"
// // LORA_AT_SHOW_ID             "AT+ID\n"
// // LORA_AT_SET_DEVEUI(eui)     "AT+ID=DEVEUI""" eui """\n" //+ '"' + eui + '"' +'\n'
// // LORA_AT_SET_DEVADDR(addr)   "AT+ID=DEVADDR" + '"' + addr + '"' +'\n'
// // LORA_AT_SET_APPEUI(eui)     "AT+ID=APPEUI" + '"' + eui + '"' +'\n'
// // LORA_SET_APP_KEY            sprintf(loraserialtxbuffer,"AT+KEY=%s\n",LORA_TTN_APPKEY) //+ '"' + eui + '"' +'\n'    "AT+KEY=" + (ak) + '\n'
// // LORA_AT_SET_MODE(mode)      "AT+MODE=" +'"' + mode + '"' + '\n'
// #define LORA_MODE_OTAA              "LWOTAA"
// #define LORA_MODE_ABP               "LWABP"
// #define LORA_MODE_TEST              "TEST"
// #define LORA_EU868_BAND             "EU868"
// #define LORA_CHAN_0_2               "0-2"
// // LORA_AT_JOIN                "AT+JOIN"+'\n'
// // LORA_AT_SEND_STR(str)       "AT+MSG="+ '"' + str + '"' + '\n'
// // LORA_AT_SEND_CONF_STR(str)  "AT+CMSG="+ '"' + str + '"' + '\n'







// //LORA_AT_COMMAND_REPLY       "+AT: OK"
// //LORA_AT_SHOW_ID_REPLY       "+ID: AppEui"
// //LORA_AT_SET_DEVEUI(eui)     "AT+ID=DEVEUI" + '"' + eui + '"'
// // LORA_AT_SET_DEVADDR(addr)   "AT+ID=DEVEUI" + '"' + addr + '"'
// // LORA_AT_SET_APPEUI(eui)     "AT+ID=APPEUI" + '"' + eui + '"'
// //LORA_SET_APP_KEY_REPLY(ak)   sprintf(loraserialrxbuffer,"+KEY= %s\n",LORA_TTN_APPKEY)
// // LORA_AT_SET_MODE(mode)      "AT+MODE=" +'"' + mode + '"'
// // LORA_MODE_OTAA              "LWOTAA"
// // LORA_MODE_ABP               "LWABP"
// // LORA_MODE_TEST              "TEST"
// // LORA_AT_JOIN                "AT+JOIN"
// // LORA_AT_SEND_STR(str)       "AT+MSG="+ '"' + str + '"'
// // LORA_AT_SEND_CONF_STR(str)  "AT+CMSG="+ '"' + str + '"'

// Thread serth;
// EventQueue queue;

// typedef enum{
//     LORA_OK,LORA_TIMEOUT,LORA_ERROR
// }loraATError_t;

// typedef enum{
//     LORA_AT_COMMAND,
//     LORA_AT_SHOW_ID,
//     LORA_AT_SET_DEVADDR,
//     LORA_AT_SET_APPEUI,
//     LORA_AT_SET_DEVEUI,
//     LORA_AT_SET_APP_KEY,
//     LORA_AT_SET_MODE,
//     LORA_AT_SET_CHANNEL,
//     LORA_AT_SET_BAND,
//     LORA_AT_JOIN,
//     LORA_AT_SEND_STR,
//     LORA_AT_SEND_CONF_STR
// }loraCommand_t;

//     Timer t;
// void lora_generate_command_strings(char* txbuf, char* rxbuf, loraCommand_t command, void* arg=nullptr ){
//         memset(txbuf,0,sizeof(txbuf));
//     switch(command){
//         case LORA_AT_COMMAND:{
//             strcpy(txbuf,"AT\n");
//             strcpy(rxbuf, "+AT: OK\n");
//             break;
//         }
//         case LORA_AT_SHOW_ID:{
//             strcpy(txbuf,"AT+ID\n");
//             strcpy(rxbuf, "+ID: AppEui\n");
//             break;
//         }
//         case LORA_AT_SET_DEVADDR:{
//          //   sprintf(txbuf,"AT+ID=DEVADDR,\"%s\"\n",(char*)arg); 
//          //   sprintf(txbuf,"+ID=DEVADDR"" %s ""\n",(char*)arg);  //WRONG!
//             break;
//         }
//         case LORA_AT_SET_APPEUI:{
//             sprintf(txbuf,"AT+ID=APPEUI,\"%s\"\n",(char*)arg); 
//             sprintf(rxbuf,"+ID: AppEui, %s\n",(char*)arg); 
//             break;
//         }
//         case LORA_AT_SET_DEVEUI:{
//             sprintf(txbuf,"AT+ID=DEVEUI,\"%s\"\n",(char*)arg); 
//             sprintf(rxbuf,"+ID: DevEui, %s\n",(char*)arg); 
//             break;
//         }
//         case LORA_AT_SET_APP_KEY:{
//             sprintf(txbuf,"AT+KEY=APPKEY,\"%s\"\n",(char*)arg);
//             sprintf(rxbuf,"+KEY= %s\n",(char*)arg);
//             break;
//         }
//         case LORA_AT_SET_MODE:{
//             sprintf(txbuf,"AT+MODE=\"%s\"\n", (char*) arg);
//             sprintf(rxbuf,"+MODE: %s\n",(char*)arg);
//             break;
//         }
        
//         case LORA_AT_SET_CHANNEL:{
//             sprintf(txbuf,"AT+CH=NUM,%s\n", (char*) arg);
//             sprintf(rxbuf,"+CH: NUM, %s\n",(char*) arg);
//             break;
//         }

//         case LORA_AT_SET_BAND:{
//             sprintf(txbuf,"AT+DR=%s\n", (char*) arg);
//             sprintf(rxbuf,"+DR: %s\n",(char*) arg);
//             break;
//         }
//         case LORA_AT_JOIN:{
//             sprintf(txbuf,"AT+JOIN\n", (char*) arg);
//             sprintf(rxbuf,"+JOIN: Done\n");
//             break;
//         }
//         case LORA_AT_SEND_STR:{
//             sprintf(txbuf,"AT+MSG=%s\n", (char*) arg);
//             sprintf(rxbuf,"+MSG: Done\n");
//             break;
//         }
//         case LORA_AT_SEND_CONF_STR:{
//             break;
//         }
//         default:{
//             break;
//         }

//     }
// }

// bool buffer_reset=true;

// loraATError_t lora_send_and_wait(loraCommand_t command, void* arg=nullptr, int timeout=5000, char* ret_str=nullptr){
//     char tx_data[256];
//     char expectedrx[256];

//     lora_generate_command_strings(tx_data,expectedrx,command,arg);

//     t.start();
//     t.reset();
//     std::string str="";
//     loraSerial.write(tx_data, sizeof(tx_data));
//     queue.call(printf,"Sending AT Command: %s",tx_data);
//     while(loraSerialrecevied==false && (t.read_ms()<timeout));
//     buffer_reset=true;
//     loraSerialrecevied=false;

//     if(ret_str !=nullptr){
//         strcpy(ret_str,loraserialrxbuffer);
//     }


//     if (strstr(loraserialrxbuffer,"ERROR")){
//         return LORA_ERROR;
//     }
//     else if(t.read_ms()>=timeout){
//         return LORA_TIMEOUT;
//     }

//     return LORA_OK;
// }


// void loraserialrx_cb(){
//     char c;
//     if(buffer_reset){
//         loraSerialrecevied=true;
//         loraserialbufferindex=0;
//         memset(loraserialrxbuffer,0,sizeof(loraserialrxbuffer));
//         buffer_reset=false;
//     }
//     if(loraSerial.read(&c,1)){
//         loraserialrxbuffer[loraserialbufferindex] = c;
//         loraserialbufferindex++;
//     }
// }

// loraATError_t sendString(char* tx_str, char* ret_str=nullptr){
//     return lora_send_and_wait(LORA_AT_SEND_STR, tx_str, 10000, ret_str);
// }


// int main()
// {
//     serth.start(callback(&queue, &EventQueue::dispatch_forever));
//     loraSerial.attach(loraserialrx_cb,SerialBase::RxIrq);
//     char at_rec_buf[256];


        
//         loraATError_t err = lora_send_and_wait(LORA_AT_COMMAND,nullptr,10000, at_rec_buf);
//         if(err != LORA_OK){
//             queue.call(printf,"Lora AT Error (%d)\r\n\n",err);
//             queue.call(printf,"%s\n",at_rec_buf);
//         }
//         else{
//             queue.call(printf,"Lora AT OK\r\n\n");
//         }



//         err = lora_send_and_wait(LORA_AT_SHOW_ID,nullptr,10000,at_rec_buf);
//         if(err != LORA_OK){
//             queue.call(printf,"Lora ID Error (%d)\r\n",err);
//         }
//         else{
//             queue.call(printf,"Lora ID OK\r\n");
//         }
//         queue.call(printf,"%s\n",at_rec_buf);



//         char key[] = "FE7954995A3E156ECFA2DBD326FCF34E";
//         err = lora_send_and_wait(LORA_AT_SET_APP_KEY,key,10000,at_rec_buf);
//         if(err!=LORA_OK){
//            queue.call(printf,"LORA Key Error\r\n");
//         }
//         else{
//             queue.call(printf,"Lora Key OK\r\n");
//         }
//         queue.call(printf,"%s\n",at_rec_buf);



//         err = lora_send_and_wait(LORA_AT_SET_MODE,(char*)LORA_MODE_OTAA,10000,at_rec_buf);
//         if(err!=LORA_OK){
//            queue.call(printf,"LORA Mode Error\r\n");
//         }
//         else{
//             queue.call(printf,"Lora Mode OK\r\n");
//         }
//         queue.call(printf,"%s\n",at_rec_buf);



//         err = lora_send_and_wait(LORA_AT_SET_BAND,(char*)LORA_EU868_BAND,10000,at_rec_buf);
//         if(err!=LORA_OK){
//            queue.call(printf,"LORA band Error\r\n");
//         }
//         else{
//             queue.call(printf,"Lora band OK\r\n");
//         }
//         queue.call(printf,"%s\n",at_rec_buf);



//         err = lora_send_and_wait(LORA_AT_SET_CHANNEL,(char*)LORA_CHAN_0_2,10000,at_rec_buf);
//         if(err!=LORA_OK){
//            queue.call(printf,"LORA chan Error\r\n");
//         }
//         else{
//             queue.call(printf,"Lora chan OK\r\n");
//         }
//         queue.call(printf,"%s\n",at_rec_buf);



//         char deveui[] = "70:B3:D5:7E:D0:05:C8:4C";
//         err = lora_send_and_wait(LORA_AT_SET_DEVEUI,deveui,10000,at_rec_buf);
//         if(err!=LORA_OK){
//            queue.call(printf,"LORA deveui Error\r\n");
//         }
//         else{
//             queue.call(printf,"Lora deveui OK\r\n");
//         }
//         queue.call(printf,"%s\n",at_rec_buf);


//         char appeui[] = "00:00:00:00:00:00:00:AB";
//         err = lora_send_and_wait(LORA_AT_SET_APPEUI,appeui,10000,at_rec_buf);
//         if(err!=LORA_OK){
//            queue.call(printf,"LORA deveui Error\r\n");
//         }
//         else{
//             queue.call(printf,"Lora deveui OK\r\n");
//         }
//         queue.call(printf,"%s\n",at_rec_buf);



//         err = lora_send_and_wait(LORA_AT_JOIN,nullptr,10000,at_rec_buf);
//         if(err!=LORA_OK){
//            queue.call(printf,"LORA chan Error\r\n");
//         }
//         else{
//             queue.call(printf,"Lora chan OK\r\n");
//         }
//         queue.call(printf,"%s\n",at_rec_buf);

//     while(1){

//         char tx_buf[128] = "\"Hello world!\"";
//         err = sendString(tx_buf);
//         if(err!=LORA_OK){
//            queue.call(printf,"LORA msg Error\r\n");
//         }
//         else{
//             queue.call(printf,"Lora msg OK\r\n");
//         }
        
//         queue.call(printf,"%s\n",at_rec_buf);
//         ThisThread::sleep_for(std::chrono::milliseconds(30000));
//     }
// }

