#include <iostream>
#include <cstdlib>
#include <functional>
#include <string>
using namespace std;

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

std::function<int()> increment(int initValue, int delta) {
    int acc = initValue;
    auto f = [=]() mutable {
        acc+=delta;
        return acc;
    };
    return f;
}


//Global with Function type
std::function<int(int,int)> fn;



int main()
{
    cout << "Lambda's and Closures" << endl;

    //Local lambda
    auto fred = [] () {
        cout << "I am Fred" << endl; 
    };

    //Call as you would a separate function 
    fred();

    //Assign a typed global. The return type declaration is optional
    fn = [] (int a, int b)->int {
        return a+b;
    };

    //Call with arguments
    int y = fn(2,3);
    cout << "y = " << y << endl;

    //Two similar lambda functions
    auto f1 = [] (int a) {
        cout << a << endl;
    };
    auto f2 = [] (int a) {
        cout << a*a << endl;
    };

    //Pass these functions as parameters
    doSomething(f1, 5);
    doSomething(f2, 3);

    //Currying example
    auto fc1 = accumulator(0.0);    //Captures 0.0 as starting value
    auto fc2 = accumulator(10.0);   //Captures 10.0 as starting value

    cout << fc1(5.0) << endl; 
    cout << fc2(1.0) << endl;

    //Another
    auto ctr = increment(10,2);
    cout << ctr() << endl;
    cout << ctr() << endl;
    cout << ctr() << endl;
    cout << ctr() << endl;

}

