#include <Arduino.h>
#include "MultiUltrasonic.h"

const int num = 4;
int trig[num] = {2, 4, 6, 8};
int acho[num] = {3, 5, 7, 9};

MultiUltrasonic ultrasonicSensors(trig, acho, num);




void setup() {
    Serial.begin(9600);
    ultrasonicSensors.begin();
}

void loop() {
    ultrasonicSensors.update();

    for (int i = 0; i < num
; i++) {
        Serial.print("Sensor ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(ultrasonicSensors.getDistance(i));
        Serial.println(" cm");
    }

    Serial.println("---------------------");
    delay(500);
}