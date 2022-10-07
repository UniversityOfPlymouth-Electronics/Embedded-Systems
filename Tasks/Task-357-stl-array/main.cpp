#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

// Using std::array
// https://www.tutorialspoint.com/cpp_standard_library/array.htm

void sort4Bytes()
{
    uint32_t u;
    array<uint32_t,4> arr;

    // Get data from user
    cout << "Please provide 4 values." << endl;
    for (uint8_t n=0; n<4; n++) {
        cout << endl << "Enter value: " << n << ": ";
        cin >> u;
        arr[n] = u;
    }
    cout << endl;
    
    // Standard library sort - pass iterators to first and last element
    sort(arr.begin(), arr.end());

    // Standard array 
    for (uint8_t n=0; n<4; n++) {
        cout << arr[n];
    }

    // Iterator based loop (special type of pointer that knows how to traverse the data)
    array<uint32_t,4>::iterator i;
    for (i = arr.begin(); i != arr.end(); i++) {
        cout << *i << endl;
    }

    // Pretty version
    for (auto iter = arr.begin(); iter != arr.end(); iter++) {
        cout << *iter << endl;
    }

    // Range based loop - easiest of all
    for (auto n : arr) {
        cout << n << endl;
    }

    // NOTE - no need for delete - arr wll go out of scope and the memory will be released
}

void sortNBytes()
{
    uint32_t u;
    std::vector<uint32_t> vec;

    // Get data from user
    cout << "Please provide values. Enter 0 when finished." << endl;
    do  {
        cout << endl << "Enter value: ";
        cin >> u;
        if (u!=0) {
            vec.push_back(u);   //Add another element (and grow the vector)
        }
        
    } while (u != 0);

    cout << endl;

    // Standard library sort - pass iterators to first and last element
    sort(vec.begin(), vec.end());    

    // Simple loop 
    for (uint8_t n=0; n<vec.size(); n++) {
        cout << vec[n] << endl;
    }    

    // Iterator based loop (special type of pointer that knows how to traverse the data)
    vector<uint32_t>::iterator i;
    for (i = vec.begin(); i != vec.end(); i++) {
        cout << *i << endl;
    }    

    // Range based loop - easiest of all
    for (auto n : vec) {
        cout << n << endl;
    }    
    
}

int main()
{
    //sort4Bytes();
    sortNBytes();
    return 0;
}