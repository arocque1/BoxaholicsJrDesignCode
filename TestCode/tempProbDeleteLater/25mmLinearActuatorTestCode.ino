enum linActDir{EXTEND, RETRACT};
/*///////////////////////////////////////////
////////////Notes////////////////////////////
- The red wire goes to OUT1
- The black wire goes to OUT2
*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int in1 = 2;
const int in2 = 3;
linActDir linAct25mmDir = RETRACT; // EXTEND or RETRACT
/////////////////////////////
 

void setup() {
  

}

void loop() {

  driveLinAct(in1, in2, linAct25mmDir);

}
