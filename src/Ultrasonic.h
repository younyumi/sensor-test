#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    int getDistance();

private:
    int triggerPin;
    int echoPin;
};

#endif
