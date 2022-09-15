// Although not strictly standard, this ensures this include file can only be included once.
#pragma once
#include <iostream>

// Template function to see if a value is significantly larger than the previous value
template<class T>
bool hasIncreasedBy(T next, T delta)
{
    // Remember that the value in a static local is retained (and only initialised the first time)
    static T prev = (T)0;

    T threshold = (prev + delta);
    prev = next;

    //Is the new value significantly larger than the previous?
    if (next > threshold) {
        return true;
    } else {
        return false;
    }

}

// Template function to see if a value is significantly smaller than the previous value
template<class T>
bool hasDecreasedBy(T next, T delta)
{
    // Remember that the value in a static local is retained (and only initialised the first time)
    static T prev = (T)0;

    T threshold = (prev - delta);
    prev = next;

    //Is the new value significantly smaller than the previous?
    if (next < threshold) {
        return true;
    } else {
        return false;
    }
}

