#include <iostream>
#include <functional>
#include "UsefulClass.h"
using namespace std;

void displayWars() {
    cout << "May the Force be With You" << endl;
}

void displayTrek() {
    cout << "Live Long and Prosper" << endl;
}

typedef void(*proc_t)(void);
typedef double(*arith_t)(int,int);

typedef long double PRECISE_NUMBER;

double addThese(int a, int b)
{
    return (a+b)*0.5;
}

int main()
{
    cout << "Test" << endl;

    //Function pointer to a fuction with no parameters and no return type
    //void(*f)(void);
    proc_t f;

    //Run time decision
    cout << "State you preference:" << endl;
    cout << "0 - Star Wars" << endl;
    cout << "1 - Star Trek" << endl;
    int choice;
    cin >> choice;

    if (choice == 0) {
        f = &displayWars;
    } else {
        f = &displayTrek;
    }
    
    //Invoke
    f();

    auto ff = [](float u) {
        return u*10.0f;
    };
    UsefulClass<float,4> obj(ff);
    obj << 1.0f;
    obj << 2.0f;
    obj << 4.0f;
    obj << 8.0f;
    //obj << 16.0f;
    for (int n=0; n<4; n++) {
        cout << obj[n] << " ";
    }


    return 0;
}