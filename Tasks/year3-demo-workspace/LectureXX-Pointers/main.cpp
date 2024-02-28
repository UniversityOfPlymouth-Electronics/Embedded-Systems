#include <iostream>
#include <functional>
using namespace std;

int main()
{
    cout << "Good Morning" << endl;

    int16_t array[8];

    cout << "How many?" << endl;
    int N;
    cin >> N;
    int32_t* address = new int32_t[N];  
    cout << address << endl;
    address[0] = 10;
    *address = 10;

    address[1] = 20;
    *(address+1) = 20;
    
    cout << address << endl;
    cout << (address+1) << endl;

    return 0;
}