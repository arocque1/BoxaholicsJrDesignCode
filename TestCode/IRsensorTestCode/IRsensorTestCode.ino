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
const int beamPin = 49;
int beamRead;
/////////////////////////////

void setup() {
  Serial.begin(9600); //Only for outputting, not essential
  pinMode(beamPin, INPUT);

}

void loop() {
  beamRead = digitalRead(beamPin);
  Serial.println(beamRead);
}
