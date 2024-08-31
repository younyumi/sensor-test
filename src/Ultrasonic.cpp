#include "Ultrasonic.h"

UltrasonicSensor::UltrasonicSensor(int trig, int echo) 
    : trig(trig), echo(echo) {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

int UltrasonicSensor::getDistance() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    long duration = pulseIn(echo, HIGH);
    int distance = duration * 0.0344 / 2;  
    return distance;
}
