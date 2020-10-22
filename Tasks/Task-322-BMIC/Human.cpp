//
//  Human.c
//  CStructures
//
//  Created by Nicholas Outram 
//  Copyright © 2020 Nicholas Outram. All rights reserved.
//

#include "Human.h"

static void calculateHumanBMI(Human* h);

void displayHuman(const Human* h) {
    printf("Age: %u, Weight: %f, Height: %f, BMI: %f", h->age, h->weight, h->height, h->bmi);
    if (h->bmi>=25.0) {
        printf("*");
    }
    printf("\n");
}

static void calculateHumanBMI(Human* h) {
    h->bmi = h->weight / (h->height * h->height);
}

Human initHuman(unsigned a, float wt, float ht) {
    Human hh = {.age = a, .weight = wt, .height = ht};
    calculateHumanBMI(&hh);
    return hh;
}

unsigned updateAge(Human* h, unsigned aa) {
    unsigned prev = h->age;

    //Update property
    h->age = aa;

    return prev;
}

float updateHeight(Human* h, float hh) {
    float prev = hh;

    //Update property
    h->height = hh;

    //Update stale calculated properties
    calculateHumanBMI(h);

    return prev;
}

float updateWeight(Human* h, float ww) {
    float prev = ww;

    //Update property
    h->weight = ww;

    //Update stale calculated properties
    calculateHumanBMI(h);

    return prev;
}
