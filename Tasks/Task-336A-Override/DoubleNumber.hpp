#ifndef __DOUBLE_NUMBER__
#define __DOUBLE_NUMBER__

#include "mbed.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
using namespace std;

class DoubleNumber {
private:

protected:
    double _real;

public:
    //Designated constructor
    DoubleNumber(double r) {
        _real = r;
        cout << "This is the constructor of Base" << endl;
    }

    //Convenience constructor
    DoubleNumber() : DoubleNumber(0.0) { }

    //Copy constructor
    DoubleNumber(const DoubleNumber& u) {
        this->setValue(getValue());
    }

    //Magnitude
    double magnitude() {
        return fabs(_real);
    }

    //Three overloaded functions
    void setValue(double u) {
        _real = u;
    }
    void setValue(int u) {
        _real = (double)u;
    }
    void setValue(string strVal) {
        _real = stod(strVal);
    }
    void setValue(DoubleNumber& u) {
        this->setValue(u.getValue());
    }

    double getValue() {
        return _real;
    }

    string asString() {
        return to_string(_real);
    }

    // OVERLOADED OPERATORS
    void operator+=(double u) {
        double sum = this->getValue() + u;
        this->setValue(sum);
    }
    void operator+=(DoubleNumber& u) {
        double sum = this->getValue() + u.getValue();
        this->setValue(sum);
    }
    DoubleNumber operator+(DoubleNumber& u) {
        DoubleNumber result;
        result = *this;
        result += u;
        return result;
    }

    // For simplicity, I have changed the return type to void
    // This simply means we cannot chain these together
    DoubleNumber& operator=(double u) {
        this->setValue(u);
        return *this;
    }
    DoubleNumber& operator=(DoubleNumber& u) {
        this->setValue(u.getValue());
        return *this;
    }
    DoubleNumber& operator=(string s) {
        this->setValue(s);
        return *this;
    }

    //The following is "slightly dodgy!"
    bool operator==(DoubleNumber& u)
    {
        if ( fabs(this->getValue() - u.getValue()) < 0.000001 ) {
            return true;
        }
        return false;
    }

    operator double() {
        return _real;
    }

};

#endif