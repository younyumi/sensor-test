#include "ShockSensor.h"

ShockSensor::ShockSensor(int pin) {
  _pin = pin;
}

void ShockSensor::begin() {
  pinMode(_pin, INPUT);
}

bool ShockSensor::isShockDetected() {
  int sensorValue = digitalRead(_pin);
  return sensorValue == HIGH;
}
