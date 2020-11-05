#include "DoubleNumber.hpp"
#include "ComplexNumber.hpp"


int main()
{
    //Constructor Function overloading 
    ComplexNumber c0(1.0, 2.0);
    DoubleNumber  d0(3.0);
    ComplexNumber c1;
    DoubleNumber  d1;

    d1 = 10.0;
    (DoubleNumber)c1 = d1;  //Type cast and = returns type DoubleNumber&
    
    // Note how this works with both types, but only on the real parts
    DoubleNumber sum = c0 + c1 + d0 + d1;
    cout << sum << endl;

    while (true) {

    }
}

