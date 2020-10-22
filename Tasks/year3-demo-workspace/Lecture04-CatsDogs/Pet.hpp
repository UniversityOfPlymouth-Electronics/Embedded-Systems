//
//  Pet.hpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef Pet_hpp
#define Pet_hpp

#include <iostream>
using namespace std;

class Pet {
protected:
    string name;
public:
    Pet(string name);
    void eat();
    string getName();
};
#endif /* Pet_hpp */
