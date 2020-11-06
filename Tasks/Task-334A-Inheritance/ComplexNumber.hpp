#ifndef __COMPLEX_NUMBER__
#define __COMPLEX_NUMBER__
#include "DoubleNumber.hpp"

class ComplexNumber : public DoubleNumber {
private:

protected:
    double _imag;

public:
    ComplexNumber(double r, double i) : DoubleNumber(r) {
        _imag = i;
        cout << "This is the constructor of the sub-class" << endl;
    }
    
    ComplexNumber() : ComplexNumber(0.0, 0.0) { }

    // ComplexNumber& operator=(double u) {
    //     DoubleNumber::operator=(u);
    //     return *this;
    // }

    // ComplexNumber& operator=(ComplexNumber& u) {
    //     DoubleNumber::operator=(u);
    //     return *this;
    // }

};

#endif