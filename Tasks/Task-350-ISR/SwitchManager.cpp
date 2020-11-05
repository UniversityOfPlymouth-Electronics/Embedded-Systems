#include "SwitchManager.hpp"

volatile uint32_t SwitchManager::count = 0;

void SwitchManager::waitForRising() {
  SwitchManager::count++;

  // Turn off interrupt
  switchInterrupt.rise(NULL);
  // Turn on timer
  t.attach(callback(this, &SwitchManager::waitForStabilityRising), 200ms);
}

void SwitchManager::waitForStabilityRising() {
  // Look for falling edge
  switchInterrupt.fall(callback(this, &SwitchManager::waitForFalling));
}

void SwitchManager::waitForFalling() {
  led = !led;
  switchInterrupt.fall(NULL);
  t.attach(callback(this, &SwitchManager::waitForStabilityFalling), 200ms);
}

void SwitchManager::waitForStabilityFalling() {
  // Look for rising edge
  switchInterrupt.rise(callback(this, &SwitchManager::waitForRising));
}
