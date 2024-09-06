#include <Arduino.h>
#include "MultiUltrasonic.h"
#include "MPU6050.h"  // MPU6050 라이브러리 포함
#include "shocksensor.h"

const int num = 2;  // 두 개의 MPU6050 센서를 사용하므로 num을 2로 설정

int trig[4] = {2, 4, 6, 8};
int echo[4] = {3, 5, 7, 9};

// 두 개의 MPU6050의 I2C 주소 (0x68, 0x69)
int mpuAddresses[num] = {0x68, 0x69};

// 충격 센서 핀 번호
int shockPins[4] = {10, 11, 12, 13};

// 센서 라벨
const char* sensorLabels[4] = {"FR", "FL", "RR", "RL"};

MultiUltrasonic ultrasonicSensors(trig, echo, 4);
MPU6050* mpu6050Sensors[num];  // 두 개의 MPU6050 센서
ShockSensor* shockSensors[4];

void setup() {
    // 시리얼 통신 초기화
    Serial.begin(115200);
    
    // 초음파 센서 초기화
    ultrasonicSensors.begin();

    // MPU6050 센서 초기화
    for (int i = 0; i < num; i++) {
        mpu6050Sensors[i] = new MPU6050(mpuAddresses[i]);
        mpu6050Sensors[i]->initialize();
    }

    // 충격 센서 초기화
    for (int i = 0; i < 4; i++) {
        shockSensors[i] = new ShockSensor(shockPins[i]);
    }
}

void loop() {
    // 초음파 거리 업데이트
    ultrasonicSensors.update();

    // 각 초음파 센서의 거리 출력
    for (int i = 0; i < 4; i++) {
        Serial.print("Ultrasonic Sensor ");
        Serial.print(sensorLabels[i]);
        Serial.print(": ");
        Serial.print(ultrasonicSensors.getDistance(i));
        Serial.println(" cm");
    }

    // 각 충격 센서의 감지 상태 출력
    for (int i = 0; i < 4; i++) {
        Serial.print("Shock Sensor ");
        Serial.print(sensorLabels[i]);
        Serial.print(": ");
        Serial.println(shockSensors[i]->isShockDetected() ? "1" : "0");
    }

    // 두 개의 MPU6050 센서 Z축 가속도 출력
    for (int i = 0; i < num; i++) {
        Serial.print("MPU6050 Sensor ");
        Serial.print(i + 1);
        Serial.print(" Z-axis: ");
        Serial.println(mpu6050Sensors[i]->getAccelerationZ());
    }

    // 구분선 출력
    Serial.println("---------------------");

    // 다음 반복 전 딜레이
    delay(100);
}
