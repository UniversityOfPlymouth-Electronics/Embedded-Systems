#include <iostream>

int x = 5;
double y = 3.14;

namespace MySpace {
    int x = 0;
    double y = 0.0;
    double d2f(int u) {
        return (double)u;
    }
}

// See https://learn.microsoft.com/en-us/cpp/cpp/namespaces-cpp?view=msvc-170

int main()
{
    //This will not compile as it does not know about cout or endl
    //cout << "Now we don't need the std:: scoping operator!" << endl;

    //From the std namespace
    std::cout << x << " " << y << std::endl;

    using namespace std;
    cout << "Now we don't need the std:: scoping operator!" << endl;
    cout << MySpace::x << " " << MySpace::y << endl;
    cout << MySpace::d2f(x) << endl;

    cout << ::x << " " << ::y << endl;                  //Global Scope
    cout << MySpace::x << " " << MySpace::y << endl;    //Namespace Scope
    cout << x << " " << y << endl;                      //(Ambiguous) Global Scope


    return 0;
}