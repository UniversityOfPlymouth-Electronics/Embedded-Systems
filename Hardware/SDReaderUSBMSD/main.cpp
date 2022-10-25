/*
 *  Example code for mounting an SD card or a portion of heap memory
 *  and allowing it to be viewed as a mass storage device on a PC.
 *  Adapted from https://os.mbed.com/docs/mbed-os/v6.15/apis/usbmsd.html
 */

/************************SD Card as MSD****************************/


 /*  Uncomment the section you wish to test and run the code with an 
 *  SD card containing files in the holder
 *  Connect the USB port next to the Ethernet port to a PC with a second
 *  micro-USB cable. The SD contents should be displayed as a USB device.
 */


#include "mbed.h"
#include "SDBlockDevice.h"
#include "USBMSD.h"
#include <chrono>


SDBlockDevice sd(PB_5, PB_4, PB_3, PF_3);

Thread th;

void usbthread(){
    // This thread will block until a connection is made
    USBMSD usb(&sd);
    while(1){
        usb.process();
    }
}


int main()
{
    th.start(usbthread);
    th.join();

    return 0;
}






/************************Heap memory as MSD****************************/

/*
    Files which are present in the HeapBlockDevice file system when the USB cable is inserted
    will appear as a mass storage device. If you disconnect and reconnect the cable, the 
    contents will update
*/

// #include "mbed.h"
// #include "USBMSD.h"
// #include "FATFileSystem.h"
// #include <chrono>


// #define DEFAULT_BLOCK_SIZE  512
// #define HEAP_BLOCK_DEVICE_SIZE (128 * DEFAULT_BLOCK_SIZE)

// FATFileSystem heap_fs("heap_fs");
// HeapBlockDevice bd(HEAP_BLOCK_DEVICE_SIZE, DEFAULT_BLOCK_SIZE);
// Thread th;

// //Function prototypes
// void usbthread();

// int main()
// {
//     // initialise the Block Device
//     bd.init();

//     // Link the Blockdevice to the filesystem
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

//     // Creation of USBMSD object causes the thread to block until a cable is connected
//     // Placing it in it's own thread allows you to do other stuff while this occurs
//     th.start(&usbthread);
    
//     int counter=0;

//     // Adding dummy data at regular intervals;
//     while (true) {
//         //Create a filename and open to "append"
//         char filename[32];
//         sprintf(filename,"/heap_fs/test%d.txt",counter);
//         FILE *fp = fopen(filename, "a");
//         if(fp == NULL) {
//             error("Could not open file for write\n");
//         }

//         //Add some data into the file
//         char buf[32];
//         sprintf(buf,"Hello Heap storage device! %d\r\n",counter);
//         fprintf(fp, buf);

//         //Close the file
//         fclose(fp); 

//         //Wait some time before next file write
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