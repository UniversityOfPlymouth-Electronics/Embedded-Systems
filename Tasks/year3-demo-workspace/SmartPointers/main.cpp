#include <iostream>
#include <memory>
using namespace std;

// https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170
// https://learn.microsoft.com/en-us/cpp/standard-library/memory?view=msvc-170

/*
 "In modern C++, raw pointers are only used in small code blocks of limited scope, loops,
 or helper functions where performance is critical and there is no chance of confusion about ownership."
 https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170

*/

/*
For examples of unique_ptr, see this:

https://learn.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-unique-ptr-instances?view=msvc-170
*/

float getUserResponse()
{
    int16_t N;
    do {
        cout << "How many values do you have? (1..10)" << endl;
        cin >> N;
    } while ((N<1) || (N>10));

    unique_ptr<float[]> pData(new float[N]);
    //auto pData = make_unique<float[]>(N);    //Alternative
    if (pData == nullptr) return 0.0f;

    float fNext;
    for (unsigned n=0; n<N; n++) {
        cout << "Enter value " << n << endl;
        cin >> fNext;
        pData[n] = fNext;
    }

    //Some calculation
    float y=0.0f;
    for (unsigned n=0; n<N; n++) {
        y = y + pData[n]*pData[N-n-1];
    }

    //Return result - data is released when pData goes out of schope
    return y;
}

int main()
{
    cout << "Smart Pointer Demo" << endl;

    float y = getUserResponse();
    cout << "y = " << y << endl;


    return 0;
}