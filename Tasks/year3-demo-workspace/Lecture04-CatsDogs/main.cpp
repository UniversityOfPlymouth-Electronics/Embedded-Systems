#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"
#include "RoboDog.hpp"
using namespace std;


#define USER_BUTTON "SIM"
class DigitalIn {
    public:
    DigitalIn(string s) {
        cout << "Using fake hardware" << endl;
    }
    operator int() {
        return (rand() % 2) == 0;
    }
};
void sleep() {}

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

