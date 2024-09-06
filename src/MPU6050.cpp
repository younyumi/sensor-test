#include "MPU6050.h"

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

int16_t MPU6050::getAccelerationZ() {
    return readRegister16(0x3F);  // Z-axis acceleration register
}

int16_t MPU6050::readRegister16(int reg) {
    Wire.beginTransmission(deviceAddress);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(deviceAddress, 2, true);
    
    int16_t value = Wire.read() << 8 | Wire.read();
    return value;
}
