#pragma once

#include <iostream>
using namespace std;

class P
{
    public:
    P() {
        cout << "Parent" << endl;
    }
    P(int u) {
        cout << "P says " << u << endl;
        func(u);
    }
    virtual int func(int a) = 0;
};

class C : public P
{
    private:
    int32_t stuff;
    public:
    C() {
        cout << "Child" << endl;
    }
    //Hideous bug alert! stuff is NOT initialised
    C(int a) : stuff(a), P(a)  {
        cout << "Child with " << a << endl;
    }
    virtual int func(int a=10);
};