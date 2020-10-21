#include "mbed.h"

#include <iostream>
#include "CHuman.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    //This looks the same?
    CHuman person1(35, 80.0, 1.81);
    
    //Display
    person1.display();
    
    //Designated initialiser
    CHuman person2 = CHuman(45, 97.0, 1.9);
    cout << person2 << endl;
    
    //Update
    person2.updateWeight(85.0);
    cout << person2 << endl;
    
    //Accessor
    float h2 = person2.height();
    cout << h2 << endl;
    
    //Try this
    //person2._height = 0.0;
    return 0;
}
