#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>

class MPU6050 {
  public:
    MPU6050(int address);
    void initialize();
    int16_t getAccelerationZ();

  private:
    int deviceAddress;
    int16_t readRegister16(int reg);
};

#endif
