#include "mbed.h"

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        printf("Hello World\n");
        ThisThread::sleep_for(500ms);
    }
}

