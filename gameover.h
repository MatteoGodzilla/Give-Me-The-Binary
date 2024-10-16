#pragma once
#include <stdbool.h>
#include <LiquidCrystal_I2C.h>

namespace GameOverNP {
  void setup();
  void loopAction(/*punteggio dalla fase Game*/);
  bool isActive();
}