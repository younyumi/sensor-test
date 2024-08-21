#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#include <Adafruit_MPU6050.h>

class MPU6050 {
public:
    MPU6050();
    void begin();
    void read();
    float getTemperature();
    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();
    float getGyroscopeX();
    float getGyroscopeY();
    float getGyroscopeZ();

private:
    Adafruit_MPU6050 mpu;
    sensors_event_t a, g, temp;
};

#endif
