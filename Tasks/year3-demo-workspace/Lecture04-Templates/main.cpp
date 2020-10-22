#include "mbed.h"

#include <iostream>

namespace ELEC35X {
    int max(int a, int b)
    {
        if (a>=b) {
            return a;
        } else {
            return b;
        }
    }
    
    float max(float a, float b)
    {
        if (a>=b) {
            return a;
        } else {
            return b;
        }
    }
    
}
namespace WITHTEMPLATE {
    
    template <typename T>
    T max(T a, T b)
    {
        if (a >= b) {
            return a;
        } else {
            return b;
        }
    }
    
}

class MyObject {
private:
    long value;
public:
    long operator >= (long u) {
        if (u >= this->value) {
            return u;
        } else {
            return this->value;
        }
    }
    operator long() {
        return this->value;
    }
    
    MyObject(long u) {
        this->value = u;
    }
    
};

using namespace std;
//using namespace ELEC35X;
int main(int argc, const char * argv[]) {
    long u=10, v = 20;
    cout << WITHTEMPLATE::max(u,v) << endl;
    cout << WITHTEMPLATE::max(4.0f, 5.0f) << endl;
    MyObject a(56);
    MyObject b(45);
    cout << WITHTEMPLATE::max(a,b) << endl;
    return 0;
}


