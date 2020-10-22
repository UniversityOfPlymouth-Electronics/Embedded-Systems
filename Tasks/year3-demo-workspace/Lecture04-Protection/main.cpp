#include "mbed.h"

#include <iostream>

class Base
{
public:
    int pub;
protected:
    int prot;
private:
    int priv;
};

class PublicChild : public Base
{
    // pub is public
    // prot is protected
    // priv is not accessible from B
};

class ProtectedChild : protected Base
{
    // pub is protected
    // prot is protected
    // priv is not accessible from B
};

class PrivateChild : private Base    // 'private' is default for classes
{
    // pub is private
    // prot is private
    // pric is not accessible from D
};

int main(int argc, const char * argv[]) {
    
    Base baseObject;
    baseObject.pub = 10;
    
    return 0;
}


