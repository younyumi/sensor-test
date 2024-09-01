#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

class MPU6050 {
public:
    bool begin();
    void getAcceleration(float &ax, float &ay, float &az);
    void getRollPitch(float &roll, float &pitch);

private:
    Adafruit_MPU6050 mpu;
};

#endif
