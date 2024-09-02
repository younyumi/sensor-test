#include <Arduino.h>
#include "Ultrasonic.h"
#include "MPU6050.h"
#include "shocksensor.h"

const int numSensors = 4;  

int trigPins[numSensors] = {2, 4, 6, 8};
int echoPins[numSensors] = {3, 5, 7, 9};

// Define I2C addresses for each MPU6050 sensor (assuming unique addresses)
int mpuAddresses[numSensors] = {0x68, 0x69, 0x6A, 0x6B};

// shock sensor pin number
int shockPins[numSensors] = {10, 11, 12, 13};

//우측전륜, 좌측전륜, 우측후륜, 좌측후륜
const char* sensorLabels[numSensors] = {"FR", "FL", "RR", "RL"};

UltrasonicSensor* ultrasonicSensors[numSensors];
MPU6050* mpu6050Sensors[numSensors];
ShockSensor* shockSensors[numSensors];

void setup() {
    Serial.begin(115200);

    for (int i = 0; i < numSensors; i++) {
        ultrasonicSensors[i] = new UltrasonicSensor(trigPins[i], echoPins[i]);
    }

    for (int i = 0; i < numSensors; i++) {
        mpu6050Sensors[i] = new MPU6050(mpuAddresses[i]);
        if (!mpu6050Sensors[i]->begin()) {
            Serial.print("MPU6050 #");
            Serial.print(i + 1);
            Serial.println(" failed");
            while (1) {
                delay(10);
            }
        }
        Serial.print("MPU6050 #");
        Serial.print(i + 1);
        Serial.println(" success");
    }

    for (int i = 0; i < numSensors; i++) {
        shockSensors[i] = new ShockSensor(shockPins[i]);
    }
}

void loop() {
    // Read and print distances from each ultrasonic sensor
    Serial.print("Sensor1: ");
    Serial.print(ultrasonicSensors[0]->getDistance());
    Serial.print(", Sensor2: ");
    Serial.print(ultrasonicSensors[1]->getDistance());
    Serial.print(", Sensor3: ");
    Serial.print(ultrasonicSensors[2]->getDistance());
    Serial.print(", Sensor4: ");
    Serial.println(ultrasonicSensors[3]->getDistance());

    for (int i = 0; i < numSensors; i++) {
        float ax = 0, ay = 0, az = 0;
        mpu6050Sensors[i]->getAcceleration(ax, ay, az);

        float roll = 0, pitch = 0;
        mpu6050Sensors[i]->getRollPitch(roll, pitch);

        Serial.print(sensorLabels[i]);
        Serial.print("- Acc_X:");
        Serial.print(ax, 2);
        Serial.print(", Acc_Y:");
        Serial.print(ay, 2);
        Serial.print(", Acc_Z:");
        Serial.print(az, 2);
        Serial.print(", Roll:");
        Serial.print(roll, 2);
        Serial.print(", Pitch: ");
        Serial.println(pitch, 2);
    }


// 충격 감지되면1, 안되면0
    for (int i = 0; i < numSensors; i++) {
        Serial.print(sensorLabels[i]);
        Serial.print("- Shock Detected: ");
        Serial.println(shockSensors[i]->isShockDetected() ? "1" : "0");
    }

    Serial.println("---------------------------------------------------------------------------------");
    delay(500);
}
