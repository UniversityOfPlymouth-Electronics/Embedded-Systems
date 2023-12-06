#include "mbed.h"
#include "stdio.h"
#include <iostream>


MemoryPool<int, 3> mpool; //  3 instances of type int may be stored here

// functions
void fill_array(int depth, int* array);


// comparing the use of new/free and memory pools //

// the program allows user to input desired array depth
// then fills it with even numbers and displays it on the terminal


int main()
{

    // dynamic memory alloc using new/free 

    int depth;
    printf("Input array size: \n");
    std::cin >> depth;
 

    int* array1 = new int[depth];
    if (array1 == nullptr) {

        printf("Error: not enough memory on heap!\n");
        return -1;
    }
    else {

        fill_array(depth, array1);
    }


    // dynamic memory alloc using MemoryPool

    int* array2 = mpool.try_alloc();
    if (array1 == nullptr) {

        printf("Error: memory pool full\n");
        return -1;
    }
    

    // then what?
    // how can I use 'depth' here to achieve the same result as above?

   
}



void fill_array(int depth, int* array) {

    for (int i=0; i<depth; i++) {

        *(array + i) = 2*i; // showcase the different syntax
        printf("%d\n", array[i]);
    }

}

