//
//  RoboDog.cpp
//  DogsAndCats
//
//  Created by Nicholas Outram on 27/11/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#include "RoboDog.hpp"
RoboDog:: RoboDog(string name) : Dog(name) {
    this->batteryLevel = 100.0f;
}

float RoboDog::getBatteryLevel() {
    return this->batteryLevel;
}

void RoboDog::recharge() {
    this->batteryLevel = 100.0f;
    cout << this->name << " has recharged!" << endl;
}

void RoboDog::woof() {
    cout << this->name << " says \"Beepy beepy boing\"" << endl;
    cout << "    I ***never*** say ";
    Dog::woof();
}
