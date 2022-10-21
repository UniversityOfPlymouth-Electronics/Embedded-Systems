//
//  Dog.hpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef Dog_hpp
#define Dog_hpp

#include "Pet.hpp"
#include <iostream>
using namespace std;

class Dog : public Pet
{
public:
    Dog();
    Dog(string name);

    // ** EXPERIMENT **
    // Make woof virtual and rerun the demo with the switch pressed
    /*virtual*/ void woof();

    void woof(string);  //Overloaded
};

#endif /* Dog_hpp */
