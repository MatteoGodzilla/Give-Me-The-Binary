#pragma once
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

namespace GameNP {
  void setup();
  void loopAction(LiquidCrystal_I2C *lcd);
  bool isActive();
  /* MISSING PROCEDURES */
}