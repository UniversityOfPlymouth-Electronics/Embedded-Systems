#include "mbed.h"

class Base {
    private:
    int _val;

    public:
    Base(int u) {
        _val = u;
    }

    int read() {
        return _val;
    }

    Base& operator=(int v) {
        _val = v;
        return *this;
    }

    void operator=(double v) {
        _val = (int)v;
    }
};

class Child : public Base {
    public:
    Child(int v) : Base(v) {
        printf("Hello\n");
    }
};

// main() runs in its own thread in the OS
int main()
{
    while (true) {

    }
}

