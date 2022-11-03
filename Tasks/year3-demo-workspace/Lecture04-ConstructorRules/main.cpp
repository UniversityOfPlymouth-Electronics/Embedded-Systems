#include <iostream>
#include <memory>
#include "AandB.hpp"
using namespace std;

// TURN ON ALL WARNINGS -Wall

template<class T, int N>
class MyData
{
    public:
    T* pointerToData;
    MyData() : pointerToData(nullptr) {
        pointerToData = new T[N];
    }
    ~MyData() {
        if(pointerToData) {
            delete [] pointerToData;
        }
    }

};

void doSomething(double x)
{
    MyData<double, 64> p;

    if (x==0.0) {
        return;
    }

    for (unsigned int n=0; n<64; n++) {
        p.pointerToData[n] = x;
    }

    std::cout << "Done" << std::endl;

}

int main()
{
    C someObj(99);
    someObj.func();

    doSomething(0.0);

    return 0;
}