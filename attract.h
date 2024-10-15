#ifndef ATTRACT_H
#define ATTRACT_H

#include <stdbool.h>
#include <Arduino.h>
#include <TimerOne.h>
#include "state.h"
#include "pins.h"

void setupAttract();
void loopAttract();
bool isAttractActive();
enum State getNextState();

#endif