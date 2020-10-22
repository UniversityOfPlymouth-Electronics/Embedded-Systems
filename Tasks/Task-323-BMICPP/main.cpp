#include "mbed.h"

#include <iostream>
#include "CHuman.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    //Create object
    CHuman person(45, 97.0, 1.9);
    //CHuman person = CHuman(45, 97.0, 1.9); //Designated initialiser (alternative method)

    //Call member function display
    person.display();

    //Use C++ stream (equivalent to printf) to write object to serial monitor
    cout << person << endl;
    
    //Update property
    person.updateWeight(85.0);
    cout << person << endl;
    
    //Read-only accessor
    float h2 = person.getHeight();
    cout << h2 << endl;
    
    //Try uncomenting this
    //person._height = 0.0;
    return 0;
}

