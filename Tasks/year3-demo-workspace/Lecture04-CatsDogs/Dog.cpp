//
//  Dog.cpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#include "Dog.hpp"

Dog::Dog(string name) : Pet(name)
{ }

//Overload the constructor
Dog::Dog() : Dog("Fido")
{

}

void Dog::woof() {
    cout << this->name << " says woof!" << endl;
}

//Overloaded version of woof
void Dog::woof(string snd) {
    cout << this->name << snd << endl;
}
