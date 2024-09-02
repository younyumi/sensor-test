#include "MPU6050.h"

MPU6050::MPU6050(int address)
    : address(address) {}

bool MPU6050::begin() {
    Wire.begin();
    Wire.beginTransmission(address);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // Wake up MPU6050
    return Wire.endTransmission() == 0;
}


// bool MPU6050::begin() {
//     Wire.begin();
//     Wire.beginTransmission(address);
//     Wire.write(0x6B);  // PWR_MGMT_1 register
//     Wire.write(0);     // Wake up MPU6050
//     if (Wire.endTransmission() != 0) {
//         return false;
//     }

//     // 기본 설정
//     setAccelerometerRange(MPU6050_RANGE_8_G);
//     setGyroRange(MPU6050_RANGE_1000_DEG);
//     setFilterBandwidth(MPU6050_BAND_94_HZ);

//     return true;
// }    범위설정 테스트해보고 필요하면 추가 

void MPU6050::getAcceleration(float& ax, float& ay, float& az) {
    Wire.beginTransmission(address);
    Wire.write(0x3B);  // Starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(address, 6, true);  // Request a total of 6 registers

    ax = readWord2C(0) / 16384.0;
    ay = readWord2C(2) / 16384.0;
    az = readWord2C(4) / 16384.0;
}

void MPU6050::getRollPitch(float& roll, float& pitch) {
    float ax, ay, az;
    getAcceleration(ax, ay, az);

    roll = atan2(ay, az) * 180.0 / PI;
    pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
}

float MPU6050::readWord2C(int addr) {
    Wire.beginTransmission(address);
    Wire.write(addr);
    Wire.endTransmission(false);
    Wire.requestFrom(address, 2, true);
    
    int16_t value = Wire.read() << 8 | Wire.read();
    return (float)value;
}
