#pragma once
#include "MPU6050.h"
#include <iostream>

class DataObject {
    private:
    float light;
    float pot;

    public:
    DataObject() : light(0.0f), pot(0.0f) {
        cout << "Parameterless Constructor Called. Warning - not initialised" << endl; 
    }
    DataObject(float light_, float pot_) : light(light_), pot(pot_) {
        cout << "Constructor called: light=" << light << " pot=" << pot << endl;
    }
    ~DataObject() {
        cout << "Destructor called: light=" << light << " pot=" << pot << endl;
    }
    void setLight(float l) { light = l;}
    void setPot(float p) { pot = p; }
    void display() {
        cout << "Display: light=" << light << " pot=" << pot << endl;
    }

};
