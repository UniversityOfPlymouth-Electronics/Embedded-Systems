#pragma once
#include <cstdint>
#include <iostream>

/*
T is the data type of the data
R is the data type of the mean (and sum)
N is the buffer size
*/
template<class T, class R>
class RunningMean {
private:
    uint32_t N;
    T *buffer;
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
    RunningMean(uint32_t N_, T initValue = (T)0) : N(N_) {
        //Initialise data to known state
        sum = (T)0;
        index = 0;
        buffer = new T[N];  //Allocate memory on the heap
        for (unsigned int n=0; n<N; n++) buffer[n] = (T)0;
    }   
    ~RunningMean() {
        //Give back the memory
        //This is critical unless you want a memory leak!
        delete [] buffer;
        // See https://docs.microsoft.com/en-us/cpp/cpp/delete-operator-cpp?view=msvc-170 for a disussion on delete []
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

