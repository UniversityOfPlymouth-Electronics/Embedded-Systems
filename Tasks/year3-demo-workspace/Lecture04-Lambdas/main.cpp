#include "mbed.h"
#include <cstdlib>
#include <functional>
#include <iostream>
#include "../../lib/uopmsb/uop_msb_2_0_0.h"
using namespace uop_msb_200;

// The author would like to acknowledge the following helpful article!
// https://www.cprogramming.com/c++11/c++11-lambda-closures.html

//Takes a lambda as a parameter
void doSomething(std::function<void(int)> f, int N)
{
    for (int n=0; n<N; n++) {
        f(n);
    }
}

//Currying - returns an initialised lambda that captures a double by value 
std::function<double(double)> accumulator(double initValue)
{
    //This is the variable that is captured
    double acc = initValue;
    //Captures by value [=]
    auto f = [=](double v) mutable {
        acc += v;
        return acc;
    };
    return f;
}

//Global with Function type
std::function<int(int,int)> fn;

int main()
{

    //Local lambda
    auto fred = [] () {
        std::cout << "I am Fred" << std::endl; 
    };

    //Call as you would a separate function 
    fred();

    //Assign a typed global. The return type declaration is optional
    fn = [] (int a, int b)->int {
        return a+b;
    };

    auto f1 = [] (int a) {
        std::cout << a << std::endl;
    };

    auto f2 = [] (int a) {
        std::cout << a*a << std::endl;
    };

    //Pass these functions as parameters
    doSomething(f1, 5);
    doSomething(f2, 3);

    //Currying example
    auto fc1 = accumulator(0.0);    //Captures 0.0
    auto fc2 = accumulator(10.0);   //Captures 10.0

    std::cout << fc1(5.0) << std::endl; 
    std::cout << fc2(1.0) << std::endl;

    while (true) {

    }
}

