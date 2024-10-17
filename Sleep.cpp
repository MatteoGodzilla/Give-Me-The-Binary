//abilita enable interrupt (può essere presente soltanto in un file in tutto il progetto)
#define LIBCALL_ENABLEINTERRUPT
#include "sleep.h"

static bool active = false;

static void wakeup(){}

void SleepNP::setup(LiquidCrystal_I2C *lcd) {
    active = true;
    Serial.println("[STATUS: Sleep]");
    Serial.flush();
    digitalWrite(LS, LOW);
    
    lcd->clear();
    lcd->noBacklight();
    
    enableInterrupt(B1, wakeup, CHANGE);
    enableInterrupt(B2, wakeup, CHANGE);
    enableInterrupt(B3, wakeup, CHANGE);
    enableInterrupt(B4, wakeup, CHANGE);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    disableInterrupt(B1);
    disableInterrupt(B2);
    disableInterrupt(B3);
    disableInterrupt(B4);

    lcd->backlight();

    active = false;
}

bool SleepNP::isActive(){
    return active;
}