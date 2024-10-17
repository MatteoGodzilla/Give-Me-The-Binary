#pragma once
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "pins.h"

namespace GameNP {
  void setup(int difficulty, LiquidCrystal_I2C *lcd);
  void loopAction(LiquidCrystal_I2C *lcd);
  bool isActive();
  int getScore();
}