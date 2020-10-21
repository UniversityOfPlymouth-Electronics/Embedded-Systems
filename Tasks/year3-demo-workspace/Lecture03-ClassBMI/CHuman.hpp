//
//  Human.hpp
//  CPPClasses
//
//  Created by Nicholas Outram on 28/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef Human_hpp
#define Human_hpp

#include <stdio.h>
#include <iostream>

class CHuman {
    
private:
    //Private Properties
    unsigned int _age;
    float _weight;
    float _height;
    float _bmi;
    bool _needsUpdate;
    
public:
    CHuman(int age, float weight, float height);
    void display();
    //Read only Accessors
    float height();
    float weight();
    float bmi();
    //Write accessors
    float updateWeight(double);
    float updateHeight(double);
    friend std::ostream& operator << (std::ostream& os, CHuman& h);

private:
    //Private member function (aka "method")
};

#endif /* Human_hpp */
