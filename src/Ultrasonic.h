#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int trig, int echo);

    int getDistance();

private:
    int trig;
    int echo;
};

#endif
