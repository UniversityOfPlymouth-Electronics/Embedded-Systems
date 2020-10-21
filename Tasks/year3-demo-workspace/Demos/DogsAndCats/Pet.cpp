//
//  Pet.cpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#include "Pet.hpp"
Pet::Pet(string name){
    this->name = name;
}

void Pet::eat() {
    cout << this->name << " is eating." << endl;
}

string Pet::getName(){
    return this->name;
}
