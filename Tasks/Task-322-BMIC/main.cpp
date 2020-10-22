#include "mbed.h"
#include "Human.h"

int main(int argc, const char * argv[]) {


    // ***************
    // USING THE C API
    // ***************
   
    //Designated initialiser
    Human person = initHuman(45, 97, 1.9);
    displayHuman(&person);
    
    //After a major lifestyle change
    updateWeight(&person, 75.0);
    displayHuman(&person);

    return 0;
}


