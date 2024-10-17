#include "game.h"

static bool active;

void GameNP::setup(){
  active = true;
  Serial.println("[STATUS: Game]");
}

void GameNP::loopAction(LiquidCrystal_I2C *lcd){
  
}

bool GameNP::isActive(){
  return active;
}
