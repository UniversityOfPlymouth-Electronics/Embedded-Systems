//
//  Cat.hpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef Cat_hpp
#define Cat_hpp

#include "Pet.hpp"
#include <iostream>
using namespace std;

class Cat : public Pet
{
public:
    Cat(string name);
    void meow();
};

#endif /* Cat_hpp */
