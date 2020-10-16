#include "mbed.h"
#include "ComplexNumber_C.hpp"

// main() runs in its own thread in the OS
int main()
{

    ComplexNumber_C p = { .real = 2.0, .imag = 3.0 };
    ComplexNumber_C q = { .real = 1.0, .imag = 7.0 };
    
    ComplexNumber_C y = complexAdd(p,q);
    displayComplex(y);
 
    complexAddInPlace(&y, p);
    displayComplex(y);

    while (true) {

    }
}

