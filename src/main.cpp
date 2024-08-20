#include <Arduino.h>
#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu;

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    
    mpu.begin();
    Serial.println("MPU6050 initialized.");
}

void loop() {
    mpu.read();

    Serial.print("Temperature: ");
    Serial.print(mpu.getTemperature());
    Serial.println(" C");

    Serial.print("Acceleration X: ");
    Serial.print(mpu.getAccelerationX());
    Serial.println(" m/s^2");

    Serial.print("Acceleration Y: ");
    Serial.print(mpu.getAccelerationY());
    Serial.println(" m/s^2");

    Serial.print("Acceleration Z: ");
    Serial.print(mpu.getAccelerationZ());
    Serial.println(" m/s^2");

    Serial.print("Gyroscope X: ");
    Serial.print(mpu.getGyroscopeX());
    Serial.println(" rad/s");

    Serial.print("Gyroscope Y: ");
    Serial.print(mpu.getGyroscopeY());
    Serial.println(" rad/s");

    Serial.print("Gyroscope Z: ");
    Serial.print(mpu.getGyroscopeZ());
    Serial.println(" rad/s");

    delay(1000);
}
