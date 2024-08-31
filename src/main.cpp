#include <Arduino.h>
#include "Ultrasonic.h"
#include "MPU6050.h"


#define TRIG_PIN 9
#define ECHO_PIN 10

UltrasonicSensor ultrasonicSensor(TRIG_PIN, ECHO_PIN);
MPU6050 mpu6050Sensor;

void setup() {
    Serial.begin(115200);

    if (!mpu6050Sensor.begin()) {
        Serial.println("MPU6050 failed");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 success");
}

void loop() {
    float distance = ultrasonicSensor.getDistance();

    float roll, pitch;
    mpu6050Sensor.getRollPitch(roll, pitch);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm, ");

    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print(" deg, ");

    Serial.print("Pitch: ");
    Serial.print(pitch);
    Serial.println(" deg");

    delay(500);
}
