#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>

class MPU6050 {
  public:
    MPU6050(int address);
    void initialize();
    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();
    float calculateRoll(float ax, float ay, float az);
    float calculatePitch(float ax, float ay, float az);

  private:
    int deviceAddress;
    int16_t readRegister16(int reg);
};

#endif