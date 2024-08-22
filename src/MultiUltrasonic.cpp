#include "MultiUltrasonic.h"

MultiUltrasonic::MultiUltrasonic(int triggerPins[], int echoPins[], int numSensors) {
    this->triggerPins = triggerPins;
    this->echoPins = echoPins;
    this->numSensors = numSensors;
    distances = new float[numSensors];
}

void MultiUltrasonic::begin() {
    for (int i = 0; i < numSensors; i++) {
        pinMode(triggerPins[i], OUTPUT);
        pinMode(echoPins[i], INPUT);
    }
}

void MultiUltrasonic::update() {
    for (int i = 0; i < numSensors; i++) {
        distances[i] = measureDistance(triggerPins[i], echoPins[i]);
    }
}

float MultiUltrasonic::getDistance(int index) {
    if (index >= 0 && index < numSensors) {
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
