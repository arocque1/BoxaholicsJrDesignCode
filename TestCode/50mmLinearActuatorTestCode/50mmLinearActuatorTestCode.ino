enum linActDir{EXTEND, RETRACT};
/*///////////////////////////////////////////
////////////Notes////////////////////////////
- The red wire goes to OUT1
- The black wire goes to OUT2
*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int sort50mmLinActIn1 = 34;
const int sort50mmLinActIn2 = 35;
const int sort50mmLinActEnable = 6;
linActDir linAct50mmDir = RETRACT; // EXTEND or RETRACT
/////////////////////////////
 

void setup() {
  pinMode(sort50mmLinActIn1, OUTPUT);
  pinMode(sort50mmLinActIn2, OUTPUT);
  pinMode(sort50mmLinActEnable, OUTPUT);

  digitalWrite(sort50mmLinActEnable, HIGH);

}

void loop() {
  driveLinAct(sort50mmLinActIn1, sort50mmLinActIn2, linAct50mmDir);

}
