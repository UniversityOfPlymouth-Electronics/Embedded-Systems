#include <stdio.h>
#include "Human.h"

int main(int argc, const char * argv[]) {

    //Create a variable of type human.
    //Human person1 = {.age =35, .weight = 80.0, .height = 1.81};
    Human person1;

    //Initialise properties
    person1.age = 35;
    person1.weight = 80.0;
    person1.height = 1.81;

    //Calculate BMI
    person1.bmi = person1.weight / (person1.height * person1.height);
    
    //Display
    printf("Age: %u, Weight: %f, Height: %f, BMI: %f", person1.age, person1.weight, person1.height, person1.bmi);
    if (person1.bmi>=25.0) {
        printf("*");
    }
    printf("\n");

    // Update weight
    person1.weight = 78.0;

    //Display
    printf("Age: %u, Weight: %f, Height: %f, BMI: %f", person1.age, person1.weight, person1.height, person1.bmi);
    if (person1.bmi>=25.0) {
        printf("*");
    }
    printf("\n");

    // **************** WHAT WENT WRONG ? ****************


    // *****************
    // NOW USING THE API
    // *****************
   
    //Designated initialiser
    Human person2 = initHuman(45, 97, 1.9);
    displayHuman(&person2);
    
    updateWeight(&person2, 75.0);
    displayHuman(&person2);

    return 0;
}


