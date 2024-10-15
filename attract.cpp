#include "attract.h"


static bool active;
static enum State next = Sleep;
int fadeAmount = 5;
int currIntensity = 0;

void setupAttract() {
  active = true;
  Timer1.initialize(10000000); //10 sec
  Timer1.attachInterrupt(goSleep());
}

void loopAttract() {
    analogWrite(LS, currIntensity);
    currIntensity += fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
        fadeAmount = -fadeAmount;
    }

    if (digitalRead(B1) == HIGH) {
        active = false;
        next = Game;
        Timer1.detachInterrupt();
    }
}

bool isAttractActive() {
    return active;
}

enum State getNextState(){
    return next;
}

void goSleep() {
    active = false;
    next = Sleep;
}