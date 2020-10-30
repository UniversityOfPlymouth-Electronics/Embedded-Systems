#include "mbed.h"
#include "ComplexNumber.hpp"

//Friend function (not always considered great practise)
void wipe(ComplexNumber& c)
{
    c.real = 0.0;
    c.imag = 0.0;
}

// main() runs in its own thread in the OS
int main()
{
 
    ComplexNumber c1(2.0,3.0);
    ComplexNumber c2(1.0,-1.0);

    //c1.add(c2);   //c1 = c1 + c2
    c1+=c2;

    //ComplexNumber c3 = c1.addedTo(c2);
    ComplexNumber c3 = c1 + c2;
    ComplexNumber c4 = c1.operator+(c2);

    double mag = c4;

    c3.conjugate();
    c3.display();


    c3 = 1.0;

    //Create new scope
    {
        ComplexNumber test(1.0);
        test.display();
        wipe(test);
        test.display();
    }
    //test is now out of scope and should be destroyed

    while (true);
}

