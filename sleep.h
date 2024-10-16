#pragma once
#include <stdbool.h>
#include <Arduino.h>
#include <EnableInterrupt.h>
#include "LowPower.h"
#include "pins.h"

namespace SleepNP {
  void setupSleep();
  bool isSleepModeActive();
}