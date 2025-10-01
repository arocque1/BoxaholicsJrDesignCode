/*///////////////////////////////////////////
////////////Notes////////////////////////////

Emitter:
- GND goes to ground
- Signal goes to a digital pin

Reciever:
- Vcc goes to 3.3V (Maybe 5V??)
- GND goes to ground
- Out goes to a digital pin

- 1 means the laser is detected
- 0 means no laser detected

WARNING!!!!
MAKE SURE THAT THE NUB ON THE EMITTER DIODE
IS FACING THE PINS.

*///////////////////////////////

/////////////////////////////
//////////Variables//////////

const int laserPin = 53;
const int laserRecieverPin = 52;

int laserReadVal;
int beamState;

//////////////////////////

void setup(){ 

Serial.begin(9600); //Optional for outputting

pinMode(laserPin, OUTPUT);
pinMode(laserRecieverPin, INPUT);

beamState = digitalRead(laserRecieverPin);

}

void loop(){

digitalWrite(laserPin, HIGH);
laserReadVal = digitalRead(laserRecieverPin);

Serial.println(laserReadVal);

//Serial.print("Angle: ");
//Serial.println(wheelAngle);

}