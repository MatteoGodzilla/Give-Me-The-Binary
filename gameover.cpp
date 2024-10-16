#include "Arduino.h"
#include "gameover.h"

static bool active;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

void GameOverNP::setup() {
  active = true;
  
  lcd.init();
  lcd.backlight();
}

void GameOverNP::loopAction(/*punteggio dalla fase Game*/) {
  //Turn on the red led for 1 second
  digitalWrite(LS, HIGH);
  delay(1000); //1 sec
  digitalWrite(LS, LOW);

  //Display on LCD the message "Game Over - Final Score XXX" for 10 seconds
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game Over");
  lcd.setCursor(0, 1);
  lcd.print("Final Score " + /*punteggio dalla fase Game*/);
  delay(10000); //10 sec
  lcd.clear();

  active = false;
}

bool GameOverNP::isActive() {
  return active;
}