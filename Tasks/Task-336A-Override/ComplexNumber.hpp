#ifndef __COMPLEX_NUMBER__
#define __COMPLEX_NUMBER__
#include "DoubleNumber.hpp"
#include <string>

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

    ComplexNumber(DoubleNumber& u) : ComplexNumber(u.getValue(), 0.0) {

    }

    //Override magnitude - more expensive than the parent class
    double magnitude() {
        double r = this->_real;
        double i = this->_imag;
        return sqrt(r*r + i*i);
    }

    DoubleNumber& asDoubleNumber() {
        return (DoubleNumber&)*this;
    }

    DoubleNumber realPart() {
        DoubleNumber res(this->_real);
        return res;
    }
    DoubleNumber imagPart() {
        DoubleNumber res(this->_imag);
        return res;
    }

    // Only works on real part
    ComplexNumber& operator=(double u) {
        DoubleNumber::operator=(u);
        return *this;
    }

    // Override the DEFAULT =
    ComplexNumber& operator=(ComplexNumber& u) {
        DoubleNumber::operator=(u);
        this->_imag = u._imag;
        return *this;
    }

    // Override asString
    string asString() {
        return to_string(_real) + " + " + to_string(_imag) + "j";
    }    

    // Override + in the parent class
    ComplexNumber operator+(ComplexNumber& u) {
        ComplexNumber result;

        //TO BE DONE

        return result;
    }
};

#endif