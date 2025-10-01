void driveLinAct(int inEven, int inOdd, linActDir dir){
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
            digitalWrite(inEven, HIGH);
            digitalWrite(inOdd, LOW);
            break;

        case RETRACT:
            digitalWrite(inEven, LOW);
            digitalWrite(inOdd, HIGH);
            break;
    }
}