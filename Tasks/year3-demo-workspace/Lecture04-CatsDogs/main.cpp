#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"
#include "RoboDog.hpp"
using namespace std;

namespace Mbed_Simulated_UoP {
    #define USER_BUTTON "USER_BUTTON"
    class DigitalIn {
        public:
        typedef enum {RANDOM, PRESSED, RELEASED} MODE_t;
        private:
        MODE_t _mode;
        public:
        DigitalIn(string s, MODE_t mode = RANDOM) {
            cout << "Using fake hardware" << endl;
            _mode = mode;
        }
        operator int() {
            int r;
            switch (_mode) {
                case RANDOM:
                r = rand();
                r %= 2;
                break;
                case PRESSED:
                r = 1;
                break;
                case RELEASED:
                r = 0;
                break;
            }
            return r;
        }
        void setMode(MODE_t mode) {
            _mode = mode;
        }
    };
    void sleep() { cout << "CPU Enters sleep mode"<< endl;}

}

// We won't use real hardware for these tests
using namespace Mbed_Simulated_UoP;

// *************** MOCKED DIGITAL INPUT ***************
DigitalIn blueButton(USER_BUTTON, DigitalIn::PRESSED);

int main()
{
    // NOTE - I've used { braces } to create a local scope simply to demonstrate the destructor 

    // Statically instantiate a Dog and Cat
    {
        Dog dog1("Mr Sizzles");
        Cat cat1("Mrs MoonCat");
        dog1.woof();
        cat1.meow();

        //OVERLOADING EXAMPLE
        dog1.woof(" says Yip Yip");
    }

    // ************
    // OVERRIDING *
    // ************
    
    //Statically instantiate a RoboDob
    {
        RoboDog robby("Beeper");
        robby.woof();               // The behaviour is "overridden"
        robby.recharge();           // This only exists in RoboDog
    }

    // Dynamic Allocation
    Dog* dog1 = new Dog("Ms Waggy Tail");
    if (dog1 == nullptr) {
        cout << "Memory allocation failure";
        return -1;
    }
    dog1->woof();   //Note that dog1 is a POINTER type (excuse pun)
    
    // TIP! Using a reference to make code look pretty
    Dog& doggyAlias = *dog1;    // De-reference dog1 (to a value) - make doggyAlias a reference to this
    doggyAlias.woof();          // Looks nicer

    //Now free up the memory
    delete dog1; 
    dog1 = nullptr; //Just in case

    // ****************************************
    // OVERRIDING behaviour with Polymorphism *
    // ****************************************
    Dog* doggy1;        //Type Dog*
    Dog* doggy2;        //Also type Dog*

    doggy1 = new Dog("Slasher");

    // Which type is actually newed up depends on the user
    if (blueButton == 0) {
        doggy2 = new Dog("Fido");
    } else {
        // Newing up a subclass of Dog
        doggy2 = new RoboDog("Buzzer");
    }
    
    // EXPERIMENT
    // Try this once - then again while making woof() virtual in Dog.hpp
    doggy1->woof();
    doggy2->woof();

    // QUESTION - Why can we not do the following?
    // doggy2->recharge(); //This line will not compile

    // *************
    // DANGER ZONE *
    // *************

    //If you are REALLY SURE - you can force a type cast
    if (blueButton == 1) {
        RoboDog* thisCouldGoBang = (RoboDog*)doggy2;    //Compiler cannot save you now
        thisCouldGoBang->recharge();
    }

    delete doggy1;
    delete doggy2;

    sleep();
}

