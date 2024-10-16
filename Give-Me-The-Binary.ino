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

using GameOverNP;
using AttractNP;
using SleepNP;
using GameNP;

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
  setupAttract();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (currentState) {
    case Attract:
      Attract::loopAttract();
      break;
    case Game:
      /*start Game.c*/;
      /*Decide when and how call Game::setup()*/
      /*Game::loopAction();*/
      break;
    case GameOver:
      /*start GameOver.c*/;
      /*Decide when and how call GameOver::setup()*/
      /*GameOver::loopAction();*/
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
      if (!isAttractActive()) {
        if (getAttractNextState() == Game) {
          currentState = Game;
        } else if (getAttractNextState() == Sleep) {
          currentState = Sleep;
          setupSleep();
        }
      }
      break;
    case Game:
      if (false/*Booleano di Game == false, Game::isActive()*/) {
        currentState = GameOver;
      }
      break;
    case GameOver:
      if (false/*Booleano di GameOver == false, GameOver::isActive()*/) {
        currentState = Attract;
        setupAttract();
      }
      break;
    case Sleep:
      if (!isSleepModeActive()) {
        currentState = Attract;
        setupAttract();
      }
      break;
  }
}