/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#include <cstdint>
#include <functional>
#include <iostream>
#include <array>
#include <utility>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

// Using std::array
// https://www.tutorialspoint.com/cpp_standard_library/array.htm

// Example of using std::array
// A direct replacement for a C Array with very low overhead
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

    cout << "Data Entered:" << endl;

    // Standard array 
    for (uint8_t n=0; n<4; n++) {
        cout << arr[n] << endl;
    }

    cout << "Again - using iterator:" << endl;

    // Iterator based loop (special type of pointer that knows how to traverse the data)
    array<uint32_t,4>::iterator i;
    for (i = arr.begin(); i != arr.end(); i++) {
        cout << *i << endl;
    }

    // Standard library sort - pass iterators to first and last element
    sort(arr.begin(), arr.end());
    cout << "Sorted LOW to HIGH" << endl;

    // Pretty version
    for (auto iter = arr.begin(); iter != arr.end(); iter++) {
        cout << *iter << endl;
    }

    // Sort - high to low
    sort(arr.begin(), arr.end(), std::greater<uint32_t>());
    cout << "Sorted HIGH to LOW" << endl;

    // Range based loop - easiest of all
    for (auto n : arr) {
        cout << n << endl;
    }

    // Value Semantics gets you copy behaviour
    array<uint32_t,4> arr_copy;
    arr_copy = arr;  // DEEP copy (does not work with C arrays!)

    //Wipe the original to prove it works
    for (uint8_t n=0; n<4; n++) {
        arr[n]  = 0;
    }

    cout << "Copies are easy!" << endl;
    for (auto n : arr_copy) {
        cout << n << endl;
    }

    // NOTE - arr is stack based and will go out of scope. The memory will be released as would any other value-type
}

// Example of using std::vector
// Shows how the vector can scale up in size at run-time
// This comes with an overhead of course
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

    // Simple loop 
    cout << "You entered the following:" << endl;
    for (uint8_t n=0; n<vec.size(); n++) {
        cout << vec[n] << endl;
    }    

    // Standard library sort - pass iterators to first and last element
    sort(vec.begin(), vec.end());    


    // Iterator based loop (special type of pointer that knows how to traverse the data)
    cout << "Sorted LOW to HIGH" << endl;
    vector<uint32_t>::iterator i;
    for (i = vec.begin(); i != vec.end(); i++) {
        cout << *i << endl;
    }    

    // Standard library sort - pass iterators to first and last element
    sort(vec.begin(), vec.end(), std::greater<uint32_t>());   

    // Range based loop - easiest of all, using modern safe loop
    cout << "Sorted HIGH to LOW" << endl;
    for (auto n : vec) {
        cout << n << endl;
    }    
}

// Example of using std::map
void demoMap()
{
    //This is the map - a key-value store
    map<uint32_t, string/*, std::greater<uint32_t>*/> myMap;    //Remove block comments to sort highest to lowest
    myMap[143] = "Embedded-Systems in Context";
    myMap[351] = "Advanced Embedded Programming";

    //Another approach
    auto entry = std::pair<uint32_t,string>(240,"Embedded-Systems");
    myMap.insert(entry);

    //Another - with a unique key
    myMap[350] = "Advanced Embedded Programming";

    //Iterate over all members
    for (auto n : myMap) {
        auto str = n.first;
        auto num = n.second;
        cout << "Key: " << str << " ,Value: " << num << endl;
    }

    //Fast lookup using key
    cout << "Title for ELEC351 is " << myMap[351] << endl;

    //Copy and sort HIGH to low
    map<uint32_t, string, std::greater<uint32_t>> sortedMap;
    for (auto n : myMap) {
        sortedMap.insert(n);
    }

    // Display
    cout << "Sorted HIGH to LOW" << endl;
    for (auto n : sortedMap) {
        cout << n.first << " : " << n.second << endl;
    }

}

DigitalIn blueButton(USER_BUTTON);

int main()
{
 
    cout << "Press the BLUE button" << endl;
    while (blueButton == 0);

    sort4Bytes();    //Experiment 1 - uncomment and step into this function
    // sortNBytes();    //Experiment 2 - uncomment and step into this function
    // demoMap();       //Experiment 3 - uncomment and step into this function


}
