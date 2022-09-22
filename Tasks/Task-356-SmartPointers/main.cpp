#include "uop_msb.h"

#include "dft.hpp"
#include "useful_stuff.hpp"

#include <iostream>
#include <memory>
#include <array>

using namespace std;

DigitalIn blueButton(USER_BUTTON);
DigitalOut led1(LED1);
DigitalOut led2(LED2);
AnalogIn pot(AN_POT_PIN);
AnalogIn ldr(AN_LDR_PIN);
AnalogIn mic(MIC_AN_PIN);

// WE HAVE 256K Bytes SRAM
// Middle C is 262Hz
// Sample at 4096Hz (4096 samples per second) for 1s
// 1 bin per Hz

#define N 4096
#define Tsamp_us (1000000 / N)

int main()
{
    //Not how much heap space we have at the start
    print_memory_info();
    
    //Create single object on the heap (expensive)
    uint32_t memAtStart = print_memory_info();

    //Wait for key press
    std::cout << "Press the blue button" << std::endl;
    while (blueButton == 0);
    wait_us(250000);
    while (blueButton == 1);
    wait_us(250000);
    std::cout << "Starting" << std::endl;

    //Create DFT object
    DFT<double,N> dft;
    array<int, 10> opengenus;

    //Repeat forever
    do 
    {
        std::cout << "Sampling..." << std::endl;
        for (uint32_t n=0; n<N; n++) {
            double samp = mic;
            dft << samp;
            wait_us(Tsamp_us);
        }
        std::cout << "1s recorded" << std::endl;
        {
            //Does the next line copy or move?
            auto spectrum = dft.calculateMagnitudeSpectrum();

            //Find the peak
            double maxP = 0.0;
            uint32_t maxIndex = 0;
            for (uint32_t n=0; n<N/2; n++) {
                double m = spectrum[n];
                if (m>maxP) {
                    maxP = m;
                    maxIndex = n;
                }
            }
            std::cout << "Peak of " << maxP << " found at index " << maxIndex << std::endl;

        }
        
    } while (blueButton == 0); 

    print_memory_info();

    //Sleep the CPU
    sleep();

    return 0;
}



