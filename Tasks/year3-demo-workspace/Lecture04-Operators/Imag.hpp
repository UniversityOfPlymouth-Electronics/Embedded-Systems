//
//  Imag.hpp
//  Complex
//
//  Created by Nicholas Outram on 22/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef Imag_hpp
#define Imag_hpp

#include <stdio.h>
class Imag {
protected:
    double value;
    
public:
    Imag() {
        value = 0.0;
    }
    
    Imag(double newVal) {
        value = newVal;
    }
    
    //read-only accessor
    double get() const {
        return value;
    }
};
#endif /* Imag_hpp */
