#pragma once
#include <Arduino.h>
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h>
#include "LowPower.h"
#include "pins.h"

namespace SleepNP {
  void setup(LiquidCrystal_I2C *lcd);
  bool isActive();
}