#include "mbed.h"

#include "Cat.hpp"
#include "Dog.hpp"
#include "RoboDog.hpp"

DigitalIn blueButton(USER_BUTTON);

int main()
{

    //Dynamic Allocation and Polymorphism
    Dog* doggy1;
    Dog* doggy2;

    doggy1 = new Dog("Slasher");

    if (blueButton == 1) {
        doggy2 = new Dog("Fido");
    } else {
        doggy2 = new RoboDog("Buzzer");
    }
    
    doggy1->woof();
    doggy2->woof();

    delete doggy1;
    delete doggy2;

    sleep();
}

