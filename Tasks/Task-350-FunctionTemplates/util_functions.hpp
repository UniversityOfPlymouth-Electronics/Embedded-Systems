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

//Function to add a sample to the a circular buffer and return the sum
template<class T, class R, int N>
R addToBuffer(T nextSample)
{
    //Again that static local trick 
    static T buffer[N];
    static T sum = (T)0;
    static int index = 0;

    // Sum is updated - add new sample, subtract oldest
    sum = sum + nextSample - buffer[index];
    buffer[index] = nextSample;     //Overwrite oldest sample
    index = (index + 1) % N;        //Update position of oldest sample
    return (R)sum/(R)N;             //Return the mean, using the precision of type R
}
