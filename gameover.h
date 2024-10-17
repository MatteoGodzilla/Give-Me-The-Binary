#pragma once
#include <stdbool.h>
#include <LiquidCrystal_I2C.h>

namespace GameOverNP {
  void setup();
  void loopAction(int points, LiquidCrystal_I2C *lcd);
  bool isActive();
}