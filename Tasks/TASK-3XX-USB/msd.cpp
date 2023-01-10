

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////// ///////////SD CARD AS MSD///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#include "mbed.h"
#include "SDBlockDevice.h"
#include "USBMSD.h"


void usbthread();

SDBlockDevice sd(PB_5, PB_4, PB_3, PF_3);

//SDReader sd;
Thread th;

int main()
{
   // sd.frequency(5000000);
    th.start(usbthread);

    while (true) {
        ThisThread::sleep_for(osWaitForever);
    }

    return 0;
}

void usbthread(){
    USBMSD usb(&sd);
    while(1){
        usb.process();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////// ///////////HEAP MEMORY AS MSD///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////



// #include "mbed.h"
// #include "USBMSD.h"
// #include "FATFileSystem.h"
// #include <chrono>

// #define DEFAULT_BLOCK_SIZE  512
// #define HEAP_BLOCK_DEVICE_SIZE (128 * DEFAULT_BLOCK_SIZE)

// FATFileSystem heap_fs("heap_fs");
// HeapBlockDevice bd(HEAP_BLOCK_DEVICE_SIZE, DEFAULT_BLOCK_SIZE);
// void usbthread();
// Thread th;
// int main()
// {
//     bd.init();

//     FATFileSystem::format(&bd);

//     int err = heap_fs.mount(&bd);

//     if (err) {
//         printf("%s filesystem mount failed\ntry to reformat device... \r\n", heap_fs.getName());
//         err = heap_fs.reformat(&bd);
//     }

//     // If still error, then report failure
//     if (err) {
//         printf("Error: Unable to format/mount the device.\r\n");
//         while (1);
//     }

//     th.start(&usbthread);
    

//     volatile int counter=0;
//     while (true) {
//         char filename[32];
//         sprintf(filename,"/heap_fs/test%d.txt",counter);
//         FILE *fp = fopen(filename, "a");
//         if(fp == NULL) {
//             error("Could not open file for write\n");
//         }
//         char buf[32];
//         sprintf(buf,"Hello Heap storage device! %d\r\n",counter);

//         fprintf(fp, buf);
//         fclose(fp); 
//         counter++;
//         ThisThread::sleep_for(std::chrono::milliseconds(5000));
//     }

//     return 0;
// }

// void usbthread(){
//     USBMSD usb(&bd);
//     while(1){
//         usb.process();
//     }
// }