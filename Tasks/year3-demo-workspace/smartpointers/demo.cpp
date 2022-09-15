#include <iostream>
#include <memory>
using namespace std;


int main()
{
    cout << "Hello" << endl;

    //Array managed by a smart pointer
    unique_ptr<uint8_t[]> pChars = make_unique<uint8_t[]>(10);
    //auto pChars = make_unique<uint8_t[]>(10);

    //Fill with values
    for (unsigned int n=0; n<10; n++) {
        pChars[n] = '0'+ (uint8_t)n;
    }

    //Read back    
    for (unsigned int n=0; n<10; n++) {
        cout << pChars[n] << endl;
    }


    {
        unique_ptr<uint8_t[]> p1(new uint8_t[10]);
        p1[0]=1;
        for (unsigned int n=1; n<10; n++) {
            p1[n] = p1[n-1]+n;
        }
        cout << p1[10] << endl;

        unique_ptr<uint8_t[]> p2 = std::move(p1);
        
        cout << p1[10] << endl;     //Error!
        cout << p2[10] << endl;
    }

    cout << "Goodbye" << endl;
}
    