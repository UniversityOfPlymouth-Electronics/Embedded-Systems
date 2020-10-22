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
#include "Imag.hpp"

class ComplexNumber {
private:
    double real;
    double imag;
    
    void copy(const ComplexNumber& c) {
        real = c.real;
        imag = c.imag;
    }
    
public:
    //Default constructor
    ComplexNumber() {
        real = 0.0;
        imag = 0.0;
    }
    
    //Constructor 2
    ComplexNumber(const double r, const double i=0.0) {
        real = r;
        imag = i;
    }
    
    //Copy constructors
    ComplexNumber(const ComplexNumber& c) {
        copy(c);
    }
    ComplexNumber(const Imag& c) {
        real = 0.0;
        imag = c.get();
    }


    //Create a new copy without using a constructor
//    ComplexNumber& operator = (const Imag& c) {
//        ComplexNumber *cc = new ComplexNumber();
//        cc->imag = c.get();
//        return *cc;
//    }
    
    //Conjugate - verb, so perform in place
    void conjugate() {
        imag *= -1.0;
    }
    
    //Conjugated - adjective, so return new copy
    ComplexNumber conjugated() {
        return ComplexNumber(real, -1.0*imag);
    }
    
    //Override equals
    void operator = (const ComplexNumber& c) {
        copy(c);
    }

    //Add in place
    void operator += (const ComplexNumber& c) {
        real += c.real;
        imag += c.imag;
    }
    
    //Add
    ComplexNumber operator + (const ComplexNumber& c) {
        return ComplexNumber(real+c.real, imag+c.imag);
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
