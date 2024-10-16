#include "Arduino.h"
#include "attract.h"

static bool active;
static enum State next = Sleep;
static int fadeAmount = 5;
static int currIntensity = 0;

static unsigned long cooldownStart;
static unsigned long cooldownDuration = 1000;

void goSleep() {
  active = false;
  next = Sleep;
  Serial.println("Passato alla fase sleep");
  Timer1.detachInterrupt();

  Serial.println(millis());
  Serial.flush();
}

void setupAttract() {
  active = true;

  Timer1.initialize(10 * 1000 * 1000);  //10 sec
  Timer1.attachInterrupt(goSleep);
  Serial.println("[STATUS: Attract]");

  cooldownStart = millis();

  Serial.println(cooldownStart);
}

void loopAttract() {
  analogWrite(LS, currIntensity);
  currIntensity += fadeAmount;
  if (currIntensity == 0 || currIntensity == 255) {
    fadeAmount = -fadeAmount;
  }

  if (millis() - cooldownStart > cooldownDuration && digitalRead(B1) == HIGH) {
    active = false;
    next = Game;
    Timer1.detachInterrupt();
  }
  delay(10);
}

bool isAttractActive() {
  return active;
}

enum State getAttractNextState() {
  return next;
}