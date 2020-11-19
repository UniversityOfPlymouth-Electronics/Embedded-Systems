#ifndef __SWITCH_MANAGER__
#define __SWITCH_MANAGER__

#include "mbed.h"
// This class manages an Interrupt in and LED output
// It automatically manages the switch-debounce using edge detection and timers
class SwitchManager {
private:
  InterruptIn switchInterrupt;
  DigitalOut led;
  Timeout t;
  static volatile uint32_t count;

  void waitForRising();
  void waitForStabilityRising();
  void waitForFalling();
  void waitForStabilityFalling();

public:
  SwitchManager(PinName intInPin, PinName gpioPin)
      : switchInterrupt(intInPin), led(gpioPin) {
    CriticalSectionLock::enable();
    count = 0;
    CriticalSectionLock::disable();
    // Listen for rising edge
    switchInterrupt.rise(callback(this, &SwitchManager::waitForRising));
  }
  ~SwitchManager() {
    // Turn off LED and shut off any ISRs
    led = 0;
    switchInterrupt.rise(NULL);
    switchInterrupt.fall(NULL);
    t.detach();
  }

  //This is a STATIC member of the CLASS
  static uint32_t getCount() { 
      CriticalSectionLock lock;
      return count; 
  }
};

#endif