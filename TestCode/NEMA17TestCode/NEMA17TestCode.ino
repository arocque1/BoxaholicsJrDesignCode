#include <Stepper.h>
enum stepperDir{CW = 1, CCW = -1};

/*///////////////////////////////////////////
////////////Notes////////////////////////////
- The red and blue wires go to OUT1 and/or OUT2
- The green and black wires go to OUT3 and/or OUT4

*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int NEMA17Speed = 200;
const int NEMA17StepsPerRev = 200; // DO NOT CHANGE
int NEMA17Step = 100;
stepperDir NEMA17dir = CW; // CW or CCW
/////////////////////////////

const int NEMA17IN1 = 22;
const int NEMA17IN2 = 23;
const int NEMA17IN3 = 24;
const int NEMA17IN4 = 25;
const int NEMA17Enable = 3;
Stepper NEMA17(NEMA17StepsPerRev, NEMA17IN1, NEMA17IN2, NEMA17IN3, NEMA17IN4);

void setup() {
  pinMode(NEMA17IN1,OUTPUT);
  pinMode(NEMA17IN2,OUTPUT);
  pinMode(NEMA17IN3,OUTPUT);
  pinMode(NEMA17IN4,OUTPUT);
  pinMode(NEMA17Enable, OUTPUT);

  digitalWrite(NEMA17Enable, HIGH);

  NEMA17.setSpeed(NEMA17Speed);

}

void loop() {

  NEMA17.step(NEMA17dir * NEMA17Step);

}
