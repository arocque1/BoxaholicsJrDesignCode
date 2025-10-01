#include <Stepper.h>
enum stepperDir{CW = 1, CCW = -1};

/*///////////////////////////////////////////
////////////Notes////////////////////////////
- The red and blue wires go to OUT1 and/or OUT2
- The green and black wires go to OUT3 and/or OUT4

*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int NEMA23WheelSpeed = 100;
const int NEMA23WheelStepsPerRev = 200;
const int NEMA23WheelStep = 1;
stepperDir NEMA23WheelDir = CCW;
const int NEMA23WheelIN1 = 2;
const int NEMA23WheelIN2 = 3;
const int NEMA23WheelIN3 = 4;
const int NEMA23WheelIN4 = 5;
/////////////////////////////


Stepper NEMA23Wheel(NEMA23WheelStepsPerRev,NEMA23WheelIN1, NEMA23WheelIN2, NEMA23WheelIN3, NEMA23WheelIN4);

void setup() {
  pinMode(NEMA23WheelIN1,OUTPUT);
  pinMode(NEMA23WheelIN2,OUTPUT);
  pinMode(NEMA23WheelIN3,OUTPUT);
  pinMode(NEMA23WheelIN4,OUTPUT);

  NEMA23Wheel.setSpeed(NEMA23WheelSpeed);

}

void loop() {
  NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);

}
