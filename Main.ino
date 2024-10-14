/*
Authors: Carletti Lorenzo, Catena Matteo
*/

enum State {
  Attract,
  Game,
  GameOver,
  Sleep
};

State currentState = Attract;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT); //Red Led (Ls)
  pinMode(12, OUTPUT); //Green Led (L1)
  pinMode(11, OUTPUT); //Green Led (L2)
  pinMode(10, OUTPUT); //Green Led (L3)
  pinMode(9, OUTPUT); //Green Led (L4)
  pinMode(5, INPUT); //B1
  pinMode(4, INPUT); //B2
  pinMode(3, INPUT); //B3
  pinMode(2, INPUT); //B4
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (currentState) {
    case Attract: /*start Attract.c*/;
                  break;
    case Game: /*start Game.c*/;
               break;
    case GameOver: /*start GameOver.c*/;
                   break;
    case Sleep: /*start Sleep.c*/;
                break;
  }
  changeState(currentState);
}

//Pass to the next state
void changeState(State state) {
  switch (state) {
    case Attract: 
      if (/*Booleano di Attract == false*/) {
        currentState = Game;
      }
      break;
    case Game: 
      if (/*Booleano di Game == false*/) {
        currentState = GameOver;
      }
      break;
    case GameOver: 
      if (/*Booleano di GameOver == false*/) {
        currentState = Attract;
      }
      break;
    case Sleep: 
      if (/*Booleano di Sleep == false*/) {
        currentState = Attract;
      }
      break;
  }
}