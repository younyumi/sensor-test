#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#include <Arduino.h>

class MPU6050 {
public:
    MPU6050(int address);
    bool begin();

    // void setAccelerometerRange(uint8_t range);   범위 설정 함수
    // void setGyroRange(uint8_t range);
    // void setFilterBandwidth(uint8_t bandwidth);
    
    void getAcceleration(float& ax, float& ay, float& az);
    void getRollPitch(float& roll, float& pitch);

private:
    int address;
    float readWord2C(int addr);
};

#endif
