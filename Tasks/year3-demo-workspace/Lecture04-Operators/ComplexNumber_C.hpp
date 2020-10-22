//
//  ComplexNumber_C.h
//  Complex
//
//  Created by Nicholas Outram on 21/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef ComplexNumber_C_h
#define ComplexNumber_C_h
#include <stdio.h>

typedef struct {
    double real;
    double imag;
} ComplexNumber_C;

ComplexNumber_C complexAdd(const ComplexNumber_C a, const ComplexNumber_C b);
void complexAddInPlace(ComplexNumber_C* a, const ComplexNumber_C b);
void displayComplex(const ComplexNumber_C c);

#endif /* ComplexNumber_C_h */
