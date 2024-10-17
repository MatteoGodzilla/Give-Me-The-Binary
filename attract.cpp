#include "attract.h"

static bool active;
static enum State next;
static int difficulty;

static unsigned long cooldownStart;
#define COOLDOWN_DURATION 2000

#define FLASH_HALF_PERIOD 500
static unsigned long cycleStart;

static bool shouldWaitMore;

static void goSleep() {
  // Serial.print("called ");
  // Serial.println(millis());

  if(shouldWaitMore){
    shouldWaitMore = false;
    // Serial.println("5 secondi sono passati, alla prossima si dorme");
  } else {
    active = false;
    next = Sleep;
    // Serial.println("Passato alla fase sleep");
    Timer1.detachInterrupt();

    // Serial.println(millis());
    Serial.flush();
  }
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
  
  Timer1.initialize(5 * 1000 * 1000);  //5 second timer, should trigger "goSleep" twice
  Timer1.attachInterrupt(goSleep);

  Serial.println("[STATUS: Attract]");

  cooldownStart = millis();
  cycleStart = millis();

  // Serial.println(cooldownStart);
}

static void calculateDifficulty(){
  int value = analogRead(POT) >> 8;
  difficulty = value + 1;
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

  calculateDifficulty();
  printLCD(lcd);

  if (millis() - cooldownStart > COOLDOWN_DURATION && digitalRead(B1) == HIGH) {
    active = false;
    next = Game;
    Timer1.detachInterrupt();
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