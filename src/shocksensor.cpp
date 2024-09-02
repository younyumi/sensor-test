#include "shocksensor.h"

ShockSensor::ShockSensor(int pin) : pin(pin) {
    pinMode(pin, INPUT);
}
bool ShockSensor::isShockDetected(){
    return digitalRead(pin) == HIGH;
}