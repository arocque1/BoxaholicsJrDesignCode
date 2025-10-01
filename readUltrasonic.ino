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