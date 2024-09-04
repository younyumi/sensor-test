#include "MultiUltrasonic.h"

MultiUltrasonic::MultiUltrasonic(int trig[], int echo[], int num) {
    this->trig = trig;
    this->echo = echo;
    this->num = num;
    distances = new float[num];
}

void MultiUltrasonic::begin() {
    for (int i = 0; i < num; i++) {
        pinMode(trig[i], OUTPUT);
        pinMode(echo[i], INPUT);
    }
}

void MultiUltrasonic::update() {
    for (int i = 0; i < num; i++) {
        distances[i] = measureDistance(trig[i], echo[i]);
    }
}

float MultiUltrasonic::getDistance(int index) {
    if (index >= 0 && index < num) {
        return distances[index];
    } else {
        return -1;  // 잘못된 인덱스 처리
    }
}

long MultiUltrasonic::measureDistance(int triggerPin, int echoPin) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    return (duration * 0.034) / 2;
}