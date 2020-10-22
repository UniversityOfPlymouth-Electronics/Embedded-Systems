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

class Entity {
private:
    unsigned int yearOfCreation;
public:
    virtual void doThisV();
    virtual void doThisPV() = 0;
};

#endif /* Entity_hpp */
