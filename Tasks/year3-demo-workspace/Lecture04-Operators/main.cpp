//#include "mbed.h"     //Uncomment for mbed studio
#include <iostream>
#include "ComplexNumber_C.hpp"
#include "ComplexNumber.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    // C API
    ComplexNumber_C p = { .real = 2.0, .imag = 3.0 };
    ComplexNumber_C q = { .real = 1.0, .imag = 7.0 };
    
    ComplexNumber_C y = complexAdd(p,q);
    displayComplex(y);
 
    complexAddInPlace(&y, p);
    displayComplex(y);

    // C++ API
    ComplexNumber aa(2.0, 3.0);
    ComplexNumber bb(1.0, 4.0);
    ComplexNumber yy = aa + bb;
    
    cout << yy << endl;

    yy[0] = 1.0;            //Set the real part to 0
    yy[1] = 2.0;
    cout << yy << endl;

    return 0;
}

