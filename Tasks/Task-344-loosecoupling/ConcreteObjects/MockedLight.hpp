#ifndef __MOCKEDLIGHT__
#define __MOCKEDLIGHT__
#include <iostream>
#include "ILightNotify.hpp"

using namespace std;

class MockedLight : public ILightNotify {
    private:
    bool state = false;
    string ID;

    public:
    MockedLight(string ID, bool initialState = false) : ID(ID) {
        cout << "Mocked Light initialised" << endl;
        state = initialState;
    }

    virtual void lightOn() { 
        cout << "LIGHT " << ID << "ON" << endl; 
        state = true; 
    };
    virtual void lightOff() { 
        cout << "LIGHT " << ID << "OFF" << endl; 
        state = false; 
    };
    virtual bool lightStatus() { 
        return state; 
    };
};

#endif