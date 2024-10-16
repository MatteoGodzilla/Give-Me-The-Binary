#pragma once
#include <stdbool.h>
#include <Arduino.h>
#include <TimerOne.h>
#include "state.h"
#include "pins.h"

namespace AttractNP {
  void setup();
  void loopAction();
  bool isActive();
  enum State getNextState();
}