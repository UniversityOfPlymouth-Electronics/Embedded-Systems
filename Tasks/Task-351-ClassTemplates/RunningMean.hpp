#pragma once
#include <iostream>

/*
T is the data type of the data
R is the data type of the mean (and sum)
N is the buffer size
*/
template<class T, class R, int N>
class RunningMean {
private:
    T buffer[N];
    R sum;
    int index;

    // Computing a running sum (Optimised for speed - no checks for overflows!!!)
    void addAndUpdate(T nextSample) {
        // Sum is updated - add new sample, subtract oldest
        sum = sum + nextSample - buffer[index];
        buffer[index] = nextSample;     //Overwrite oldest sample
        index = (index + 1) % N;        //Update position of oldest sample
    }

public:
    //Constructor
    RunningMean(T initValue = (T)0) {
        //Initialise data to known state
        sum = (T)0;
        index = 0;
        for (unsigned int n=0; n<N; n++) buffer[n] = (T)0;
    }   

    //Used to add a sample to the buffer
    void operator += (T sample) {
        this->addAndUpdate(sample);
    }

    //Used to read the mean
    operator R() {
        return sum/(R)N;             //Return the mean, using the precision of type R
    }
};

