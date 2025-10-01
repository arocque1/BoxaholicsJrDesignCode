void driveLinAct(int inOdd, int inEven, linActDir dir){
    /* Function: Drives linear actuator
     * Inputs:
     *          vPosPin: Integer describing Arduino pin connected to positive wire on linear actuator.
     *                  Typically the red wire.
     *          vNegPin: Integer describing Arduino pin connected to negative/ground wire on linear actuator.
     *                  Typically the black wire
     *          dir: Enumerator describing desired direction of linear actuator.
     */
    switch(dir){
        case EXTEND:
            digitalWrite(inOdd, HIGH);
            digitalWrite(inEven, LOW);
            break;

        case RETRACT:
            digitalWrite(inOdd, LOW);
            digitalWrite(inEven, HIGH);
            break;
    }
}