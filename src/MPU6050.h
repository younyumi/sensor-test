#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>

class MPU6050 {
  public:
    MPU6050(int address);
    void initialize();
    float getAccelerationZ();  // Modify return type to float for m/s²

  private:
    int deviceAddress;
    int16_t readRegister16(int reg);
};

#endif
