//
//  main.cpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#include "Cat.hpp"
#include "Dog.hpp"
#include "RoboDog.hpp"

int main()
{
    Dog* doggy1;
    Dog* doggy2;

    doggy1 = new Dog("Slasher");
    doggy2 = new RoboDog("Zapper");

    doggy1->woof();
    doggy2->woof();

    delete doggy1;
    delete doggy2;
    
}
