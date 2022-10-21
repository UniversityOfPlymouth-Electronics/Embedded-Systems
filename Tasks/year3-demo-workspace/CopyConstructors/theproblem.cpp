#include <iostream>
using namespace std;

class MyClass {
    private:
    int* a;
    public:
    MyClass(int u) { 
        a = new int[10];
        for (unsigned n=0; n<10; n++) a[n] = u;
    }
    ~MyClass() { 
        delete [] a; 
    }
    void setLast(int u) { a[9]=u; }
    int last() { return a[9]; }
};

int main()
{
    //Create a local scope
    {
        MyClass p1(10);
        MyClass p2(20);
        p2 = p1;    //Copy?
        p2.setLast(0);
        cout << p2.last() << endl;
        cout << p1.last() << endl;
        cout << "Copy Constructors" << endl;
    }
    //How many and which destructors run?

    return 0;
}