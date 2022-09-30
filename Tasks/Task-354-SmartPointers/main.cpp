
#include "uop_msb.h"

#include "dft.hpp"
#include "useful_stuff.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <array>
#include <type_traits>

using namespace std;

DigitalIn blueButton(USER_BUTTON);
DigitalOut led1(LED1);
DigitalOut led2(LED2);
AnalogIn pot(AN_POT_PIN);
AnalogIn ldr(AN_LDR_PIN);
AnalogIn mic(MIC_AN_PIN);

// WE HAVE 256K Bytes SRAM
// Middle C is 262Hz in case you want to try this


double magnitudeAtFrequency(double f, double Fs, uint32_t Nsamples)
{
    //Create DFT object on the stack (the internal memory is on the heap)
    DFT<double> dft(Nsamples);

    //Sampling interval (uS)
    uint32_t T = (uint32_t)round(1000000.0/Fs);

    //Perform crude sampling (assumes ADC and buffer write take zero time)
    for (uint32_t n=0; n<Nsamples; n++) {
        dft << (double)mic.read();          //Read ADC and write to dft buffer
        wait_us(T);
    }

    //Identify the bin for the frequency f - each bin => Fs/N
    //  k * (Fs/N) = f
    uint32_t k = ((uint32_t)(f * Nsamples / Fs)) % Nsamples;
    return dft.calculateMagnitudeForBin(k);

    //dft now goes out of scope
}

int main()
{
    double Fs;          //Sampling rate (Hz)
    uint32_t Nsamples;  //Number of samples to measure
    double f;           //Frequency of interest

    //Repeat until the blue button is pressed
    do 
    {
        //Get user data
        cout << "Enter sampling rate (Hz)" << endl;
        cin >> Fs;

        cout << "Enter number of samples" << endl;
        cin >> Nsamples;

        cout << "Frequency of interest (Hz)" << endl;
        cin >> f;

        cout << "Starting" << endl;
    
        print_memory_info();
        double mag = magnitudeAtFrequency(f, Fs, Nsamples);
        print_memory_info();
        
        cout << "Magnitude at " << f << " is " << mag << endl << endl;

    } while (blueButton == 0); 

    print_memory_info();

    //Sleep the CPU
    sleep();

    return 0;
}



