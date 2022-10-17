#include "uop_msb.h"
#include "DataObject.hpp"
#include "mbed_mem_trace.h"

#include <iostream>
using namespace std;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
AnalogIn pot(AN_POT_PIN);
AnalogIn ldr(AN_LDR_PIN);

#define N 10

uint32_t print_memory_info() { 
    // Grab the heap statistics
    mbed_stats_heap_t heap_stats;
    mbed_stats_heap_get(&heap_stats);
    cout << "Heap size: " << heap_stats.current_size << " / " << heap_stats.reserved_size << " bytes" << endl;
    return heap_stats.current_size;
}

int main()
{
    //Not how much heap space we have at the start
    print_memory_info();

    // ********* TEST 1 - SINGLE OBJECT *********
    cout << "********* TEST 1 - SINGLE OBJECT *********" << endl;
    
    //Create single object on the heap (expensive)
    uint32_t memAtStart = print_memory_info();
    DataObject *pObj = new DataObject(1.0f, 2.0f);

    //Invoke class functions via the pointer
    pObj->display();
    //How much memory has been used
    print_memory_info();
    //Free up memory with delete (not delete [])
    delete pObj;
    cout << "Memory should now be returned" << endl;
    print_memory_info();

    // ********* TEST 2 - ARRAY OF OBJECTS *********
    cout << "********* TEST 2 - ARRAY OF OBJECTS *********" << endl;    

    //Repeat forever
    while (true) 
    {
        //Create an Array of type DataObject
        DataObject *buffer = new DataObject[N];
        if (!buffer) {
            cout << "Not enough memory" << endl;
            wait_us(5000000);
            system_reset();
        }

        for (unsigned int n=0; n<N; n++) {
            //Read the ADC     
            float fPot = pot;
            float fLDR = ldr;    

            //Insert data    
            buffer[n].setLight(ldr);
            buffer[n].setPot(pot);

            //Output heart beat
            led1 = !led1;
            wait_us(50000);
        } //End for

        //Iterate over the array
        for (unsigned int n=0; n<N; n++) {
            buffer[n].display();
        }

        //Free up the memory
        cout << "Memory before deallocating" << endl;
        print_memory_info();
        delete [] buffer;
        buffer = nullptr;
        
        //Let's see if all the memory has been returned
        cout << "Memory after deallocating" << endl;
        uint32_t memAtEnd = print_memory_info();

        //Check
        if (memAtStart != memAtEnd) {
            cout << "MEMORY LEAK!" << endl;
            wait_us(5000000);
            system_reset();
        } else {
            cout << "MEMORY OK" << endl;
        }
        wait_us(1000000);

    } //end while
    return 0;
}



