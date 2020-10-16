//
//  ComplexNumber_C.c
//  Complex
//
//  Created by Nicholas Outram on 21/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#include "ComplexNumber_C.hpp"

void doIt() {
    printf("Hello\n");
}

ComplexNumber_C complexAdd(const ComplexNumber_C a, const ComplexNumber_C b) {
    double r = a.real + b.real;
    double i = a.imag + b.imag;
    ComplexNumber_C result = { .real = r, .imag = i};
    return result;
}

void complexAddInPlace(ComplexNumber_C* a, const ComplexNumber_C b) {
    a->real += b.real;
    a->imag += b.imag;
}

void displayComplex(const ComplexNumber_C c) {
    printf("%f + %fj\n", c.real, c.imag);
}

