#include "mbed.h"

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

