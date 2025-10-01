/*///////////////////////////////////////////
////////////Notes////////////////////////////
- Vcc goes to 3.3V (maybe 5V but idk)
- GND goes to ground
- Out goes to a digital pin

- An output of 1 means there's nothing close
- An output of 0 means something is close

*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int IRreadPin = 2;
int IRreadVal;
/////////////////////////////

void setup() {
  Serial.begin(9600); //Only for outputting, not essential
  pinMode(IRreadPin, INPUT);

}

void loop() {
  IRreadVal = digitalRead(IRreadPin);
  Serial.println(IRreadVal);
}
