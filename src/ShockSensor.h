#ifndef SHOCKSENSOR_H
#define SHOCKSENSOR_H

#include <Arduino.h>

class ShockSensor {
  public:
    ShockSensor(int pin);
    void begin();
    bool isShockDetected();
    
  private:
    int _pin;
};

#endif
