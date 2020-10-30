//
//  Entity.hpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 04/12/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class Entity {
private:
    unsigned int yearOfCreation;
public:
    virtual void doThisV();         //Ordinary virtual function
    virtual void doThisPV() = 0;    //Pure virtual
};

#endif /* Entity_hpp */
