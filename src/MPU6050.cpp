#include "MPU6050.h"

bool MPU6050::begin() {
    if (!mpu.begin()) {
        return false;
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    delay(100);
    return true;
}

void MPU6050::getAcceleration(float &ax, float &ay, float &az) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    ax = a.acceleration.x;
    ay = a.acceleration.y;
    az = a.acceleration.z;
}

void MPU6050::getRollPitch(float &roll, float &pitch) {
    float ax, ay, az;
    getAcceleration(ax, ay, az);
    roll  = atan2(ay, az) * 180.0 / PI;
    pitch = atan(-ax / sqrt(ay * ay + az * az)) * 180.0 / PI;
}
