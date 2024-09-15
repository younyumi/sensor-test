#include <Arduino.h>
#include "TinyGPS++.h"
#include "MultiUltrasonic.h"
#include "MPU6050.h"  // MPU6050 라이브러리 포함
#include "shocksensor.h"

static const uint32_t GPSBaud = 9600;

const int num = 2;  // 두 개의 MPU6050 센서를 사용하므로 num을 2로 설정

int trig[4] = {2, 4, 6, 8};
int echo[4] = {3, 5, 7, 9};

// 두 개의 MPU6050의 I2C 주소 (0x68, 0x69)
int mpuAddresses[num] = {0x68, 0x69};

// 충격 센서 핀 번호
int shockPins[4] = {40, 41, 42, 43};

// 센서 라벨
const char* sensorLabels[4] = {"FR", "FL", "RR", "RL"};

TinyGPSPlus gps;
MultiUltrasonic ultrasonicSensors(trig, echo, 4);
MPU6050* mpu6050Sensors[num];  // 두 개의 MPU6050 센서
ShockSensor* shockSensors[4];

void setup() {
    // 시리얼 통신 초기화
    Serial.begin(115200); // 컴퓨터와의 통신 속도
    Serial1.begin(GPSBaud);  // GPS 모듈과의 통신 속도
    ultrasonicSensors.begin();  // 초음파 센서 초기화

    // MPU6050 센서 초기화
    for (int i = 0; i < num; i++) {
        mpu6050Sensors[i] = new MPU6050(mpuAddresses[i]);
        mpu6050Sensors[i]->initialize();
    }

    // 충격 센서 초기화
    for (int i = 0; i < 4; i++) {
        shockSensors[i] = new ShockSensor(shockPins[i]);
    }
}

void loop() {
    // 초음파 거리 업데이트
    ultrasonicSensors.update();

    // 각 초음파 센서의 거리 출력
    for (int i = 0; i < 4; i++) {
        Serial.print("Ultrasonic ");
        Serial.print(i+1);
        Serial.print(": ");
        Serial.println(ultrasonicSensors.getDistance(i));
    }

    // 각 충격 센서의 감지 상태 출력
    for (int i = 0; i < 4; i++) {
        Serial.print("Shock Sensor ");
        Serial.print(sensorLabels[i]);
        Serial.print(": ");
        Serial.println(shockSensors[i]->isShockDetected() ? "1" : "0");
    }

    // 두 개의 MPU6050 센서의 가속도와 Roll, Pitch 출력
    for (int i = 0; i < num; i++) {
        float ax = mpu6050Sensors[i]->getAccelerationX();
        float ay = mpu6050Sensors[i]->getAccelerationY();
        float az = mpu6050Sensors[i]->getAccelerationZ();
        float roll = mpu6050Sensors[i]->calculateRoll(ax, ay, az);
        float pitch = mpu6050Sensors[i]->calculatePitch(ax, ay, az);
        
        Serial.print("MPU6050 Sensor ");
        Serial.print(i + 1);
        Serial.print(" Z_acc : ");
        Serial.println(az);
        Serial.print("Roll: ");
        Serial.println(roll);
        Serial.print("Pitch: ");
        Serial.println(pitch);
    }
    
    while (Serial1.available() > 0) {
        gps.encode(Serial1.read());  
    }
    if (gps.location.isUpdated()) {
        Serial.print("Latitude: ");
        Serial.print(gps.location.lat(), 6);  
        Serial.print(", Longitude: ");
        Serial.println(gps.location.lng(), 6);  
        } else {
        Serial.println("Waiting for GPS data...");
    }

    Serial.println("---------------------");

    delay(500);
}
