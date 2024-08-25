#include "MPU6050.h"
#include <Wire.h>
#include <Arduino.h>

MPU6050::MPU6050() : mpu() {}  //mpu 객체

void MPU6050::begin() {
    if(!mpu.begin()) {
        Serial.println("Failed to find MPU6050");   //센서 연결 오류코드
        while(1){
            delay(10);
        }
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);  //가속도 인식 범위 : 플마8G로 설정함, 테스트해보고 수정
    mpu.setGyroRange(MPU6050_RANGE_1000_DEG);       //너무 넓으면 분해능 저하
    mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);  //주파수 범위(44,94,184,260) 너무 높으면 노이즈많이포함, 너무 낮으면 반응속도떨어짐
}

void MPU6050::readSensors() {
    sensors_event_t a, g,temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print("Acceleration X: ");    //가속도랑 roll, pitch만 사용할듯
    Serial.print(a.acceleration.x);
    Serial.print("Acceleration Y: ");
    Serial.print(a.acceleration.y);
    Serial.print("Acceleration Z: ");
    Serial.print(a.acceleration.z);
    Serial.println("m/s^2");

    // 각속도 출력 (rad/s)
    // Serial.print("Rotation X: ");
    // Serial.print(g.gyro.x);
    // Serial.print(" rad/s, Y: ");
    // Serial.print(g.gyro.y);
    // Serial.print(" rad/s, Z: ");
    // Serial.print(g.gyro.z);
    // Serial.println(" rad/s");

    float roll = atan(a.acceleration.x / sqrt(pow(a.acceleration.y,2)+pow(a.acceleration.z,2)))*180.0/PI;
    float pitch = atan(a.acceleration.y / sqrt(pow(a.acceleration.x,2)+pow(a.acceleration.z,2)))*180.0/PI;

    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print(" deg, ");

    Serial.print("Pitch: ");
    Serial.print(pitch);
    Serial.print(" deg");

    Serial.println("");
    delay(500);
}
