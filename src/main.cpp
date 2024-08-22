#include <Arduino.h>
#include "MultiUltrasonic.h"

const int numSensors = 4;
int triggerPins[numSensors] = {2, 4, 6, 8};
int echoPins[numSensors] = {3, 5, 7, 9};

MultiUltrasonic ultrasonicSensors(triggerPins, echoPins, numSensors);

void setup() {
    Serial.begin(9600);
    ultrasonicSensors.begin();
}

void loop() {
    ultrasonicSensors.update();

    for (int i = 0; i < numSensors; i++) {
        Serial.print("Sensor ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(ultrasonicSensors.getDistance(i));
        Serial.println(" cm");
    }

    Serial.println("---------------------");
    delay(500);
}
