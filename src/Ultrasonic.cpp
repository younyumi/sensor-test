#include "Ultrasonic.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) 
    : triggerPin(triggerPin), echoPin(echoPin) {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int UltrasonicSensor::getDistance() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.0344 / 2;
    return distance;
}
