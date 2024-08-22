#include <Arduino.h>
#include "MPU6050.h"

MPU6050 mpuModule;

void setup() {
    Serial.begin(115200);
    mpuModule.begin(); // MPU6050 초기화
}

void loop() {
    mpuModule.readSensors(); // 센서 데이터 읽기 및 출력
    Serial.println("");      // 출력 간격을 주기 위해 빈 줄 추가
    delay(500);              // 0.5초 간격으로 데이터 출력
}
