#pragma once
#include <Arduino.h>
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>
#include "state.h"
#include "pins.h"

namespace AttractNP {
  void setup();
  void loopAction(LiquidCrystal_I2C *lcd);
  bool isActive();
  enum State getNextState();
}