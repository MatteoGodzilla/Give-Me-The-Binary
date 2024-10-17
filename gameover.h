#pragma once
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "pins.h"

namespace GameOverNP {
  void setup();
  void loopAction(int points, LiquidCrystal_I2C *lcd);
  bool isActive();
}