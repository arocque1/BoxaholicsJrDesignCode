#include <Stepper.h>
enum linActDir{EXTEND, RETRACT};
enum stepperDir{CW = 1, CCW = -1};

////////////Variables////////////
//const int linActIn1 = ;
//const int linActIn2 = ;
//const int IRreadPin = ;
//int IRreadVal;

const int NEMA23WheelIN1 = 2;
const int NEMA23WheelIN2 = 3;
const int NEMA23WheelIN3 = 4;
const int NEMA23WheelIN4 = 5;

const int laserPin = 6;
const int laserRecieverPin = 7;
int laserReadVal;

const int NEMA23WheelSpeed = 100;
const int NEMA23WheelStepsPerRev = 200;
const int NEMA23WheelStep = 1;
stepperDir NEMA23WheelDir = CW;
Stepper NEMA23Wheel(NEMA23WheelStepsPerRev,NEMA23WheelIN1, NEMA23WheelIN2, NEMA23WheelIN3, NEMA23WheelIN4);

int beamState;
float wheelAngle = 0;
const float numDivs = 16;
const float dAngle = 360 / numDivs;
////////////////////////////////


void setup() {
  pinMode(NEMA23WheelIN1,OUTPUT);
  pinMode(NEMA23WheelIN2,OUTPUT);
  pinMode(NEMA23WheelIN3,OUTPUT);
  pinMode(NEMA23WheelIN4,OUTPUT);

  NEMA23Wheel.setSpeed(NEMA23WheelSpeed);

  pinMode(laserPin, OUTPUT);
  pinMode(laserRecieverPin, INPUT);

  beamState = digitalRead(laserRecieverPin);
  digitalWrite(laserPin, HIGH);

}

void loop() {
  
  while(wheelAngle < 100){
    laserReadVal = digitalRead(laserRecieverPin);
     NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);
     if(laserReadVal == 0 && beamState == 1){
      wheelAngle = wheelAngle + (NEMA23WheelDir * dAngle);
     }
     beamState = laserReadVal;
  }
  delay(1000);

  // Suction
  NEMA23WheelDir = CCW;
  while(wheelAngle > -100){
    laserReadVal = digitalRead(laserRecieverPin);
    NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);
    if(laserReadVal == 0 && beamState == 1){
      wheelAngle = wheelAngle + (NEMA23WheelDir * dAngle);
    }
    beamState = laserReadVal;
  }
  delay(1000);

  // Drop product
  NEMA23WheelDir = CW;
  while(wheelAngle < 0){
    laserReadVal = digitalRead(laserRecieverPin);
    NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);
    if(laserReadVal == 0 && beamState == 1){
      wheelAngle = wheelAngle + (NEMA23WheelDir * dAngle);
    }
    beamState = laserReadVal;
  }

  delay(1000);

  
 

}
