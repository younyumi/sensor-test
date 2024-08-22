#ifndef MULTIULTRASONIC_H
#define MULTIULTRASONIC_H

#include <Arduino.h>

class MultiUltrasonic {
public:
    MultiUltrasonic(int triggerPins[], int echoPins[], int numSensors);
    void begin();   //초음파 센서 핀 설정 함수
    void update();  //거리 데이터 업데이트 함수
    float getDistance(int index);  //측정된 거리 받아옴

private:
    int* triggerPins;
    int* echoPins;
    int numSensors;
    float* distances;
    long measureDistance(int triggerPin, int echoPin);
};

#endif
