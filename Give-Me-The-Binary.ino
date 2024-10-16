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

void setup() {
  currentState = Attract;
  // put your setup code here, to run once:
  pinMode(LS, OUTPUT); // Red Led (Ls)
  pinMode(L1, OUTPUT); // Green Led (L1)
  pinMode(L2, OUTPUT); // Green Led (L2)
  pinMode(L3, OUTPUT); // Green Led (L3)
  pinMode(L4, OUTPUT); // Green Led (L4)
  pinMode(B1, INPUT); // B1
  pinMode(B2, INPUT); // B2
  pinMode(B3, INPUT); // B3
  pinMode(B4, INPUT); // B4
  Serial.begin(9600);
  AttractNP::setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (currentState) {
    case Attract:
      AttractNP::loopAction();
      break;
    case Game:
      /*start Game.c*/;
      /*Decide when and how call Game::setup()*/
      /*Game::loopAction();*/
      break;
    case GameOver:
      GameOverNP::loopAction(/*punteggio dalla fase Game*/);
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
          /*Missing call to GameNP::setup() ???*/
        } else if (AttractNP::getNextState() == Sleep) {
          currentState = Sleep;
          SleepNP::setup();
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