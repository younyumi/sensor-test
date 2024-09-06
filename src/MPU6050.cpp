#include "MPU6050.h"
#include <math.h>  // Roll, Pitch 계산에 필요

MPU6050::MPU6050(int address) {
    deviceAddress = address;
}

void MPU6050::initialize() {
    Wire.begin();
    Wire.beginTransmission(deviceAddress);
    Wire.write(0x6B);  // Power management register
    Wire.write(0);     // Wake the MPU6050 up
    Wire.endTransmission(true);
}

float MPU6050::getAccelerationX() {
    int16_t rawX = readRegister16(0x3B);  // X-axis acceleration register
    float xG = rawX / 16384.0;  // Convert raw data to G-force
    return xG * 9.80665;  // Convert G-force to m/s²
}

float MPU6050::getAccelerationY() {
    int16_t rawY = readRegister16(0x3D);  // Y-axis acceleration register
    float yG = rawY / 16384.0;  // Convert raw data to G-force
    return yG * 9.80665;  // Convert G-force to m/s²
}

float MPU6050::getAccelerationZ() {
    int16_t rawZ = readRegister16(0x3F);  // Z-axis acceleration register
    float zG = rawZ / 16384.0;  // Convert raw data to G-force
    return zG * 9.80665;  // Convert G-force to m/s²
}

float MPU6050::calculateRoll(float ax, float ay, float az) {
    return atan2(ay, az) * 180.0 / M_PI;
}

float MPU6050::calculatePitch(float ax, float ay, float az) {
    return atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / M_PI;
}

int16_t MPU6050::readRegister16(int reg) {
    Wire.beginTransmission(deviceAddress);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(deviceAddress, 2, true);
    
    int16_t value = Wire.read() << 8 | Wire.read();
    return value;
}
