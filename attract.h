#pragma once
#include <stdbool.h>
#include <Arduino.h>
#include <TimerOne.h>
#include "state.h"
#include "pins.h"

namespace AttractNP {
  void setupAttract();
  void loopAttract();
  bool isAttractActive();
  enum State getAttractNextState();
}