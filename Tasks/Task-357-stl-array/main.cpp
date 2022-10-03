#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

// Using std::array
// https://www.tutorialspoint.com/cpp_standard_library/array.htm

void sortBytes()
{
    uint32_t u;
    array<uint32_t,4> arr;
    for (unsigned int n=0; n<4; n++) {
        cout << endl << "Enter value: " << n << ": ";
        cin >> u;
        arr[n] = u;
    }
    cout << endl;
    
    // Standard library sort - pass iterators to first and last element
    sort(arr.begin(), arr.end());

    // Output by iteration
    for (auto n : arr) {
        cout << n << endl;
    }

}

int main()
{
    sortBytes();
    return 0;
}