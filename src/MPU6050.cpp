#include "MPU6050.h"

bool MPU6050::begin() {
    if (!mpu.begin()) {
        return false;
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);  //2,4,8,16 클수록 민감도 낮아짐
    mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);  //5,10,21,44,94,184,260 필터 대역폭, 작을수록 노이즈 제거 잘되는데 신호 반응속도 느림
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
