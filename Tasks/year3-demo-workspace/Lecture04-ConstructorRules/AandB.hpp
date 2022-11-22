#pragma once

#include <iostream>
using namespace std;

class P
{
    private:
    int32_t parentData;
    public:
    P() : parentData(100) {
        cout << "Parent " << parentData << endl;
    }
    P(int u) {
        cout << "P says " << u << endl;
        parentData = u;
    }
    virtual void display() = 0;    
};

class C : public P
{
    private:
    int32_t childData;
    public:
    C() : childData(200) {
        cout << "Child " << childData << endl;
    }
    C(int a) : P(a), childData(a)  {
        cout << "Child with " << a << endl;
    }
    virtual void display() {
        cout << "Class C " << childData << endl;
    }
};


