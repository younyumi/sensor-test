#include  <Arduino.h>
#include "MPU6050.h"

MPU6050 mpuModule; //  MPU6050 클래스의 mpuModule객체 생성

void setup() {
    Serial.begin(115200);
    mpuModule.begin();
}

void loop() {
    mpuModule.readSensors();
    Serial.println("");
    delay(500);
}
