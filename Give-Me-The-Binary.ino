/*
Authors: Carletti Lorenzo, Catena Matteo, Dall'Ara Lorenzo
*/

/* State enumeration header */
#include "state.h"

/* Game logic headers */
#include "gameover.h"
#include "attract.h"
#include "sleep.h"
#include "game.h"

/* Hardware references header */
#include "pins.h"

enum State currentState;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

void setup() {
  // put your setup code here, to run once:
  currentState = Attract;
  lcd.init();
  lcd.backlight();
  pinMode(LS, OUTPUT); // Red Led (Ls)
  pinMode(L1, OUTPUT); // Green Led (L1)
  pinMode(L2, OUTPUT); // Green Led (L2)
  pinMode(L3, OUTPUT); // Green Led (L3)
  pinMode(L4, OUTPUT); // Green Led (L4)
  pinMode(B1, INPUT); // Button 1
  pinMode(B2, INPUT); // Button 2
  pinMode(B3, INPUT); // Button 3
  pinMode(B4, INPUT); // Button 4
  Serial.begin(9600);
  AttractNP::setup();
}

void loop() {
  switch (currentState) {
    case Attract:
      AttractNP::loopAction(&lcd);
      break;
    case Game:
      GameNP::loopAction(&lcd);
      break;
    case GameOver:
      GameOverNP::loopAction(0,&lcd);
      break;
    case Sleep:
      break;
  }
  changeState();
}

//Pass to the next state
void changeState() {
  switch (currentState) {
    case Attract:
      if (!AttractNP::isActive()) {
        if (AttractNP::getNextState() == Game) {
          currentState = Game;
          GameNP::setup();
        } else if (AttractNP::getNextState() == Sleep) {
          // currentState = Sleep;
          // SleepNP::setup();
        }
      }
      break;
    case Game:
      if (!GameNP::isActive()) {
        currentState = GameOver;
        GameOverNP::setup();
      }
      break;
    case GameOver:
      if (!GameOverNP::isActive()) {
        currentState = Attract;
        AttractNP::setup();
      }
      break;
    case Sleep:
      if (!SleepNP::isActive()) {
        currentState = Attract;
        AttractNP::setup();
      }
      break;
  }
}