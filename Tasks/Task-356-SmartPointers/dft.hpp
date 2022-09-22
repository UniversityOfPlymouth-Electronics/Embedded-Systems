#pragma once

#include "math.h"
#include <memory>
#include <array>

//Normalised Discrete Fourier Transform
template <class T, uint32_t Nsamp = 64>
class DFT {
    private:
    std::unique_ptr<T[]> timeSeries;
    uint32_t index = 0;

    public:
    DFT() {
        timeSeries = std::unique_ptr<T[]>(new T[Nsamp]);
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

    // For read input data, calculate the magnitude spectrum up to Fs/2
    std::array<T, Nsamp/2> calculateMagnitudeSpectrum() {
        //Allocate the memory
        std::array<T, Nsamp/2> spectrum;

        //Calculate all bins
        for (uint32_t k=0; k<Nsamp/2; k++) {
            spectrum[k] = this->calculateMagnitudeForBin(k);
        }
        return spectrum;
    }
};