//
//  ComplexNumber.cpp
//  Complex
//
//  Created by Nicholas Outram on 21/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#include "ComplexNumber.hpp"

std::ostream& operator << (std::ostream& os, const ComplexNumber& c)
{
    os << c.real << " + " << c.imag << "j";
    return os; //allows chaining
}

// This would not allow chaining
//void operator << (ostream& os, const ComplexNumber& c)
//{
//    os << c.real << " + " << c.imag << "j";
//}


