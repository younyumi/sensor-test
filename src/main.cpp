#include <Arduino.h>
#include "MultiUltrasonic.h"
//#include "MPU6050.h"
#include "shocksensor.h"

const int num = 4;  

int trig[num] = {2, 4, 6, 8};
int echo[num] = {3, 5, 7, 9};

// Define I2C addresses for each MPU6050 sensor (assuming unique addresses)
//int mpuAddresses[num] = {0x68, 0x69, 0x6A, 0x6B};

// shock sensor pin number
int shockPins[num] = {10, 11, 12, 13};

//우측전륜, 좌측전륜, 우측후륜, 좌측후륜
const char* sensorLabels[num] = {"FR", "FL", "RR", "RL"};

MultiUltrasonic ultrasonicSensors(trig, echo, num);
//MPU6050* mpu6050Sensors[num];
ShockSensor* shockSensors[num];

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    
    // Initialize ultrasonic sensors
    ultrasonicSensors.begin();

    // Initialize shock sensors
    for (int i = 0; i < num; i++) {
        shockSensors[i] = new ShockSensor(shockPins[i]);
    }
}

void loop() {
    // Update distance measurements
    ultrasonicSensors.update();

    // Print distance from each ultrasonic sensor
    for (int i = 0; i < num; i++) {
        Serial.print("Ultrasonic Sensor ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(ultrasonicSensors.getDistance(i));
        Serial.println(" cm");
    }

    // Print shock detection status from each shock sensor
    for (int i = 0; i < num; i++) {
        Serial.print("Shock Sensor ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(shockSensors[i]->isShockDetected() ? "1" : "0");
    }

    // Divider for readability
    Serial.println("---------------------");

    // Delay before the next loop iteration
    delay(500);
}
