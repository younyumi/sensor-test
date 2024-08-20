#include "MPU6050.h"

MPU6050::MPU6050() {}

void MPU6050::begin() {
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void MPU6050::read() {
    mpu.getEvent(&a, &g, &temp);
}

float MPU6050::getTemperature() {
    return temp.temperature;
}

float MPU6050::getAccelerationX() {
    return a.acceleration.x;
}

float MPU6050::getAccelerationY() {
    return a.acceleration.y;
}

float MPU6050::getAccelerationZ() {
    return a.acceleration.z;
}

float MPU6050::getGyroscopeX() {
    return g.gyro.x;
}

float MPU6050::getGyroscopeY() {
    return g.gyro.y;
}

float MPU6050::getGyroscopeZ() {
    return g.gyro.z;
}
