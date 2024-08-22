#include "MPU6050.h"
#include <Wire.h>
#include <Arduino.h>

MPU6050::MPU6050() : mpu() {}

void MPU6050::begin() {
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }

    Serial.println("MPU6050 Found!");

    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void MPU6050::readSensors() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // 가속도 출력 (m/s^2)
    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(" m/s^2, Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(" m/s^2, Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");

    // 각속도 출력 (rad/s)
    Serial.print("Rotation X: ");
    Serial.print(g.gyro.x);
    Serial.print(" rad/s, Y: ");
    Serial.print(g.gyro.y);
    Serial.print(" rad/s, Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");

    // Pitch와 Roll 각도 계산 및 출력
    float pitch = atan(a.acceleration.x / sqrt(pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2))) * 180.0 / PI;
    float roll = atan(a.acceleration.y / sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.z, 2))) * 180.0 / PI;

    Serial.print("Pitch: ");
    Serial.print(pitch);
    Serial.print(" degrees, ");

    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.println(" degrees");

    Serial.println(""); // 출력 간격을 주기 위해 빈 줄 추가
    delay(500);         // 0.5초 간격으로 데이터 출력
}
