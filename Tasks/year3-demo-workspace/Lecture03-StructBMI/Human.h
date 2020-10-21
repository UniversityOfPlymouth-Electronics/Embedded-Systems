//
//  Human.h
//  CStructures
//
//  Created by Nicholas Outram 
//  Copyright © 2020 Nicholas Outram. All rights reserved.
//

#ifndef Human_h
#define Human_h

#include <stdio.h>
typedef struct {
    unsigned int age;
    float weight;
    float height;
    float bmi;
} Human;

//Private API

//Public API void displayHuman(const Human* h);
extern "C" void displayHuman(const Human* h);
extern "C" Human initHuman(unsigned a, float wt, float ht);
extern "C" unsigned updateAge(Human* h, unsigned aa);
extern "C" float updateHeight(Human* h, float hh);
extern "C" float updateWeight(Human* h, float ww);

#endif /* Human_h */
