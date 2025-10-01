/*///////////////////////////////////////////
////////////Notes////////////////////////////
- Vcc goes to 5V
- GND goes to ground
- White wire goes to a digital pin
*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int beamPin = 2;
int beamRead;
/////////////////////////////


void setup() {
  Serial.begin(9600); // Optional for printing data
  pinMode(2, INPUT);
  //digitalWrite(beamPin, HIGH);

}

void loop() {
  beamRead = digitalRead(beamPin);
  Serial.println(beamRead);
}
