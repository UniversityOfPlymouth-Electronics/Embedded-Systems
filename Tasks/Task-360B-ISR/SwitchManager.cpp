#include "SwitchManager.hpp"

volatile uint32_t SwitchManager::count = 0;

void SwitchManager::waitForRising() {
  SwitchManager::count++;

  // Turn off interrupt
  switchInterrupt.rise(NULL);

  // Turn on timer
  t.attach(callback(this, &SwitchManager::waitForStabilityRising), 50ms);
}

void SwitchManager::waitForStabilityRising() {
  // Turn off interrupt
  t.detach();

  // Look for falling edge
  switchInterrupt.fall(callback(this, &SwitchManager::waitForFalling));
}

void SwitchManager::waitForFalling() {
  led = !led;

  // Turn off interrupt
  switchInterrupt.fall(NULL);

  // Turn on timer
  t.attach(callback(this, &SwitchManager::waitForStabilityFalling), 50ms);
}

void SwitchManager::waitForStabilityFalling() {
  // Turn off interrupt
  t.detach();

  // Look for rising edge
  switchInterrupt.rise(callback(this, &SwitchManager::waitForRising));
}
