#ifndef MPU6050_H
#define MPU6050_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

class MPU6050 {
public:
    MPU6050();
    void begin();
    void readSensors();

private:
    Adafruit_MPU6050 mpu;
};

#endif
