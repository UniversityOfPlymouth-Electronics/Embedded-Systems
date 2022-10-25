//
//  ComplexNumber.hpp
//  Complex
//
//  Created by Nicholas Outram on 21/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef ComplexNumber_hpp
#define ComplexNumber_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>

class ComplexNumber {
private:
    double real;
    double imag;
    
    void copy(const ComplexNumber& c) {
        real = c.real;
        imag = c.imag;
    }
    
public:
    
    //Constructor 1
    ComplexNumber(const double r=0.0, const double i=0.0) {
        real = r;
        imag = i;
    }
    
    //Copy constructor
    ComplexNumber(const ComplexNumber& c) {
        copy(c);
    }

    //Copy operator
    ComplexNumber& operator = (const ComplexNumber& c) {
        real = c.real;
        imag = c.imag;
        return *this;
    }

    //Conjugate - verb, so perform in place
    void conjugate() {
        imag *= -1.0;
    }
    
    //Conjugated - adjective, so return new copy
    ComplexNumber conjugated() const {
        return ComplexNumber(real, -1.0*imag);
    }
    
    //Add in place
    void operator += (const ComplexNumber& c) {
        real += c.real;
        imag += c.imag;
    }
    
    //Add
    ComplexNumber operator + (const ComplexNumber& c) const {
        return ComplexNumber(real+c.real, imag+c.imag);
    }

    //Multiply
    ComplexNumber operator * (const ComplexNumber& c) const {
        return ComplexNumber(real*c.real-imag*c.imag, real*c.imag + imag*c.real);
    }

    //Conversion operator - complex magnitude
    operator double() {
        return sqrt(real*real + imag*imag);
    }

    //Read only - note this is a const function
    double operator[](const unsigned part) const {
        return (part == 0) ? real : imag;
    }
    
    //Set by accessing a reference
    double& operator[](const unsigned part) {
        return (part == 0) ? real : imag;
    }

    //Display
    void display() {
        using namespace std;
        cout << real << " + " << imag << "j" << endl;
    }
    
    //Add support for cout - this is a binary operator, so needs two parameters
    friend std::ostream& operator << (std::ostream& os, const ComplexNumber& c);
};



#endif /* ComplexNumber_hpp */
