#include <Stepper.h>
enum linActDir{EXTEND, RETRACT};
enum stepperDir{CW = 1, CCW = -1};
enum casePos{IMPORT, EXPORT};
enum wheelPos{SUCTION, NEUTRAL, DROP};

int checkIfSupplyOn = 8;
////////Stepper Motor Parameters////////
/////////////////NEMA 17////////////////
const int NEMA17Speed = 200;
const int NEMA17StepsPerRev = 200; // DO NOT CHANGE
int NEMA17Step = 100;
stepperDir NEMA17dir = CW; // CW or CCW

/////////////NEMA 23 Wheel//////////////
const int NEMA23WheelSpeed = 100;
const int NEMA23WheelStepsPerRev = 200;
const int NEMA23WheelStep = 1;
stepperDir NEMA23WheelDir = CCW;


////////NEMA 23 Linear Guide Rail///////
const int NEMA23LinGuideSpeed = 200;
const int NEMA23LinGuideStepsPerRev = 200;
const int NEMA23LinGuideStep = 50;
stepperDir NEMA23LinGuideDir = CW;

////////////////////////////////////////

////////Stepper motor variables/////////
///////////NEMA 17 Conveyor/////////////
const int NEMA17IN1 = 22;
const int NEMA17IN2 = 23;
const int NEMA17IN3 = 24;
const int NEMA17IN4 = 25;
const int NEMA17Enable = 3;
Stepper NEMA17(NEMA17StepsPerRev, NEMA17IN1, NEMA17IN2, NEMA17IN3, NEMA17IN4);

//////////NEMA 23 Wheel/////////////////
const int NEMA23WheelIN1 = 26;
const int NEMA23WheelIN2 = 27;
const int NEMA23WheelIN3 = 28;
const int NEMA23WheelIN4 = 29;
const int NEMA23WheelEnable = 4;
Stepper NEMA23Wheel(NEMA23WheelStepsPerRev, NEMA23WheelIN1, NEMA23WheelIN2, NEMA23WheelIN3, NEMA23WheelIN4);

////////NEMA 23 Linear Guide Rail///////
const int NEMA23LinGuideIN1 = 30;
const int NEMA23LinGuideIN2 = 31;
const int NEMA23LinGuideIN3 = 32;
const int NEMA23LinGuideIN4 = 33;
const int NEMA23LinGuideEnable = 5;
Stepper NEMA23LinGuide(NEMA23LinGuideStepsPerRev,NEMA23LinGuideIN1, NEMA23LinGuideIN2, NEMA23LinGuideIN3, NEMA23LinGuideIN4);

////////////////////////////////////////

/////////Sorting Lin Act (50mm)///////
const int sort50mmLinActIn1 = 34;
const int sort50mmLinActIn2 = 35;
const int sort50mmLinActEnable = 6;
linActDir linAct50mmDir; // EXTEND or RETRACT

/////////Suction Lin Act (25mm)///////
const int suction25mmLinActIn1 = 37;
const int suction25mmLinActIn2 = 36;
const int suction25mmLinActEnable = 7;
linActDir linAct25mmDir = RETRACT; // EXTEND or RETRACT

////////////////////////////////////////

//////////Sensor Variables////////////
///////////////Laser//////////////////
const int laserPin = 53;
const int laserRecieverPin = 52;
int laserReadVal;

//////////////Ultrasonic//////////////
const int trigPin = 51;
const int echoPin = 50;
float ultrasonicDistance;
float ultrasonicDuration;

/////////////Beam Breaker////////////
const int beamPin = 49;
int beamRead;

////////////////////////////////////////

void setup() {

  Serial.begin(9600);
  ///////////NEMA 17 Conveyor/////////////
  pinMode(NEMA17IN1,OUTPUT);
  pinMode(NEMA17IN2,OUTPUT);
  pinMode(NEMA17IN3,OUTPUT);
  pinMode(NEMA17IN4,OUTPUT);
  pinMode(NEMA17Enable, OUTPUT);
  NEMA17.setSpeed(NEMA17Speed);

  //////////NEMA 23 Wheel/////////////////
  pinMode(NEMA23WheelIN1,OUTPUT);
  pinMode(NEMA23WheelIN2,OUTPUT);
  pinMode(NEMA23WheelIN3,OUTPUT);
  pinMode(NEMA23WheelIN4,OUTPUT);
  pinMode(NEMA23WheelEnable, OUTPUT);

  NEMA23Wheel.setSpeed(NEMA23WheelSpeed);

  ////////NEMA 23 Linear Guide Rail///////
  pinMode(NEMA23LinGuideIN1,OUTPUT);
  pinMode(NEMA23LinGuideIN2,OUTPUT);
  pinMode(NEMA23LinGuideIN3,OUTPUT);
  pinMode(NEMA23LinGuideIN4,OUTPUT);
  pinMode(NEMA23LinGuideEnable, OUTPUT);

  NEMA23LinGuide.setSpeed(NEMA23LinGuideSpeed);

  /////////Sorting Lin Act (50mm)///////
  pinMode(sort50mmLinActIn1, OUTPUT);
  pinMode(sort50mmLinActIn2, OUTPUT);
  pinMode(sort50mmLinActEnable, OUTPUT);

  /////////Suction Lin Act (25mm)///////
  pinMode(suction25mmLinActIn1, OUTPUT);
  pinMode(suction25mmLinActIn2, OUTPUT);
  pinMode(suction25mmLinActEnable, OUTPUT);

  ///////////////Laser//////////////////
  pinMode(laserPin, OUTPUT);
  pinMode(laserRecieverPin, INPUT);

  //////////////Ultrasonic//////////////
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  /////////////Beam Breaker/////////////
  pinMode(beamPin, INPUT);



  // Turn off all motors
  digitalWrite(NEMA17Enable, LOW);
  digitalWrite(NEMA23WheelEnable, LOW);
  digitalWrite(NEMA23LinGuideEnable, LOW);
  digitalWrite(sort50mmLinActEnable, LOW);
  digitalWrite(suction25mmLinActEnable, LOW);

}




///////////State Variables/////////////
int productCount = 0;
int beamState;
int prevBeamState;
casePos casePosition = IMPORT;
wheelPos wheelPosition = DROP;
float caseExportDistance = 4.6; // ??????

int laserState;
int prevLaserState;

casePos IMPORTenum = IMPORT;
casePos EXPORTenum = EXPORT;

wheelPos SUCTIONenum = SUCTION;
wheelPos NEUTRALenum = NEUTRAL;
wheelPos DROPenum = DROP;

int numLaserBreak;

//////////Reset variables////////////
linActDir resetSorter = RETRACT;
linActDir resetSuction = EXTEND;


//////////State functions////////////
void resetMotors(int caseCount){
  ////////////Reset stuff////////////

  digitalWrite(NEMA17Enable, LOW);
  digitalWrite(NEMA23WheelEnable, LOW);
  digitalWrite(NEMA23LinGuideEnable, LOW);
  digitalWrite(sort50mmLinActEnable, LOW);
  digitalWrite(suction25mmLinActEnable, LOW);
  
  // Wheel
  digitalWrite(NEMA23WheelEnable, HIGH);
  digitalWrite(laserPin,HIGH);
  NEMA23WheelDir = CW;
  wheelPosition = DROP;
  while(wheelPosition != NEUTRAL){
    NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);
    //Serial.println(digitalRead(laserRecieverPin));
    laserState = digitalRead(laserRecieverPin);
    if(laserState == 0 && prevLaserState == 1){
      wheelPosition = NEUTRAL;
    }
    prevLaserState = laserState;
  }

  

  NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);
  //Serial.println(caseCount);
  if(caseCount % 2 == 0 || caseCount == 0){
  // Linear Guide Rail
  digitalWrite(NEMA23LinGuideEnable, HIGH);
  NEMA23LinGuideDir = CW;
  while(readUltrasonic(trigPin, echoPin) < 14){
    //Serial.println(readUltrasonic(trigPin, echoPin));
    NEMA23LinGuide.step(NEMA23LinGuideDir * NEMA23LinGuideStep);
    casePosition = IMPORT;
  }
  digitalWrite(NEMA23LinGuideEnable, LOW);
  }

  
  /*
  // Sorter
  digitalWrite(sort50mmLinActEnable, HIGH);
  driveLinAct(sort50mmLinActIn1, sort50mmLinActIn2, resetSorter);
  delay(5000);
  digitalWrite(sort50mmLinActEnable, LOW);
  
  // Suction
  digitalWrite(suction25mmLinActEnable, HIGH);
  driveLinAct(suction25mmLinActIn1, suction25mmLinActIn2, resetSuction);
  delay(5000);
  digitalWrite(suction25mmLinActEnable, LOW);
  */
}

void inputAndSort(){
  ////////Input and sort product////////

  digitalWrite(NEMA17Enable, LOW);
  digitalWrite(NEMA23WheelEnable, LOW);
  digitalWrite(NEMA23LinGuideEnable, LOW);
  digitalWrite(sort50mmLinActEnable, LOW);
  digitalWrite(suction25mmLinActEnable, LOW);

  productCount = 0;

  digitalWrite(NEMA17Enable, HIGH); // Turn on conveyor
  
  while(productCount < 2){
    beamState = digitalRead(beamPin);
    //Serial.println(beamState);
    if(beamState == 0 && prevBeamState == 1){
      productCount++;
    }
    prevBeamState = beamState;
    NEMA17.step(NEMA17dir * NEMA17Step);
  }
  for(int i = 0; i < 5; i++){ // Add delay in case product gets caught
    NEMA17.step(NEMA17dir * NEMA17Step);
  }
  digitalWrite(NEMA17Enable, LOW); // Turn off conveyor

  linAct50mmDir = EXTEND;
  digitalWrite(sort50mmLinActEnable, HIGH);
  driveLinAct(sort50mmLinActIn1, sort50mmLinActIn2, linAct50mmDir); // Extend sorter
  delay(4600); // Wait until fully extended (Adjust)
  linAct50mmDir = RETRACT;
  driveLinAct(sort50mmLinActIn1, sort50mmLinActIn2, linAct50mmDir); // Retract sorter
  delay(4600); // Wait until fully extended (Adjust)
  digitalWrite(sort50mmLinActEnable, LOW);



  productCount = 0;

  digitalWrite(NEMA17Enable, HIGH); // Turn on conveyor
  while(productCount < 2){
    beamState = digitalRead(beamPin);
    if(beamState == 0 && prevBeamState == 1){
      productCount++;
    }
    prevBeamState = beamState;
    NEMA17.step(NEMA17dir * NEMA17Step);
  }
  for(int i = 0; i < 5; i++){ // Add delay in case product gets caught
    NEMA17.step(NEMA17dir * NEMA17Step);
  }
  digitalWrite(NEMA17Enable, LOW); // Turn off conveyor

  linAct50mmDir = EXTEND;
  digitalWrite(sort50mmLinActEnable, HIGH);
  driveLinAct(sort50mmLinActIn1, sort50mmLinActIn2, EXTEND); // Extend sorter
  delay(800); // Wait until fully extended (Adjust)
  linAct50mmDir = RETRACT;
  driveLinAct(sort50mmLinActIn1, sort50mmLinActIn2, RETRACT); // Retract sorter
  delay(800); // Wait until fully extended (Adjust)
  digitalWrite(sort50mmLinActEnable, LOW);
}




void suction(){
  ////////Suction and move case////////
  digitalWrite(NEMA17Enable, LOW);
  digitalWrite(NEMA23WheelEnable, LOW);
  digitalWrite(NEMA23LinGuideEnable, LOW);
  digitalWrite(sort50mmLinActEnable, LOW);
  digitalWrite(suction25mmLinActEnable, LOW);

  digitalWrite(suction25mmLinActEnable, HIGH); // Enable suction
  driveLinAct(suction25mmLinActIn1, suction25mmLinActIn2, RETRACT); // Suction product
  delay(4000); // Wait until fully extended (Adjust)
  digitalWrite(suction25mmLinActEnable, LOW); // Disable suction. Maybe can remove if power is not a problem
}

void releaseSuction(){
  ////////Suction and move case////////
  digitalWrite(NEMA17Enable, LOW);
  digitalWrite(NEMA23WheelEnable, LOW);
  digitalWrite(NEMA23LinGuideEnable, LOW);
  digitalWrite(sort50mmLinActEnable, LOW);
  digitalWrite(suction25mmLinActEnable, LOW);

  digitalWrite(suction25mmLinActEnable, HIGH); // Enable suction
  driveLinAct(suction25mmLinActIn1, suction25mmLinActIn2, EXTEND); // Suction product
  delay(4000); // Wait until fully extended (Adjust)
  digitalWrite(suction25mmLinActEnable, LOW); // Disable suction. Maybe can remove if power is not a problem
}



void alignWheelAndCase(){
  ////////Move case and wheel////////

  digitalWrite(NEMA17Enable, LOW);
  digitalWrite(NEMA23WheelEnable, LOW);
  digitalWrite(NEMA23LinGuideEnable, LOW);
  digitalWrite(sort50mmLinActEnable, LOW);
  digitalWrite(suction25mmLinActEnable, LOW);

  NEMA23LinGuideDir = CCW;
  NEMA23WheelDir = CW;
  prevLaserState = 0;
  digitalWrite(laserPin,HIGH);


  digitalWrite(NEMA23LinGuideEnable, HIGH); // Enable the linear guide rail

  while(casePosition != EXPORTenum){ // Move the wheel and linear guide rail while its not lined up
    NEMA23LinGuide.step(NEMA23LinGuideDir * NEMA23LinGuideStep);
    //Serial.println(readUltrasonic(trigPin, echoPin));
    if(readUltrasonic(trigPin, echoPin) < caseExportDistance){ // Checks if the case is in the right position
      casePosition = EXPORT;
      digitalWrite(NEMA23LinGuideEnable, LOW);
    }
  }
  digitalWrite(NEMA23WheelEnable, HIGH); // Enable Wheel

  while(wheelPosition != SUCTIONenum){
    NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);
    laserState = digitalRead(laserRecieverPin);
    //Serial.println(laserState);
    if(laserState == 0 && prevLaserState == 1){ // Check if the wheel is in position
      wheelPosition = SUCTION;
      digitalWrite(NEMA23WheelEnable, LOW);
    }
    prevLaserState = laserState;
  }

  digitalWrite(NEMA23LinGuideEnable, LOW);
  digitalWrite(NEMA23WheelEnable, LOW);
}

void transportProduct(int caseCount){
  ///////Transport product to case//////////
  numLaserBreak = 0;
  prevLaserState = 0;
  NEMA23WheelDir = CCW;

  digitalWrite(NEMA23WheelEnable, HIGH);
  digitalWrite(laserPin, HIGH);
  while(wheelPosition != DROPenum){ // Move wheel to export
    NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);
    laserState = digitalRead(laserRecieverPin);
    if(laserState == 0 && prevLaserState == 1){
      numLaserBreak++;
      if(numLaserBreak == 1){
        wheelPosition = NEUTRAL;
      }
      else if(numLaserBreak == 2){
        wheelPosition = DROP;
      }
    }
    prevLaserState = laserState;
  }

  // Delete if broken
  if(caseCount % 2 == 0){
    for(int i = 0; i < 50; i++){
      NEMA23Wheel.step(NEMA23WheelDir * NEMA23WheelStep);
    }
  }
  //

  digitalWrite(NEMA23WheelEnable, LOW); // Disable wheel NEMA 23

  digitalWrite(suction25mmLinActEnable, HIGH); // Enable suction
  driveLinAct(suction25mmLinActIn1, suction25mmLinActIn2, EXTEND); // Release product into case
  delay(2000); // Wait until fully extended (Adjust)
  digitalWrite(suction25mmLinActEnable, LOW); // Disable suction
}


int caseCount = 0;

void loop() {
  /*
  digitalWrite(suction25mmLinActEnable, HIGH);
  driveLinAct(suction25mmLinActIn1, suction25mmLinActIn2, resetSuction);
  delay(5000);
  digitalWrite(suction25mmLinActEnable, LOW);

  delay(5000);
  */
  //while(digitalRead(checkIfSupplyOn) == 0){}
  for(int i = 0; i < 2; i++){
    resetMotors(caseCount);
    inputAndSort();

    alignWheelAndCase();
    delay(2000);
    suction();

    //wheelPosition = SUCTION;
    transportProduct(caseCount);
    releaseSuction();
    caseCount++;
  }
  
}
