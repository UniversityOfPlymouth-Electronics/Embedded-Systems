//
//  Cat.cpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#include "Cat.hpp"

Cat::Cat(string name) : Pet(name)
{ }

void Cat::meow() {
    cout << this->name << " says meow!" << endl;
}
