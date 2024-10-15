/*
Authors: Carletti Lorenzo, Catena Matteo
*/

#include "state.h"
#include "attract.h"
#include "sleep.h"

enum State currentState;

void setup() {
  currentState = Attract;
  // put your setup code here, to run once:
  pinMode(LS, OUTPUT); //Red Led (Ls)
  pinMode(12, OUTPUT); //Green Led (L1)
  pinMode(11, OUTPUT); //Green Led (L2)
  pinMode(10, OUTPUT); //Green Led (L3)
  pinMode(9, OUTPUT); //Green Led (L4)
  pinMode(B1, INPUT); //B1
  pinMode(4, INPUT); //B2
  pinMode(3, INPUT); //B3
  pinMode(2, INPUT); //B4
  Serial.begin(9600);
  setupAttract();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (currentState) {
    case Attract:
      loopAttract();
      /*start Attract.c*/;
      break;
    case Game: /*start Game.c*/;
               break;
    case GameOver: /*start GameOver.c*/;
                   break;
    case Sleep:
      ;
                break;
  }
  changeState(currentState);
}

//Pass to the next state
void changeState(State state) {
  switch (state) {
    case Attract:
    if (!isAttractActive()) {
      if (getNextState() == Game) {
        currentState = Game;
      } else if (getNextState() == Sleep) {
        currentState = Sleep;
        setupSleep();
      }
    }
      break;
    case Game:
      if (false/*Booleano di Game == false*/) {
        currentState = GameOver;
      }
      break;
    case GameOver:
      if (false/*Booleano di GameOver == false*/) {
        currentState = Attract;
        setupAttract();
      }
      break;
    case Sleep:
      if (false/*Booleano di Sleep == false*/) {
        currentState = Attract;
      }
      break;
  }
}