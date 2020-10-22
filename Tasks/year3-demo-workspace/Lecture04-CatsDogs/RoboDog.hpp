//
//  RoboDog.hpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef RoboDog_hpp
#define RoboDog_hpp

#include <iostream>
#include "Dog.hpp"

using namespace std;

class RoboDog : public Dog
{
protected:
    float batteryLevel;
public:
    RoboDog(string name);
    void recharge();
    float getBatteryLevel();
    void woof();
};
#endif /* RoboDog_hpp */
