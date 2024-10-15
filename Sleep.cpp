//abilita enable interrupt (può essere presente soltanto in un file in tutto il progetto)
#define LIBCALL_ENABLEINTERRUPT
#include "sleep.h"

static bool active = false;

static void wakeup(){}

void setupSleep() {
    Serial.println("[STATUS: Sleep]");
    Serial.flush();
    active = true;
    enableInterrupt(B1, wakeup, CHANGE);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    disableInterrupt(B1);
    active = false;
}

bool isSleepModeActive(){
    return active;
}