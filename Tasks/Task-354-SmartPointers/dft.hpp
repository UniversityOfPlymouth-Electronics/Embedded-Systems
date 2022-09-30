#pragma once

#include "math.h"
#include <memory>

//Normalised Discrete Fourier Transform (DFT) - for type T data
template <class T>
class DFT {
    private:
    uint32_t Nsamp;                     //Number of samples
    std::unique_ptr<T[]> timeSeries;    //Pointer to internal time series array
    uint32_t index = 0;                 //Index to the location of the next sample

    public:
    // Constructor requires the number of samples N at run time
    DFT(uint32_t N = 64) : Nsamp(N) {
        //Allocate the memory - this has only ONE owner (timeSeries)
        timeSeries = std::unique_ptr<T[]>(new T[Nsamp]);
        if (timeSeries == nullptr) {
            //Force a crash
            std::throw_with_nested(std::runtime_error("MEMORY ALLOCATION FAILURE"));
        }
        //Initialise
        for (uint32_t n=0; n<Nsamp; n++) {
            timeSeries[n] = (T)0;
        }
    }

    // Add sample to the internal buffer (time domain)
    void operator << (T sample) {
        timeSeries[index] = sample;
        index = (index == 0) ? Nsamp-1 : index-1;
    }

    // Calculate the magnitude spectrum for a particular bin k
    T calculateMagnitudeForBin(uint32_t k)
    {
        //Perform calculation
        T scale = 2.0*3.1415926/(T)Nsamp;
        T real = (T)0;
        T imag = real;
        for (uint32_t n=0; n<Nsamp; n++) {
            real += timeSeries[n] * cos(scale*k*n);
            imag -= timeSeries[n] * sin(scale*k*n);
        }
        T magnitude = sqrt(real*real + imag*imag);
        return magnitude;
    }
};