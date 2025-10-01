enum linActDir{EXTEND, RETRACT};
/*///////////////////////////////////////////
////////////Notes////////////////////////////
- The red wire goes to OUT1
- The black wire goes to OUT2
*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int in1 = 37;
const int in2 = 36;
linActDir linAct25mmDir = EXTEND; // EXTEND or RETRACT
const int suction25mmLinActEnable = 7;
/////////////////////////////
 

void setup() {
  
digitalWrite(suction25mmLinActEnable, HIGH);
}

void loop() {

  driveLinAct(in1, in2, linAct25mmDir);

}
