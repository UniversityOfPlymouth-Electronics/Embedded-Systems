//
//  Pet.hpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef Pet_hpp
#define Pet_hpp
#include "Entity.hpp"
#include <iostream>
using namespace std;

// class Pet : Entity {     //uncomment this for pure-virtual demo
class Pet {
protected:
    string name;
public:
    Pet(string name);
    ~Pet() { cout << this->name << "Says Bye" << endl; }
    void eat();
    string getName();
    // void doThisPV() {
    //     cout << "doThisPV() in Pet" << endl;
    // }
};
#endif /* Pet_hpp */
