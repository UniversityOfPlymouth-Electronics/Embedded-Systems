#include "mbed.h"

#include <iostream>
#include "CHuman.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    //Static allocation
    CHuman person1(35, 80.0, 1.81);
    
    //Display
    person1.display();
    
    //Designated initialiser
    CHuman person2(45, 97.0, 1.9);
    cout << person2 << endl;
    
    //Update
    person2.updateWeight(85.0);
    cout << person2 << endl;
    
    //Accessor
    float h2 = person2.height();
    cout << h2 << endl;
    
    //Try this
    //person2._height = 0.0;

    //Dynamic Memory Allocation
    CHuman* person3 = new CHuman(50, 85.0, 1.9);
    if (person3 == nullptr) {
        cout << "Failed to allocate memory";
        return -1;
    }

    //Invoke a member function
    person3->display();

    //Free up memory
    delete person3;
    person3 = nullptr;

    //Error - do not do this!
    //person3->display();

    return 0;
}
