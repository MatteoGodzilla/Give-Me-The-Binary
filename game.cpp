#include "Arduino.h"
#include "game.h"

static bool active;
static int toGuess;
static unsigned long roundPeriod = 0;
static int score;
static int roundPoints;

static unsigned long periodStart;

#define MID_ROUND_DELAY 3000
#define FIRST_ROUND_PERIOD 5000

static float factor;

static void startRound(){
  digitalWrite(LS, LOW);
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(L3,LOW);
  digitalWrite(L4,LOW);

  toGuess = random(0,16);
  roundPeriod *= factor;
  periodStart = millis();
}

void GameNP::setup(int difficulty, LiquidCrystal_I2C *lcd){
  active = true;
  Serial.println("[STATUS: Game]");
  Serial.println(difficulty);
  
  //1 = minimum difficulty, 4 = maximum difficulty
  switch(difficulty){
    default:
    case 1:
      factor = 0.95;
      roundPoints = 1;
      break;
    case 2:
      factor = 0.90;
      roundPoints = 2;
      break;
    case 3:
      factor = 0.85;
      roundPoints = 4;
      break;
    case 4:
      factor = 0.80;
      roundPoints = 8;
      break;
  }

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Go!");
  delay(1000);

  score = 0;
  startRound();
  roundPeriod = FIRST_ROUND_PERIOD; //10 seconds
}

static void goodJob(LiquidCrystal_I2C *lcd){
  lcd->clear();
  lcd->setCursor(0,0);
  lcd->print("GOOD! Score:");
  lcd->print(score);
}

static void printRoundLCD(unsigned long time, LiquidCrystal_I2C *lcd){
  lcd->clear();
  lcd->setCursor(0, 0);
  //time bar
  int bars;
  if(time - periodStart < roundPeriod){
    bars = (roundPeriod - (time - periodStart)) * 20 / roundPeriod;
  } else {
    bars = 0;
  }

  for(int i = 0; i < bars; i++){
    lcd->write(255);
  }
  lcd->setCursor(0, 1);
  lcd->print(toGuess);
}

static void checkGuess(LiquidCrystal_I2C *lcd){
  int guess = 0;

  //For those who really like bitwise operators
  /*
  guess |= digitalRead(B1);
  guess <<= 1;

  guess |= digitalRead(B2);
  guess <<= 1;

  guess |= digitalRead(B3);
  guess <<= 1;

  guess |= digitalRead(B4);
  */

  if(digitalRead(B1) == HIGH){
    guess += 8;
  }

  if(digitalRead(B2) == HIGH){
    guess += 4;
  }

  if(digitalRead(B3) == HIGH){
    guess += 2;
  }

  if(digitalRead(B4) == HIGH){
    guess += 1;
  } 

  if(guess == toGuess){
    score += roundPoints;
    goodJob(lcd);
    delay(MID_ROUND_DELAY);
    startRound();
  } else {
    active = false;
  }
}

static void updateLED(){
  digitalWrite(L1,digitalRead(B1));
  digitalWrite(L2,digitalRead(B2));
  digitalWrite(L3,digitalRead(B3));
  digitalWrite(L4,digitalRead(B4));
}

void GameNP::loopAction(LiquidCrystal_I2C *lcd){
  unsigned long now = millis();
  if(now - periodStart >= roundPeriod){
    checkGuess(lcd);
  }
  updateLED();
  printRoundLCD(now, lcd);
  delay(10);
}

bool GameNP::isActive(){
  return active;
}

int GameNP::getScore(){
  return score;
}
