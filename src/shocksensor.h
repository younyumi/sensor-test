#ifndef SHOCKSENSOR_H
#define SHOCKSENSOR_H

#include <Arduino.h>

class ShockSensor {
public:
    ShockSensor(int pin);
    bool isShockDetected();

private:
    int pin;
};

#endif