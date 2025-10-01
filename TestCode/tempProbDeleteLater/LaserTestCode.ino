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

const int laserPin = 2;
const int laserRecieverPin = 3;

int laserReadVal;
float wheelAngle = 0;
const float numDivs = 16;
const float dAngle = 360 / numDivs;
int beamState;

////////////////////////////

//////Variables from other parts///
//NEMA23Wheel: 
enum stepperDir{CW = 1, CCW = -1};
stepperDir NEMA23WheelDir = CCW; // For testing only

///////////////////

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
if(laserReadVal == 0 && beamState == 1){
  wheelAngle = wheelAngle + (NEMA23WheelDir * dAngle);
}
beamState = laserReadVal;

//Serial.print("Angle: ");
//Serial.println(wheelAngle);

}