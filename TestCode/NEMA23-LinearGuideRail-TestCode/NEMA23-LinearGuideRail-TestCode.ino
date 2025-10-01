#include <Stepper.h>
enum stepperDir{CW = 1, CCW = -1};

/*///////////////////////////////////////////
////////////Notes////////////////////////////
- The yellow and blue wires go to OUT1 and/or OUT2
- The green and red wires go to OUT3 and/or OUT4

*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int NEMA23LinGuideSpeed = 200;
const int NEMA23LinGuideStepsPerRev = 200;
const int NEMA23LinGuideStep = 50;
stepperDir NEMA23LinGuideDir = CW;

const int NEMA23LinGuideIN1 = 30;
const int NEMA23LinGuideIN2 = 31;
const int NEMA23LinGuideIN3 = 32;
const int NEMA23LinGuideIN4 = 33;
const int NEMA23LinGuideEnable = 5;
/////////////////////////////


Stepper NEMA23LinGuide(NEMA23LinGuideStepsPerRev,NEMA23LinGuideIN1, NEMA23LinGuideIN2, NEMA23LinGuideIN3, NEMA23LinGuideIN4);

void setup() {
  pinMode(NEMA23LinGuideIN1,OUTPUT);
  pinMode(NEMA23LinGuideIN2,OUTPUT);
  pinMode(NEMA23LinGuideIN3,OUTPUT);
  pinMode(NEMA23LinGuideIN4,OUTPUT);

  digitalWrite(NEMA23LinGuideEnable, HIGH);

  NEMA23LinGuide.setSpeed(NEMA23LinGuideSpeed);

}

void loop() {
  NEMA23LinGuide.step(NEMA23LinGuideDir * NEMA23LinGuideStep);

}
