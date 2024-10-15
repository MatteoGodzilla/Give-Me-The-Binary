#ifndef SLEEP_H
#define SLEEP_H

#include <stdbool.h>
#include <Arduino.h>
#include <EnableInterrupt.h>
#include "LowPower.h"
#include "pins.h"

void setupSleep();
bool isSleepModeActive();

#endif