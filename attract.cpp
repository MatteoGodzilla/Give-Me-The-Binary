#include "attract.h"

static bool active;
static enum State next;
static int difficulty;
static int lastPotValue = 0;

static unsigned long cooldownStart;
#define COOLDOWN_DURATION 1000

#define FLASH_HALF_PERIOD 500
static unsigned long cycleStart;

#define TIME_TO_SLEEP 10000
static unsigned long sleepTimeoutStart;

static bool shouldWaitMore;

static void goSleep() {
  active = false;
  next = Sleep;
}

static void printLCD(LiquidCrystal_I2C *lcd){
  lcd->setCursor(0, 0);
  lcd->print("Welcome to GMB!");
  lcd->setCursor(0, 1);
  lcd->print("Press B1 to Start");
  lcd->setCursor(0, 2);
  lcd->print("Difficulty:");
  lcd->print(difficulty);
}

void AttractNP::setup() {
  active = true;
  shouldWaitMore = true;

  Serial.println("[STATUS: Attract]");

  cooldownStart = millis();
  cycleStart = millis();
  sleepTimeoutStart = millis();
}

static void calculateDifficulty(){
  int currentPot = analogRead(POT);
  int value = currentPot >> 8;
  difficulty = value + 1;
  if (currentPot != lastPotValue) {
    lastPotValue = currentPot;
    sleepTimeoutStart = millis();
  }
}

void AttractNP::loopAction(LiquidCrystal_I2C *lcd) {
  unsigned long now = millis();
  unsigned long cycleDelta = now - cycleStart;
  if(cycleDelta < FLASH_HALF_PERIOD){
    //rising
    int amount = cycleDelta * 255 / (FLASH_HALF_PERIOD);
    analogWrite(LS, amount);
  } else if(cycleDelta < FLASH_HALF_PERIOD * 2){
    //falling
    int amount = 255 - ((cycleDelta - FLASH_HALF_PERIOD) * 255 / (FLASH_HALF_PERIOD));
    analogWrite(LS, amount);
  } else {
    cycleStart = now;
  }

  unsigned long sleepDelta = now - sleepTimeoutStart;
  if(sleepDelta > TIME_TO_SLEEP){
    goSleep();
  }

  calculateDifficulty();
  printLCD(lcd);

  if (millis() - cooldownStart > COOLDOWN_DURATION && digitalRead(B1) == HIGH) {
    active = false;
    next = Game;
  }
  delay(10);
}

bool AttractNP::isActive() {
  return active;
}

enum State AttractNP::getNextState() {
  return next;
}

int AttractNP::getDifficulty(){
  return difficulty;
}