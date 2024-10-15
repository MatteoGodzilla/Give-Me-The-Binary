#include <stdbool.h>
#include "state.h"
#include <TimerOne.h>

#define LS 13
#define B1 5

void setupAttract();
void loopAttract();
bool isAttractActive();
enum State getNextState();