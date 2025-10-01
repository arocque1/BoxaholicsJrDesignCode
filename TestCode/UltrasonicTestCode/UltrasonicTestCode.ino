/*///////////////////////////////////////////
////////////Notes////////////////////////////
- Vcc goes to 5V
- GND goes to ground
- Trig and echo go to a digital pin
*///////////////////////////////

/////////////////////////////
//////////Variables//////////
const int trigPin = 51;
const int echoPin = 50;
float ultrasonicDistance;
float ultrasonicDuration;
/////////////////////////////


float readUltrasonic(int trigPin, int echoPin){
  float ultrasonicDistance;
  float ultrasonicDuration;
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  ultrasonicDuration = pulseIn(echoPin, HIGH);

  ultrasonicDistance = 0.017 * ultrasonicDuration / 2;

  return ultrasonicDistance;
}


void setup() {
  Serial.begin(9600); //Optional only for outputting

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  ultrasonicDuration = pulseIn(echoPin, HIGH);

  ultrasonicDistance = 0.017 * ultrasonicDuration / 2;

  Serial.println(ultrasonicDistance); // Option for outputting

}
